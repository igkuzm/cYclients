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

#define PAGE_SIZE 25

CYCLIENTS_COUNTER
cyclients_clients_search(const char *token,
                         int company_id,
						 const char *comma_separeted_fields_to_return,
						 const char *search_query,
                         void *userdata,
                         int (*callback)(void *userdata, 
                                         const void *client))
{
	int page = 0, total_count = 0, current_count = 0, is_first_field = 1;
	cJSON *json = NULL, *fields, *filters, *filter, *state, *meta, *data, *obj;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	assert(comma_separeted_fields_to_return);
	assert(search_query);

	sprintf(requestString, "%s/company/%d/clients/search", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	do {
	    json = cJSON_CreateObject();
	    cJSON_AddNumberToObject(json, "page", page);
	    cJSON_AddNumberToObject(json, "page_size", PAGE_SIZE);
	    fields = cJSON_CreateArray();
	    strtok_foreach(comma_separeted_fields_to_return, ",", field){
		    if (field){
			    cJSON *obj = cJSON_CreateString(field);
			    if (is_first_field)
			        cJSON_AddStringToObject(json, "order_by", field);
			    is_first_field = 0;
			    cJSON_AddItemToArray(fields, obj);
		    }
	    }
        cJSON_AddItemToObject(json, "fields", fields);
	    cJSON_AddStringToObject(json, "order_by_direction", "ASC");
	    cJSON_AddStringToObject(json, "operation", "AND");
	    filters = cJSON_CreateArray();
	    filter = cJSON_CreateObject();
	    cJSON_AddStringToObject(filter, "type", "quick_search");
	    state = cJSON_CreateObject();
	    cJSON_AddStringToObject(state, "value", search_query);
	    cJSON_AddItemToObject(filter, "state", state);
	    cJSON_AddItemToArray(filters, filter);
	    cJSON_AddItemToObject(json, "filters", filters);
		
	    post_data = cJSON_Print(json);
	    cJSON_free(json);
	    json = NULL;
	
	    http_code = curl_transport_exec(requestString,
									    auth, "POST",
									    post_data, &json);
		// iterate page
		page++;
		
		if(post_data)
			free(post_data);
		
		if (http_code != 200)
			break;
		
		if (json == NULL)
			break;
		
		meta = cJSON_GetObjectItem(json, "meta");
		if (meta == NULL)
			break;
		obj = cJSON_GetObjectItem(meta, "total_count");
		if (obj)
			total_count = (int)cJSON_GetNumberValue(obj);
		
		data = cJSON_GetObjectItem(json, "data");
		if (data == NULL)
			break;
		
		current_count += cJSON_GetArraySize(data);

		cJSON_free(json);
		json = NULL;
				
	} while (current_count < total_count);

	return 0;
}
