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
	CYCLIENTS_COUNTER n = 0;
	cJSON *responce = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/services", 
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
				cJSON *service;
				cJSON_ArrayForEach(service, data)
				{
					memset(&SERVICE, 0, sizeof(SERVICE));
					cyc_service_fr_json(
							&SERVICE, service);
					if (callback)
						if (callback(userdata, &SERVICE))
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
cyclients_service_get(const char *token,
                      int company_id,
                      int service_id,
                      void *userdata,
                      int (*callback)(void *userdata, 
                                      const CYCService *service))
{
	int ret = 1;
	cJSON *responce = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/services/%d", 
			URL, company_id, service_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(requestString,
		 	                        auth, "GET",
		 	                        NULL, &responce);

	ret = http_code;

	if (http_code == 200){ // good
		if (cJSON_IsObject(responce))
		{
			cJSON *data = cJSON_GetObjectItem(responce, "data");
			if (cJSON_IsObject(data))
			{
				memset(&SERVICE, 0, sizeof(SERVICE));
				cyc_service_fr_json(&SERVICE, data);
				ret = 0;
				if (callback)
					callback(userdata, &SERVICE);
			}
		}
	}
	if (responce)
		cJSON_free(responce);

	return ret;
}

CYCLIENTS_ID
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
                      const char *staff_json)
{
	int service_id = 0;
	CYCService *service = NULL;
	cJSON *responce = NULL, *astaff, *post;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/services/%d", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);

	post = cJSON_CreateObject();
	astaff = cJSON_CreateArray();	

	if (title)
		cJSON_AddStringToObject(post, "title", title);
	cJSON_AddNumberToObject(post, "category_id", category_id);
	cJSON_AddNumberToObject(post, "price_min", price_min);
	cJSON_AddNumberToObject(post, "price_max", price_max);
	cJSON_AddNumberToObject(post, "duration", duration);
	if (technical_break_duration)
		cJSON_AddNumberToObject(post, "technical_break_duration", technical_break_duration);
	cJSON_AddNumberToObject(post, "discount", discount);
	if (comment)
		cJSON_AddStringToObject(post, "comment", comment);
	cJSON_AddNumberToObject(post, "weight", weight);
	cJSON_AddNumberToObject(post, "service_type", service_type);
	if (api_service_id)
		cJSON_AddStringToObject(post, "api_service_id", api_service_id);

	cJSON_AddItemToObject(post, "staff", cJSON_Parse(staff_json));

	post_data = cJSON_Print(post);
	if (post_data == NULL){
		ERR("%s", "can't generate post data");
		return 0;
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
					service_id = id->valueint;
			}
		}
	}
	if (responce)
		cJSON_free(responce);

	return service_id;
}

int
cyclients_service_set(const char *token,
                      int company_id,
                      int service_id,
                      int number_of_key_value_pairs,
                      ...)
{
	int i, k;
	cJSON *post, *custom_fields;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	va_list args;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	assert(number_of_key_value_pairs > 0);

	sprintf(requestString, "%s/company/%d/services/%d"
			,URL, company_id, service_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);

	post = cJSON_CreateObject();
	custom_fields = cJSON_CreateObject();
	va_start(args, number_of_key_value_pairs);
	for (i=0; i<number_of_key_value_pairs; ++i) 
	{
		char *key, *value;
		struct default_field *fields; 

		key = va_arg(args, char *);
		if (key == NULL)
			break;
		value = va_arg(args, char *);
		if (value == NULL)
			break;

		// check if key is in default fields
		fields = (struct default_field *)service_fields; 
		for (k=0; fields[k].name; ++k)
		{
			if (strcmp(key, fields[i].name) == 0)
			{
				// this is default field
				cJSON *item = json_from_default_field(
						&fields[k], value);
				cJSON_AddItemToObject(post, key, item);
			} else {
				// this is custom field
				cJSON_AddStringToObject(
						custom_fields, key, value);
			}
		}
	}
	va_end(args);
	cJSON_AddItemToObject(
		post, "custom_fields", custom_fields);

	post_data = cJSON_Print(post);
	if (post_data == NULL){
		ERR("%s", "can't generate post data");
		return 1;
	}
	cJSON_free(post);

	http_code = curl_transport_exec(requestString,
                                    auth, "PATCH",
									post_data, NULL);
	free(post_data);

	if (http_code == 200){ // updated
		return 0; 
	}

	return 1;
}

int
cyclients_service_remove(const char *token,
                         int company_id,
                         int service_id)
{
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/services/%d/%d", 
			URL, company_id, service_id);
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

int
cyclients_service_set_links(const char *token,
                            int company_id,
							              int service_id,
                            int nmaster_configs,
							              struct master_cofig master_cofigs[],
                            int nresources,
							              int resources[],
                            int ntranslations,
							              struct translation translations[])
{
	int i;
	cJSON *obj, *post, 
          *master_settings, 
          *resource_ids,
          *array_translations;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/services/links"
			,URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);

	obj = cJSON_CreateObject();
	master_settings = cJSON_CreateArray();
	cJSON_AddNumberToObject(obj, "service_id", service_id);
	for (i = 0; i < nmaster_configs; ++i) {
		cJSON *price = cJSON_CreateObject();
		cJSON *setting = cJSON_CreateObject();		
		cJSON_AddNumberToObject(setting, "master_id", master_cofigs[i].master_id);
		cJSON_AddNumberToObject(setting, "technological_card_id", master_cofigs[i].technological_card_id);
		cJSON_AddNumberToObject(setting, "hours", master_cofigs[i].hours);
		cJSON_AddNumberToObject(setting, "minutes", master_cofigs[i].minutes);			
		cJSON_AddNumberToObject(price, "min", master_cofigs[i].price.min);
		cJSON_AddNumberToObject(price, "max", master_cofigs[i].price.max);
		cJSON_AddItemToObject(setting, "price", price);
		cJSON_AddItemToArray(master_settings, setting);
	}
	cJSON_AddItemToObject(obj, "master_settings", master_settings);

	resource_ids = cJSON_CreateIntArray(resources, nresources);
	cJSON_AddItemToObject(obj, "resource_ids", resource_ids);

	array_translations = cJSON_CreateArray();
	for (i = 0; i < ntranslations; ++i){
		cJSON *translation = cJSON_CreateObject();
		cJSON_AddNumberToObject(translation, "language_id", translations[i].language_id);
		cJSON_AddStringToObject(translation, "translation", translations[i].translation);
		cJSON_AddItemToArray(array_translations, translation);
	} 
	cJSON_AddItemToObject(obj, "translations", array_translations);

	post = cJSON_CreateArray();
	cJSON_AddItemToArray(post, obj);
	
	post_data = cJSON_Print(post);
	if (post_data == NULL){
		ERR("%s", "can't generate post data");
		return 1;
	}	
	cJSON_free(post);

	http_code = curl_transport_exec(requestString,
                                    auth, "POST",
                                    post_data, NULL);
	free(post_data);

	if (http_code == 201){
		return 0; 
	}

	return 1;
}

int
cyclients_service_set_staff(const char *token,
                            int company_id,
                            int service_id,
						                int master_id,
                            int seance_length,
                            int technological_card_id)
{
	cJSON *post;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/company/%d/services/%d/staff"
			,URL, company_id, service_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();
	cJSON_AddNumberToObject(post, "master_id", master_id);
	cJSON_AddNumberToObject(post, "seance_length", seance_length);
	cJSON_AddNumberToObject(post, "technological_card_id", technological_card_id);
	
	post_data = cJSON_Print(post);
	if (post_data == NULL){
		ERR("%s", "can't generate post data");
		return 1;
	}	
	cJSON_free(post);
	
	http_code = curl_transport_exec(requestString,
									auth, "POST",
									post_data, NULL);
	free(post_data);
	
	if (http_code == 201){
		return 0; 
	}
	
	return 1;	
}

int
cyclients_service_update_staff(const char *token,
                               int company_id,
                               int service_id,
						                   int master_id,
                               int seance_length,
                               int technological_card_id)
{
	cJSON *post;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/company/%d/services/%d/staff/%d"
			,URL, company_id, service_id, master_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();
	cJSON_AddNumberToObject(post, "seance_length", seance_length);
	cJSON_AddNumberToObject(post, "technological_card_id", technological_card_id);
	
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
	
	if (http_code == 200){
		return 0; 
	}
	
	return 1;	
}

int
cyclients_service_delete_staff(const char *token,
                               int company_id,
                               int service_id,
						       int master_id)
{
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/company/%d/services/%d/staff/%d"
			,URL, company_id, service_id, master_id);
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

