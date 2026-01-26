#include "../cYclients.h"
#include "config.h"
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

static CYCServiceCategory CATEGORY;

CYCLIENTS_COUNTER
cyclients_service_categories(const char *token,
                             int company_id,
                             void *userdata,
                             int (*callback)(void *userdata, 
                                             const CYCServiceCategory *category))
{
	CYCLIENTS_COUNTER n = 0;
	cJSON *responce = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/service_categories", 
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
				cJSON *category;
				cJSON_ArrayForEach(category, data)
				{
					memset(&CATEGORY, 0, sizeof(CATEGORY));
					cyc_service_category_fr_json(&CATEGORY, category);
					if (callback)
						if (callback(userdata, &CATEGORY))
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
cyclients_service_category_get(const char *token,
                               int company_id,
                               int category_id,
                               void *userdata,
                               int (*callback)(void *userdata, 
                                               const CYCServiceCategory *category))
{
	int ret = 1;
	cJSON *responce = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/service_categories/%d", 
			URL, company_id, category_id);
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
				memset(&CATEGORY, 0, sizeof(CATEGORY));
				cyc_service_category_fr_json(&CATEGORY, data);
				ret = 0;
				if (callback)
					callback(userdata, &CATEGORY);
			}
		}
	}
	if (responce)
		cJSON_free(responce);

	return ret;
}

int
cyclients_service_category_update(const char *token,
							      int company_id,
								  int category_id,
								  const char *title,
							      const char *api_id,
							      int weight,
							      int nstaff,
							      int astaff[])
{
	cJSON *post, *staff;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/service_categories/%d/%d", 
			URL, company_id, category_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();
	staff = cJSON_CreateArray();	
	
	if (title)
		cJSON_AddStringToObject(post, "title", title);
	if (api_id)
		cJSON_AddStringToObject(post, "api_id", api_id);
	cJSON_AddNumberToObject(post, "weight", weight);
	staff = cJSON_CreateIntArray(astaff,nstaff);
	cJSON_AddItemToObject(post, "staff", staff);
	
	post_data = cJSON_Print(post);
	if (post_data == NULL){
		ERR("%s", "can't generate post data");
		return 1;
	}
	cJSON_free(post);
	
	http_code = curl_transport_exec(requestString,
									auth, "PUT",
									post_data, NULL);
	free(post_data);
	
	if (http_code == 200){ // good
		return 0;
	}
	
	return 1;	
}

CYCLIENTS_ID
cyclients_service_category_new(const char *token,
							                 int company_id,
							                 const char *title,
							                 const char *api_id,
							                 int weight,
							                 int nstaff,
							                 int astaff[])
{
	int service_category_id = 0;
	CYCServiceCategory *category = NULL;
	cJSON *post, *responce = NULL, *staff;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/service_categories/%d", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();
	staff = cJSON_CreateArray();	
	
	if (title)
		cJSON_AddStringToObject(post, "title", title);
	if (api_id)
		cJSON_AddStringToObject(post, "api_id", api_id);
	cJSON_AddNumberToObject(post, "weight", weight);
	staff = cJSON_CreateIntArray(astaff,nstaff);
	cJSON_AddItemToObject(post, "staff", staff);
	
	post_data = cJSON_Print(post);
	if (post_data == NULL){
		ERR("%s", "can't generate post data");
		return service_category_id;
	}
	cJSON_free(post);
	
	http_code = curl_transport_exec(requestString,
									auth, "POST",
									post_data, &responce);
	free(post_data);
	
	if (http_code == 201){ // created
		if (cJSON_IsObject(responce))
		{
			cJSON *data = cJSON_GetObjectItem(responce, "data");
			if (cJSON_IsObject(data))
			{
				cJSON *id = cJSON_GetObjectItem(data, "id");
				if (id)
					service_category_id = id->valueint;
			}
		}
	}
	if (responce)
		cJSON_free(responce);
	return service_category_id;	
}

int
cyclients_service_category_delete(const char *token,
							      int company_id,
								  int category_id)
{
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/service_categories/%d/%d", 
			URL, company_id, category_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(requestString,
									auth, "DELETE",
									NULL, NULL);
	if (http_code == 204){ // deleted
		return 0;
	}
	
	return 1;
}
