#include "config.h"
#include "../cYclients.h"
#include "log.h"
#include "alloc.h"
#include "structs.h"
#include "cJSON.h"
#include "../partner_token.h"
#include "curl_transport.h"
#include "strtok_foreach.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#define PAGE_SIZE 100

CYCLIENTS_COUNTER
cyclients_clients_search(const char *token,
                         int company_id,
						 const char *comma_separeted_fields_to_return,
						 const char *search_query,
                         void *userdata,
                         int (*callback)(void *userdata, 
                                         const void *client))
{
	int npage = 0, total_count = 0, current_count = 0, is_first_field = 1;
	cJSON *post, *page, *fields, *filters, *filter, *state, *meta, *data, *obj, *responce;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	assert(comma_separeted_fields_to_return);
	assert(search_query);

	sprintf(requestString, "%s/company/%d/clients/search", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	post = cJSON_CreateObject();
	cJSON_AddNumberToObject(post, "page", npage);
	cJSON_AddNumberToObject(post, "page_size", PAGE_SIZE);
	fields = cJSON_CreateArray();
	strtok_foreach(comma_separeted_fields_to_return, ",", field){
		if (field){
			cJSON *obj = cJSON_CreateString(field);
			if (is_first_field)
				cJSON_AddStringToObject(post, "order_by", field);
			is_first_field = 0;
			cJSON_AddItemToArray(fields, obj);
		}
	}
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
			ERR("%s: can't generate post data", __func__);
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

			cJSON_free(responce);
			responce = NULL;
		}
				
	} while (current_count < total_count);

	if (post)
		cJSON_free(post);
	return current_count;
}
