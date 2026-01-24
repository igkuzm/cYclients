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
	cJSON *post, *responce, *meta, *data, *obj;
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
			ERR("%s: can't generate post data", __FILE__);
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
	return current_count;    
    
}

int
cyclients_record_new (const char *token,
                      int company_id,
					  int staff_id,
                      const char *client_name,
                      const char *client_phone,
                      const char *datetime,
                      int nservices,
                      int *aservices,
					  int seance_length,
                      const char *comment,
					  const char *api_id,
                      int number_custom_fields_key_value_pairs,
                      ...)
{
        int i = 0, length = seance_length;
        cJSON *post, *client, *services, *custom_fields;
        char *phone_number;
        long http_code = 0;
        char requestString[BUFSIZ], auth[128], *post_data = NULL;
        char * SETUP_PARTNER_TOKEN(partner_token);
        
        assert(client_name);
        assert(client_phone);
        assert(datetime);

        phone_number = (char *)client_phone;
        if (*phone_number == '+') {
            phone_number++;
        }
        
        if (seance_length < 0)
            seance_length = 3600;
        
        sprintf(requestString, "%s/records/%d", 
                URL, company_id);
        sprintf(auth, "Authorization: Bearer %s, User %s"
                , partner_token, token);
        
        post = cJSON_CreateObject();
        cJSON_AddNumberToObject(post, "staff_id", staff_id);
        
        client = cJSON_CreateObject();
        cJSON_AddStringToObject(client, "name", client_name);
        cJSON_AddStringToObject(client, "phone_number", phone_number);
        cJSON_AddItemToObject(post, "client", client);
        
        cJSON_AddStringToObject(post, "datetime", datetime);
        
        services = cJSON_CreateArray();
        for (i = 0; i < nservices; i++) {
            cJSON *s = cJSON_CreateNumber(aservices[i]);
            cJSON_AddItemToArray(services, s);
        }
        cJSON_AddItemToObject(post, "services", services);
        
        cJSON_AddNumberToObject(post, "seance_length", seance_length);
    
        if (comment) {
            cJSON_AddStringToObject(post, "comment", comment);
        }    
        if (api_id) {
            cJSON_AddStringToObject(post, "api_id", api_id);
        }            
        if (number_custom_fields_key_value_pairs>0)
        {
            va_list args;
            va_start(args, number_custom_fields_key_value_pairs);
            custom_fields = cJSON_CreateObject();
            for (i=0; i<number_custom_fields_key_value_pairs; ++i) {
                char *key, *value;
                key = va_arg(args, char *);
                if (key == NULL)
                    break;
                value = va_arg(args, char *);
                if (value == NULL)
                    break;
                cJSON_AddStringToObject(custom_fields, key, value);
            }
            cJSON_AddItemToObject(post, "custom_fields", custom_fields);
        }
        
        post_data = cJSON_Print(post);
        cJSON_free(post);
        if (post_data == NULL){
            ERR("%s: can't generate post data", __FILE__);
            return 1;
        }	
        
        http_code = curl_transport_exec(requestString,
                                        auth, "POST",
                                        post_data, NULL);
        free(post_data);
        
        if (http_code == 201)
            return 0;
        
        return 1;
}

