#include "config.h"
#include "structs.h"
#include "cJSON.h"
#include <partner_token.h>
#include "../cYclients.h"
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
	CYCLIENTS_COUNTER n = 0;
	cJSON *responce = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], company_id_req[16];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(company_id_req, "&id=%s", company_id);
	sprintf(requestString, "%s/companies?my=1%s", 
			URL, company_id?company_id_req:"");
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(requestString,
                                    auth, "GET",
                                    NULL, &responce);

	if (http_code == 200){ // good
		if (cJSON_IsObject(responce))
		{
			cJSON *data = cJSON_GetObjectItem(responce, "data");
			// only one item
			if (cJSON_IsObject(data))
			{
				memset(&COMPANY, 0, sizeof(COMPANY));
				cyc_company_fr_json(&COMPANY, data);
				if (callback)
					callback(userdata, &COMPANY);
				n = 1;
			}
			// array of items
			else if (cJSON_IsArray(data))
			{
				cJSON *company;
				cJSON_ArrayForEach(company, data)
				{
					memset(&COMPANY, 0, sizeof(COMPANY));
					cyc_company_fr_json(&COMPANY, company);
					if (callback)
						if (callback(userdata, &COMPANY))
							break;

					n++;
				}
			}
		}
	}
	
	if (responce)
	    cJSON_free(responce);
	return n;
}
