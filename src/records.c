#include "log.h"
#include "alloc.h"
#include "structs.h"
#include "cJSON.h"
#include "../partner_token.h"
#include "../cYclients.h"
#include "curl_transport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#define PAGE_SIZE 50

static CYCRecord RECORD;

CYCLIENTS_COUNTER
cyclients_records(const char *token,
                  int company_id,
                  const char *start_date,
                  const char *end_date,
                  void *userdata,
                  int (*callback)(void *userdata, 
                                  const CYCRecord *record))
{
  int npage = 0, total_count = 0, current_count = 0, exit_loop = 0, 
      is_first_field = 1;
	cJSON *post, *responce = NULL, *meta, *data, *obj;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);
    
	sprintf(requestString, "%s/records/%d", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();
	cJSON_AddNumberToObject(post, "page", npage);
	cJSON_AddNumberToObject(post, "count", PAGE_SIZE);
    cJSON_AddBoolToObject(post, "with_deleted", true);
    if (start_date)
        cJSON_AddStringToObject(post, "start_date", start_date);
    if (end_date)
        cJSON_AddStringToObject(post, "end_date", end_date);
	
	do {
		responce = NULL;
	    post_data = cJSON_Print(post);
		if (post_data == NULL){
			ERR("%s", "can't generate post data");
			return current_count;
		}	
		
	    http_code = curl_transport_exec(requestString,
									    auth, "GET",
									    post_data, &responce);
		free(post_data);
        
		// iterate page
		npage++;
		cJSON_ReplaceItemInObject(post, "page", cJSON_CreateNumber(npage));
		
		if (http_code != 200)
			break;
		
		if (cJSON_IsObject(responce))
		{
			
			meta = cJSON_GetObjectItem(responce, "meta");
			if (meta == NULL)
				break;
			
			data = cJSON_GetObjectItem(responce, "data");
			if (data == NULL)
				break;
			
			obj = cJSON_GetObjectItem(meta, "total_count");
			if (obj == NULL)
				break;
			
			total_count = (int)cJSON_GetNumberValue(obj);
			current_count += cJSON_GetArraySize(data);
            
			if (cJSON_IsArray(data))
			{
				cJSON *record;
				cJSON_ArrayForEach(record, data)
				{
                    memset(&RECORD, 0, sizeof(RECORD));
                    cyc_record_fr_json(&RECORD, record);
					if (callback)
						if (callback(userdata, &RECORD))
                            exit_loop = 1;
                    if (exit_loop)
                        break;
				}
			}
            
			cJSON_free(responce);
			responce = NULL;
		}
        
	} while (exit_loop == 0 && current_count < total_count);
    
	if (post)
		cJSON_free(post);
	if (responce)
		cJSON_free(responce);
	
	return current_count;    
}

CYCLIENTS_ID
cyclients_record_new(const char *token,
                     int company_id,
					           int staff_id,
                     const char *client_name,
                     const char *client_phone,
                     const char *datetime,
					           int seance_length,
                     int number_of_key_value_pairs,
                     ...)
{
	int i = 0, k, length = seance_length, record_id = 0;
	cJSON *post, *client, *custom_fields, *responce = NULL, *data;
	char *phone_number;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	va_list args;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	assert(client_name);
	assert(client_phone);
	assert(datetime);

	phone_number = (char *)client_phone;
	if (*phone_number == '+') {
		phone_number++;
	}
	
	if (seance_length < 1)
		seance_length = 3600;
	
	sprintf(requestString, "%s/records/%d", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();
	cJSON_AddNumberToObject(post, "staff_id", staff_id);
	client = cJSON_CreateObject();
	cJSON_AddStringToObject(client, "name", client_name);
	cJSON_AddStringToObject(client, "phone", phone_number);
	cJSON_AddItemToObject(post, "client", client);
	
	cJSON_AddStringToObject(post, "datetime", datetime);
	
	cJSON_AddNumberToObject(post, "seance_length", seance_length);

	va_start(args, number_of_key_value_pairs);
	custom_fields = cJSON_CreateObject();
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
    fields = (struct default_field *)record_fields; 
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
	cJSON_free(post);
	if (post_data == NULL){
		ERR("%s", "can't generate post data");
		return record_id;
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
				record_id = id->valueint;
			}
		}
	}

	if(responce)
		cJSON_free(responce);
	
	return record_id;
}

int
cyclients_record_get(const char *token,
                     int company_id,
                     int record_id,
										 void *userdata,
                     int (*callback)(void *userdata, 
                                     const CYCRecord *record))
{
	int ret = 1;
	cJSON *responce = NULL, *data;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);
    
	sprintf(requestString, "%s/record/%d/%d", 
			URL, company_id, record_id);
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
			if (cJSON_IsObject(data))
			{
        memset(&RECORD, 0, sizeof(RECORD));
        cyc_record_fr_json(&RECORD, data);
				ret = 0;	
				if (callback)
					callback(userdata, &RECORD);
			}
		}
	}
		
	if (responce)
		cJSON_free(responce);
	
	return ret;
}

int
cyclients_record_set(const char *token,
                     int company_id,
					           int record_id,
                     int number_of_key_value_pairs,
                     ...)
{
	int i, k, ret = 1;
	cJSON *post, *custom_fields;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	va_list args;
	char * SETUP_PARTNER_TOKEN(partner_token);

	assert(number_of_key_value_pairs > 0);
	
	sprintf(requestString, "%s/record/%d/%d", 
			URL, company_id, record_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();

	va_start(args, number_of_key_value_pairs);
	custom_fields = cJSON_CreateObject();
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
    fields = (struct default_field *)record_fields; 
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
cyclients_record_remove(const char *token,
                        int company_id,
					              int record_id)
{
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/record/%d/%d", 
			URL, company_id, record_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
		, partner_token, token);
	
	http_code = curl_transport_exec(requestString,
																	auth, "DELETE",
																	NULL, NULL);
	
	if (http_code == 204)
		return 0;
	
	return http_code;
}


