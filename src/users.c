#include "config.h"
#include "../cYclients.h"
#include "log.h"
#include "alloc.h"
#include "structs.h"
#include "cJSON.h"
#include "../partner_token.h"
#include "curl_transport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static CYCUserRole USERROLE;

CYCLIENTS_COUNTER
cyclients_users_roles(const char *token,
                      int company_id,
					  void *userdata,
                      int (*callback)(void *userdata, 
                                      const CYCUserRole *user_role))
{
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/company/%d/users/roles", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(
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
				cJSON *user_role;
				cJSON_ArrayForEach(user_role, data)
				{
					memset(&USERROLE, 0, sizeof(USERROLE));
					cyc_user_role_fr_json(
										&USERROLE, user_role);
					if (callback)
						if (callback(userdata, &USERROLE))
							break;
					
					i++;
				}
				
				return i;
			}
		}
	}
	
	return 0;	
}
