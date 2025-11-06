#include "config.h"
#include "structs.h"
#include "cJSON.h"
#include "../partner_token.h"
#include "curl_transport.h"
#include <stdio.h>
#include <string.h>

static cyclients_company_t COMPANY;

int
cyclients_companies(const char *token,
										void *userdata,
										int (*callback)(void *userdata, 
																		const cyclients_company_t *company))
{
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/companies?my=1", URL);
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
			if (cJSON_IsArray(data))
			{
				int i = 0;
				cJSON *company;
				memset(&COMPANY, 0, sizeof(COMPANY));
				cJSON_ArrayForEach(company, data)
				{
					cyclients_company_from_json(
							company, &COMPANY);
					if (callback)
						if (callback(userdata, &COMPANY))
							break;

					i++;
				}
				
				return i;
			}
		}
	}
	
	return 0;
}
