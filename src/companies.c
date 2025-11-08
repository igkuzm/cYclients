#include "config.h"
#include "structs.h"
#include "cJSON.h"
#include "../partner_token.h"
#include "curl_transport.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static CYCCompany COMPANY;

int
cyclients_companies(const char *token,
		                char *company_id,
										void *userdata,
										int (*callback)(void *userdata, 
											              const CYCCompany *company))
{
	int count = 0;
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], company_id_req[16];
	char * SETUP_PARTNER_TOKEN(partner_token);

	assert(token);

	sprintf(company_id_req, "&id=%s", company_id);
	sprintf(requestString, "%s/companies?my=1%s", 
			URL, company_id?company_id_req:"");
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
				cJSON *company;
				memset(&COMPANY, 0, sizeof(COMPANY));
				cJSON_ArrayForEach(company, data)
				{
					cyc_company_fr_json(
							&COMPANY, company);
					if (callback)
						if (callback(userdata, &COMPANY))
							break;

					count++;
				}
			}
		}
	}
	
	cJSON_free(json);
	return count;
}
