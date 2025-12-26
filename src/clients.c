#include "config.h"
#include "../cYclients.h"
#include "log.h"
#include "alloc.h"
#include "structs.h"
#include "cJSON.h"
#include "stb_ds.h"
#include "../partner_token.h"
#include "curl_transport.h"
#include "strtok_foreach.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#define PAGE_SIZE 100

static CYCFile CYCFILE;
static CYCVisit VISIT;

CYCLIENTS_COUNTER
cyclients_clients_search(const char *token,
                         int company_id,
                         const char *comma_separeted_fields_to_return,
                         const char *search_query,
                         void *userdata,
                         int (*callback)(void *userdata, 
                                         int nfields,
                                         const kvpair_t *fields))
{
	int npage = 0, total_count = 0, current_count = 0, 
			is_first_field = 1;
	cJSON *post, *fields, *filters, *filter, *state, 
				*meta, *data, *obj, *responce;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	assert(comma_separeted_fields_to_return);
    if (search_query == NULL)
        search_query = "";

	sprintf(requestString, "%s/company/%d/clients/search", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();
	cJSON_AddNumberToObject(post, "page", npage);
	cJSON_AddNumberToObject(post, "page_size", PAGE_SIZE);
	fields = cJSON_CreateArray();
	do {
		strtok_foreach(comma_separeted_fields_to_return, ",", field){
			if (field){
				cJSON *obj = cJSON_CreateString(field);
				if (is_first_field)
					cJSON_AddStringToObject(post, "order_by", field);
				is_first_field = 0;
				cJSON_AddItemToArray(fields, obj);
			}
		}
	} while(0);
	cJSON_AddItemToObject(post, "fields", fields);
	cJSON_AddStringToObject(post, "order_by_direction", "ASC");
	cJSON_AddStringToObject(post, "operation", "AND");
	filters = cJSON_CreateArray();
	filter = cJSON_CreateObject();
	cJSON_AddStringToObject(filter, "type", "quick_search");
	state = cJSON_CreateObject();
	cJSON_AddStringToObject(state, "value", search_query);
	cJSON_AddItemToObject(filter, "state", state);
	cJSON_AddItemToArray(filters, filter);
	cJSON_AddItemToObject(post, "filters", filters);
		
	do {
		responce = NULL;
	    post_data = cJSON_Print(post);
		if (post_data == NULL){
			ERR("%s: can't generate post data", __FILE__);
			return current_count;
		}	
		
	    http_code = curl_transport_exec(requestString,
									    auth, "POST",
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
				kvpair_t *client = NULL;
				cJSON *element, *item;
				cJSON_ArrayForEach(element, data)
				{
					if (cJSON_IsObject(element))
					{
						// make hashtable
						for (item = element->child;
								 item;
								 item = item->next)
						{
							if (cJSON_IsString(item))
								shput(client, item->string, item->valuestring);
							else if (cJSON_IsNumber(item))
								shput(client, item->string, STR("%d", item->valueint));
							else if (cJSON_IsBool(item))
								shput(client, item->string, STR("%d", item->valueint));
							/* TODO: ARAY and OBJECT <22-12-25, yourname> */
						}
					}
					if (callback)
						if (callback(userdata, shlen(client), client))
								break;
				}
				shfree(client);
			}

			cJSON_free(responce);
			responce = NULL;
		}
				
	} while (current_count < total_count);

	if (post)
		cJSON_free(post);
	return current_count;
}

int
cyclients_client_new(const char *token,
                     int company_id,
                     const char *name,
                     const char *surname,
                     const char *patronymic,
                     const char *phone,
                     const char *email,
                     const char *birth_date,
                     const char *comment,
                     int number_custom_fields_key_value_pairs,
                     ...)
{
    int i = 0;
    cJSON *post, *custom_fields;
    char *phone_number;
    long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);
    
    assert(name);
    assert(phone);
    
    phone_number = (char *)phone;
    if (*phone_number == '+') {
        phone_number++;
    }
        
    sprintf(requestString, "%s/clients/%d", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();
    cJSON_AddStringToObject(post, "name", name);
    if (surname) {
        cJSON_AddStringToObject(post, "surname", surname);
    }
    if (patronymic) {
        cJSON_AddStringToObject(post, "patronymic", patronymic);
    }
    cJSON_AddStringToObject(post, "phone", phone_number);
    if (email) {
        cJSON_AddStringToObject(post, "email", email);
    }
    if (birth_date) {
        cJSON_AddStringToObject(post, "birth_date", birth_date);
    }
    if (comment) {
        cJSON_AddStringToObject(post, "comment", comment);
    }    
    if (i>0)
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

CYCLIENTS_COUNTER
cyclients_client_files(const char *token,
                       int company_id,
                       int client_id,
                       void *userdata,
                       int (*callback)(void *userdata, 
                                       const CYCFile *file))
{
    CYCLIENTS_COUNTER n = 0;
    cJSON *responce;
    long http_code = 0;
    char requestString[BUFSIZ], auth[128];
    char * SETUP_PARTNER_TOKEN(partner_token);
    
    sprintf(requestString, "%s/company/%d/clients/files/%d", 
			URL, company_id, client_id);
    sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
    
    http_code = curl_transport_exec(requestString,
                                    auth, "GET",
                                    NULL, &responce);
    
    if (http_code == 200)
    {
        if (cJSON_IsObject(responce))
        {
            cJSON *data = cJSON_GetObjectItem(responce, "data");
            if (cJSON_IsArray(data))
            {
                cJSON *file;
                cJSON_ArrayForEach(file, data)
                {
                    memset(&CYCFILE, 0, sizeof(CYCFILE));
                    cyc_file_fr_json(&CYCFILE, file);
                    if (callback)
                        if (callback(userdata, &CYCFILE))
                            break;                       
                }
            }
        }
    }
    
    if(responce)
        cJSON_free(responce);

    return n;
}

int
cyclients_client_file_remove(const char *token,
                             int company_id,
                             int client_id,
														 int file_id)
{
    long http_code = 0;
    char requestString[BUFSIZ], auth[128];
    char * SETUP_PARTNER_TOKEN(partner_token);
    
    sprintf(requestString, "%s/company/%d/clients/files/%d/%d", 
			URL, company_id, client_id, file_id);
    sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
    
    http_code = curl_transport_exec(requestString,
                                    auth, "DELETE",
                                    NULL, NULL);
    
    if (http_code == 202)
			return 0;

		return 1;
}

CYCLIENTS_COUNTER
cyclients_client_visits(const char *token,
                       int company_id,
                       int client_id,
                       void *userdata,
                        int (*callback)(void *userdata, 
                                        const CYCVisit *visit))
{
    CYCLIENTS_COUNTER n = 0;
    cJSON *responce, *post, *from, *to;
    long http_code = 0;
    char requestString[BUFSIZ], auth[128], *post_data;
    char * SETUP_PARTNER_TOKEN(partner_token);
    
    sprintf(requestString, "%s/company/%d/clients/visits/search", 
			URL, company_id);
    sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);

		post = cJSON_CreateObject();
		cJSON_AddNumberToObject(post, "client_id", client_id);
		cJSON_AddNullToObject(post, "client_phone");
		cJSON_AddNullToObject(post, "from");
		cJSON_AddNullToObject(post, "to");
		cJSON_AddNullToObject(post, "payment_statuses");
		cJSON_AddNullToObject(post, "attendance");
	
		post_data = cJSON_Print(post);
    if (post_data == NULL){
        ERR("%s: %d: can't generate post data", __FILE__, __LINE__);
        return n;
    }	
		cJSON_free(post);
    
    http_code = curl_transport_exec(requestString,
                                    auth, "POST",
                                    post_data, &responce);
    
    if (http_code == 200)
    {
        if (cJSON_IsObject(responce))
        {
            cJSON *data = cJSON_GetObjectItem(responce, "data");
            if (cJSON_IsObject(data))
            {
                cJSON *records = cJSON_GetObjectItem(data, "records");
                if (cJSON_IsArray(records))
                {
                    cJSON *visit;
                    cJSON_ArrayForEach(visit, records)
                    {
                        memset(&VISIT, 0, sizeof(VISIT));
                        cyc_visit_fr_json(&VISIT, visit);
                        if (callback)
                            if (callback(userdata, &VISIT))
                                break;                       
                    }
                }
            }
        }
    }
    
    if(responce)
        cJSON_free(responce);

    return n;
}


