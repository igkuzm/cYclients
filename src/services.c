#include "config.h"
#include "structs.h"
#include "cJSON.h"
#include "../partner_token.h"
#include "curl_transport.h"
#include <stdio.h>
#include <string.h>

static CYCService SERVICE;

int
cyclients_services(const char *token,
		               int company_id,
									 char *service_id,
									 void *userdata,
									 int (*callback)(void *userdata, 
										               const CYCService *service))
{
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/services/%s", 
			URL, company_id, service_id?service_id:"");
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
			// only one item
			if (cJSON_IsObject(data))
			{
				memset(&SERVICE, 0, sizeof(SERVICE));
				cyc_service_fr_json(
						&SERVICE, data);
				if (callback)
					callback(userdata, &SERVICE);
				return 1;
			}
			// array of items
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
