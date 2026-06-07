#include "log.h"
#include "alloc.h"
#include "structs.h"
#include "cJSON.h"
#include <partner_token.h>
#include "../cYclients.h"
#include "curl_transport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

static CYCCustomField CUSTOM_FIELD;

CYCLIENTS_COUNTER
cyclients_custom_fields(const char *token,
                        CYCLIENTS_CATEGORY_TYPE category,
                        int company_id,
                        void *userdata,
                        int (*callback)(void *userdata, 
                                        const CYCCustomField *field))
{
  int count = 0;
	cJSON *responce = NULL, *data;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);
    
	sprintf(requestString, "%s/custom_fields/%s/%d", 
			URL, 
			category == CYCLIENTS_CATEGORY_CLIENT?"client":"record",
		 	company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(requestString,
									auth, "GET",
									NULL, &responce);
			
	if (http_code == 200)
	{
		if (cJSON_IsObject(responce))
		{
			data = cJSON_GetObjectItem(responce, "data");
			if (cJSON_IsArray(data))
			{
				cJSON *element;
				cJSON_ArrayForEach(element, data)
				{
					cJSON *custom_field = 
						cJSON_GetObjectItem(element, "custom_field");
					if (cJSON_IsObject(custom_field))
					{
						memset(&CUSTOM_FIELD, 0, sizeof(CUSTOM_FIELD));
						cyc_custom_field_fr_json(&CUSTOM_FIELD, custom_field);
						count++;
						if (callback)
							if (callback(userdata, &CUSTOM_FIELD))
								break;
					}
				}
			}
						
		}
	}
        
	if (responce)
		cJSON_free(responce);
	
	return count;    
}

CYCLIENTS_ID
cyclients_custom_field_new(const char *token,
						   CYCLIENTS_CATEGORY_TYPE category,
						   int company_id,
						   const char *type,
						   const char *code,
						   const char *title,
						   bool user_can_edit,
						   bool show_in_ui)
{
	int custom_field_id = 0;
	cJSON *post, *responce = NULL, *data;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	assert(type);
	assert(code);
	assert(title);

	sprintf(requestString, "%s/custom_fields/%s/%d", 
			URL, 
			category == CYCLIENTS_CATEGORY_CLIENT?"client":"record",
		 	company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();
	cJSON_AddStringToObject(post, "type", type);
	cJSON_AddStringToObject(post, "code", code);
	cJSON_AddStringToObject(post, "title", title);
	cJSON_AddBoolToObject(post, "user_can_edit", user_can_edit);
	cJSON_AddBoolToObject(post, "show_in_ui", show_in_ui);

	post_data = cJSON_Print(post);
	cJSON_free(post);
	if (post_data == NULL){
		ERR("%s", "can't generate post data");
		return custom_field_id;
	}	
	
	http_code = curl_transport_exec(requestString,
									auth, "POST",
									post_data, &responce);
	free(post_data);
	
	if (http_code == 201)
	{
		if (cJSON_IsObject(responce))
		{
			data = cJSON_GetObjectItem(responce, "data");
			if (cJSON_IsObject(data))
			{
				cJSON *id = cJSON_GetObjectItem(data, "id");
				custom_field_id = id->valueint;
			}
		}
	}

	if(responce)
		cJSON_free(responce);
	
	return custom_field_id;
}

int
cyclients_custom_field_set(const char *token,
                           CYCLIENTS_CATEGORY_TYPE category,
                           int company_id,
                           int field_id,
                           int number_of_key_value_pairs,
                           ...)
{
	int i, k, ret = 1;
	cJSON *post;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	va_list args;
	char * SETUP_PARTNER_TOKEN(partner_token);

	assert(number_of_key_value_pairs > 0);
	
	sprintf(requestString, "%s/custom_fields/%s/%d", 
			URL, 
			category == CYCLIENTS_CATEGORY_CLIENT?"client":"record",
		 	company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();

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
    fields = (struct default_field *)custom_fields; 
		for (k=0; fields[k].name; ++k)
		{
			if (strcmp(key, fields[i].name) == 0)
			{
				// this is default field
				cJSON *item = json_from_default_field(
						&fields[k], value);
		    cJSON_AddItemToObject(post, key, item);
			}
		}
	}
	va_end(args);
	
	post_data = cJSON_Print(post);
	cJSON_free(post);
	if (post_data == NULL){
		ERR("%s", "can't generate post data");
		return ret;
	}	
	
	http_code = curl_transport_exec(requestString,
									auth, "PUT",
									post_data, NULL);
	free(post_data);
	
	if (http_code == 201)
		ret = 0;
	
	return ret;
}

int
cyclients_custom_field_remove(const char *token,
                              CYCLIENTS_CATEGORY_TYPE category,
                              int company_id,
                              int field_id)
{
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/custom_fields/%s/%d/%d", 
			URL, 
			category == CYCLIENTS_CATEGORY_CLIENT?"client":"record",
		 	company_id, field_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
		, partner_token, token);
	
	http_code = curl_transport_exec(requestString,
																	auth, "DELETE",
																	NULL, NULL);
	
	if (http_code == 204)
		return 0;
	
	return http_code;
}
