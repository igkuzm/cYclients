#include "config.h"
#include "structs.h"
#include "cJSON.h"
#include "../partner_token.h"
#include "curl_transport.h"
#include <stdio.h>
#include <string.h>

static cyclients_service_t SERVICE;

int
cyclients_services(const char *token,
									 int company_id,
									 char *service_id,
									 void *userdata,
									 int (*callback)(void *userdata, 
																	 const cyclients_service_t *service))
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
		//if (cJSON_IsObject(json))
		//{
			//cJSON *data = cJSON_GetObjectItem(json, "data");
			//if (cJSON_IsArray(data))
			//{
				//int i = 0;
				//cJSON *company;
				//memset(&SERVICE, 0, sizeof(SERVICE));
				//cJSON_ArrayForEach(company, data)
				//{
					//cyclients_company_from_json(
							//company, &COMPANY);
					//if (callback)
						//if (callback(userdata, &COMPANY))
							//break;

					//i++;
				//}
				
				//return i;
			//}
		//}
	}
	
	return 0;
}
