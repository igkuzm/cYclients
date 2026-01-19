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

#define PAGE_SIZE 100

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
    int npage = 0, total_count = 0, current_count = 0, 
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
    cJSON_AddBooToObject(post, "with_deleted", true);
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
				//kvpair_t *client = NULL;
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
							/* TODO: ARAY and OBJECT <22-12-25, yourname> */
						}
					}
					//if (callback)
//						if (callback(userdata, shlen(client), client))
//                            break;
				}
				//shfree(client);
			}
            
			cJSON_free(responce);
			responce = NULL;
		}
        
	} while (current_count < total_count);
    
	if (post)
		cJSON_free(post);
	return current_count;    
    
}
