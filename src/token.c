#include "../cYclients.h"
#include "../partner_token.h"
#include "config.h"
#include "curl_transport.h"
#include <string.h>

static cyclients_user_t USER;

const cyclients_user_t *
cyclients_login(const char *login,
				const char *password)
{
	cJSON *json;
	char requestString[BUFSIZ], auth[128], post[BUFSIZ];
	char * SETUP_PARTNER_TOKEN(partner_token);
		
	sprintf(requestString, "%s/auth", URL);
	sprintf(auth, "Authorization: Bearer %s", partner_token);
	sprintf(post, "{\"login\":\"%s\",\"password\":\"%s\"}", login, password);		
	
	json = curl_transport_post(requestString, auth, post);
	if (cJSON_IsObject(json)) {
		cJSON *data = cJSON_GetObjectItem(json, "data");
		if (cJSON_IsObject(data)) {
			cyclients_user_from_json(data, &USER);
			return &USER;
		}
	}
	
	return NULL;
}













