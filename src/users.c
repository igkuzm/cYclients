#include "config.h"
#include "../cYclients.h"
#include "log.h"
#include "alloc.h"
#include "structs.h"
#include "cJSON.h"
#include "../partner_token.h"
#include "curl_transport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

static CYCUserRole USERROLE;
static CYCUserPermissions USERPERMISSIONS;

CYCLIENTS_ID
cyclients_user_new(const char *token,
				           int company_id,
                   const char *name,
                   const char *phone_number)
{
	int user_id = 0;
	cJSON *post, *responce;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data, *number;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	assert(name);
	assert(phone_number);
	
	sprintf(requestString, "%s/company/%d/staff/quick", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();
	cJSON_AddStringToObject(post, "name", name);
	cJSON_AddNullToObject(post, "specialization");
	cJSON_AddNullToObject(post, "position_id");
	// phone number without +
	number = (char *)phone_number;
	if (*number == '+')
		number++;
	cJSON_AddStringToObject(post, "phone_number", number);
	
	post_data = cJSON_Print(post);
	if (post_data == NULL){
		ERR("%s: can't generate post data", __FILE__);
		return 1;
	}	
	cJSON_free(post);
	
	http_code = curl_transport_exec(requestString,
									auth, "POST",
									post_data, &responce);
	free(post_data);
	
	if (http_code == 201)
	{
		if (cJSON_IsObject(responce))
		{
			cJSON *data = cJSON_GetObjectItem(responce, "data");
			if (cJSON_IsObject(data))
			{
				cJSON *id = cJSON_GetObjectItem(data, "id");
				if (id)
					user_id = id->valueint;
			}
		}
	}

	if (responce)
		cJSON_free(responce);
	
	return user_id;	
}

CYCLIENTS_COUNTER
cyclients_users_roles(const char *token,
                      int company_id,
					            void *userdata,
                      int (*callback)(void *userdata, 
                                      const CYCUserRole *user_role))
{
	CYCLIENTS_COUNTER n = 0;
	cJSON *responce;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/company/%d/users/roles", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(requestString,
									auth, "GET",
									NULL, &responce);
	
	if (http_code == 200){ // good
		if (cJSON_IsObject(responce))
		{
			cJSON *data = cJSON_GetObjectItem(responce, "data");
			if (cJSON_IsArray(data))
			{
				cJSON *user_role;
				cJSON_ArrayForEach(user_role, data)
				{
					memset(&USERROLE, 0, sizeof(USERROLE));
					cyc_user_role_fr_json(&USERROLE, user_role);
					if (callback)
						if (callback(userdata, &USERROLE))
							break;
					
					n++;
				}
			}
		}
	}
	if (responce)
		cJSON_free(responce);

	return n;	
}

CYCLIENTS_COUNTER
cyclients_user_roles(const char *token,
                     int company_id,
                     int user_id,
                     void *userdata,
                     int (*callback)(void *userdata, 
                                     const CYCUserRole *user_role))
{
	CYCLIENTS_COUNTER n = 0;
	cJSON *responce;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/company/%d/users/%d/roles", 
			URL, company_id, user_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(requestString,
									auth, "GET",
									NULL, &responce);
	
	if (http_code == 200){ // good
		if (cJSON_IsObject(responce))
		{
			cJSON *data = cJSON_GetObjectItem(responce, "data");
			if (cJSON_IsArray(data))
			{
				cJSON *user_role;
				cJSON_ArrayForEach(user_role, data)
				{
					memset(&USERROLE, 0, sizeof(USERROLE));
					cyc_user_role_fr_json(&USERROLE, user_role);
					if (callback)
						if (callback(userdata, &USERROLE))
							break;
					
					n++;
				}
			}
		}
	}
	if (responce)
		cJSON_free(responce);
	
	return n;
}

int
cyclients_user_permissions(const char *token,
                           int company_id,
                           int user_id,
													 void *userdata,
                           int (*callback)(void *userdata, 
                                     const CYCUserPermissions *permissions))
{
	int ret = 1;
	cJSON *responce;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/company/%d/users/%d/permissions", 
			URL, company_id, user_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(requestString,
									auth, "GET",
									NULL, &responce);
	
	if (http_code == 200){ // good
		if (cJSON_IsObject(responce))
		{
			cJSON *data = cJSON_GetObjectItem(responce, "data");
			if (cJSON_IsObject(data))
			{
				cJSON *user_permissions = cJSON_GetObjectItem(data, "user_permissions");
				if (user_permissions)
				{
				    memset(&USERPERMISSIONS, 0, sizeof(USERPERMISSIONS));
				    cyc_user_permissions_fr_json(&USERPERMISSIONS, user_permissions);
						ret = 0;
						if (callback)
							callback(userdata, &USERPERMISSIONS);
				}
			}
		}
	}
	
	if (responce)
		cJSON_free(responce);

	return ret;
}

char * 
user_permissions_json_with_slug_and_value_pairs(int nslug_and_value_pairs, ...)
{
	int i;
	char *slug, *value, *str;
	cJSON *json, *obj;
	va_list args;
	
	va_start(args, nslug_and_value_pairs);
	json = cJSON_CreateArray();
	if (json == NULL)
		return NULL;
	
	for (i=0; i<nslug_and_value_pairs; ++i) {
		slug = va_arg(args, char *);
		if (slug == NULL)
			break;
		value = va_arg(args, char *);
		if (value == NULL)
			break;
		
		obj = cJSON_CreateObject();
		if (obj == NULL)
			break;
		
		cJSON_AddStringToObject(obj, "slug", slug);
		cJSON_AddStringToObject(obj, "value", value);

		cJSON_AddItemToArray(json, obj);
	}
	va_end(args);
	
	str = cJSON_Print(json);
	cJSON_free(json);
	return str;
}

int
cyclients_user_copy_to_companies(const char *token,
                                 int company_id,
								                 int user_id,
								                 int nuser_user_company_links,
                                 struct user_company_link *links)
{
	int i;
	cJSON *post;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/company/%d/users/%d/copy_to_companies", 
			URL, company_id, user_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateArray();
	for (i=0; i<nuser_user_company_links; ++i) {
		if (links[i].user_permissions_json){
			cJSON *obj, *user_permissions;
			user_permissions = cJSON_Parse(links[i].user_permissions_json);
			if (cJSON_IsObject(user_permissions)){
				obj = cJSON_CreateObject();
				cJSON_AddNumberToObject(obj, "company_id", links[i].company_id);
				cJSON_AddItemToObject(obj, "user_permissions", user_permissions);
				cJSON_AddItemToArray(post, obj);
			}
		}
	}
	post_data = cJSON_Print(post);
	if (post_data == NULL){
		ERR("%s: can't generate post data", __FILE__);
		return 1;
	}	
	cJSON_free(post);
	
	http_code = curl_transport_exec(requestString,
									auth, "POST",
									post_data, NULL);
	free(post_data);

	if (http_code == 200)
		return 0;
	
	return 1;
}


