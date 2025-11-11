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
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/service_categories", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(
			requestString,
		 	auth, "GET",
		 	NULL, &json);

	if (http_code == 200){ // good
		if (cJSON_IsObject(json))
		{
			cJSON *data = cJSON_GetObjectItem(json, "data");
			if (cJSON_IsArray(data))
			{
				int i = 0;
				cJSON *category;
				cJSON_ArrayForEach(category, data)
				{
					memset(&CATEGORY, 0, sizeof(CATEGORY));
					cyc_service_category_fr_json(
							&CATEGORY, category);
					if (callback)
						if (callback(userdata, &CATEGORY))
							break;

					i++;
				}
				
				return i;
			}
		}
	}
	
	return 0;
}

CYCServiceCategory *
cyclients_service_category_get(const char *token,
                               int company_id,
                               int category_id)
{
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/service_categories/%d", 
			URL, company_id, category_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(
			requestString,
		 	auth, "GET",
		 	NULL, &json);

	if (http_code == 200){ // good
		if (cJSON_IsObject(json))
		{
			cJSON *data = cJSON_GetObjectItem(json, "data");
			if (cJSON_IsObject(data))
			{
				CYCServiceCategory *category = NEW(CYCServiceCategory);
				if (category){
					cyc_service_category_fr_json(
							category, data);
					return category;
				}
			}
		}
	}
	
	return NULL;
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
	cJSON *json = NULL, *staff = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/service_categories/%d/%d", 
			URL, company_id, category_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	json = cJSON_CreateObject();
	staff = cJSON_CreateArray();	
	
	if (title)
		cJSON_AddStringToObject(json, "title", title);
	if (api_id)
		cJSON_AddStringToObject(json, "api_id", api_id);
	cJSON_AddNumberToObject(json, "weight", weight);
	staff = cJSON_CreateIntArray(astaff,nstaff);
	cJSON_AddItemToObject(json, "staff", staff);
	
	post_data = cJSON_Print(json);
	if (post_data == NULL){
		ERR("%s: can't generate post data", __func__);
		return 1;
	}
	cJSON_free(json);
	
	http_code = curl_transport_exec(
									requestString,
									auth, "PUT",
									post_data, NULL);
	free(post_data);
	
	if (http_code == 200){ // good
		return 0;
	}
	
	return 1;	
}

CYCServiceCategory *
cyclients_service_category_new(const char *token,
							   int company_id,
							   const char *title,
							   const char *api_id,
							   int weight,
							   int nstaff,
							   int astaff[])
{
	cJSON *json = NULL, *staff = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/service_categories/%d", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	json = cJSON_CreateObject();
	staff = cJSON_CreateArray();	
	
	if (title)
		cJSON_AddStringToObject(json, "title", title);
	if (api_id)
		cJSON_AddStringToObject(json, "api_id", api_id);
	cJSON_AddNumberToObject(json, "weight", weight);
	staff = cJSON_CreateIntArray(astaff,nstaff);
	cJSON_AddItemToObject(json, "staff", staff);
	
	post_data = cJSON_Print(json);
	if (post_data == NULL){
		ERR("%s: can't generate post data", __func__);
		return NULL;
	}
	cJSON_free(json);
	
	http_code = curl_transport_exec(
									requestString,
									auth, "POST",
									post_data, &json);
	free(post_data);
	
	if (http_code == 201){ // created
		if (cJSON_IsObject(json))
		{
			cJSON *data = cJSON_GetObjectItem(json, "data");
			if (cJSON_IsObject(data))
			{
				CYCServiceCategory *category = NEW(CYCServiceCategory);
				if (category){
					cyc_service_category_fr_json(
												 category, data);
					return category;
				}
			}
		}
	}
	
	return NULL;	
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
	
	http_code = curl_transport_exec(
									requestString,
									auth, "DELETE",
									NULL, NULL);
	if (http_code == 204){ // deleted
		return 0;
	}
	
	return 1;
}
