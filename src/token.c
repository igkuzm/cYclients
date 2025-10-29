#include "../cYclients.h"
#include "../partner_token.h"
#include "config.h"
#include "curl_transport.h"
#include <string.h>

static char USER_TOKEN[64];

const char *
cyclients_get_user_token(const char *login,
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
			cJSON *user_token = cJSON_GetObjectItem(data, "user_token");			
			strncpy(USER_TOKEN, user_token->valuestring, 63);
			USER_TOKEN[63] = '\0';
			return USER_TOKEN;
		}
	}
	
	return NULL;
}













