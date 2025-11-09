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

static CYCService SERVICE;

CYCLIENTS_COUNTER
cyclients_services(const char *token,
		               int company_id,
									 void *userdata,
									 int (*callback)(void *userdata, 
										               const CYCService *service))
{
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/services", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_post(
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
				cJSON *service;
				cJSON_ArrayForEach(service, data)
				{
					memset(&SERVICE, 0, sizeof(SERVICE));
					cyc_service_fr_json(
							&SERVICE, service);
					if (callback)
						if (callback(userdata, &SERVICE))
							break;

					i++;
				}
				
				return i;
			}
		}
	}
	
	return 0;
}

CYCService *
cyclients_service_get(const char *token,
                      int company_id,
                      int service_id)
{
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/services/%d", 
			URL, company_id, service_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_post(
			requestString,
		 	auth, "GET",
		 	NULL, &json);

	if (http_code == 200){ // good
		if (cJSON_IsObject(json))
		{
			cJSON *data = cJSON_GetObjectItem(json, "data");
			if (cJSON_IsObject(data))
			{
				CYCService *service = NEW(CYCService);
				if (service){
					cyc_service_fr_json(
							service, data);
					return service;
				}
			}
		}
	}
	
	return NULL;
}

CYCService *
cyclients_service_new(const char *token,
                      int company_id,
                      const char *title,
                      int category_id,
                      double price_min,
                      double price_max,
                      int duration,
                      int technical_break_duration,
                      double discount,
                      const char *comment,
                      int weight,
                      CYCLIENTS_SERVICE_TYPE service_type,
                      const char *api_service_id,
											int nstaff,
											struct staff staff[])
{
	int i;
	cJSON *json = NULL, *astaff = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/services/%d", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);

	json = cJSON_CreateObject();
	astaff = cJSON_CreateArray();	

	if (title)
		cJSON_AddStringToObject(json, "title", title);
	cJSON_AddNumberToObject(json, "category_id", category_id);
	cJSON_AddNumberToObject(json, "price_min", price_min);
	cJSON_AddNumberToObject(json, "price_max", price_max);
	cJSON_AddNumberToObject(json, "duration", duration);
	if (technical_break_duration)
		cJSON_AddNumberToObject(json, "technical_break_duration", technical_break_duration);
	cJSON_AddNumberToObject(json, "discount", discount);
	if (comment)
		cJSON_AddStringToObject(json, "comment", comment);
	cJSON_AddNumberToObject(json, "weight", weight);
	cJSON_AddNumberToObject(json, "service_type", service_type);
	if (api_service_id)
		cJSON_AddStringToObject(json, "api_service_id", api_service_id);

	for (i = 0; i < nstaff; ++i) {
		cJSON *staff_obj = cJSON_CreateObject();
		cJSON_AddNumberToObject(
				staff_obj, "id", staff[i].id);
		cJSON_AddNumberToObject(
				staff_obj, "seance_length", staff[i].seance_length);
		cJSON_AddItemToArray(astaff, staff_obj);			
	}
	cJSON_AddItemToObject(json, "staff", astaff);

	post_data = cJSON_Print(json);
	if (post_data == NULL){
		ERR("%s: can't generate post data", __func__);
		return NULL;
	}
	cJSON_free(json);

	http_code = curl_transport_post(
			requestString,
		 	auth, "POST",
		 	cJSON_Print(json), &json);
	free(post_data);

	if (http_code == 201){ // created
		if (cJSON_IsObject(json))
		{
			cJSON *data = cJSON_GetObjectItem(json, "data");
			if (cJSON_IsObject(data))
			{
				CYCService *service = NEW(CYCService);
				if (service){
					cyc_service_fr_json(
							service, data);
					return service;
				}
			}
		}
	}

	return NULL;
}
