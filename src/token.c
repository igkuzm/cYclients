#include "../cYclients.h"
#include "../partner_token.h"
#include "config.h"
#include "curl_transport.h"
#include <string.h>

static cyclients_user_t USER;
static cyclients_2fa_t  USER_2FA;

const cyclients_user_t *
cyclients_login(const char *login,
				const char *password,
				const cyclients_2fa_t **user2fa)
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
			if (cyclients_user_from_json(data, &USER) == 0){
				// we have user structure
				return &USER;
			} else {
				// try to get 2 factor authorization
				if (cyclients_2fa_from_json(data, &USER_2FA) == 0){
					if (user2fa){
						*user2fa = &USER_2FA;
						return NULL;
					}
				}
			}
		}
	}
	
	return NULL;
}

const cyclients_user_t *
cyclients_login_2fa(const char *login, 
				    const char *password,
					const char *uuid,
                    const char *secret)
{
	cJSON *json;
	char requestString[BUFSIZ], auth[128], post[BUFSIZ];
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	sprintf(requestString, "%s/auth", URL);
	sprintf(auth, "Authorization: Bearer %s", partner_token);
	sprintf(post, "{\"login\":\"%s\",\"password\":\"%s\",\"2fa:{\"uuid\":\"%s\",\"secret\":\"%s\"}\"}"
			, login, password, uuid, secret);		
	
	json = curl_transport_post(requestString, auth, post);
	if (cJSON_IsObject(json)) {
		cJSON *data = cJSON_GetObjectItem(json, "data");
		if (cJSON_IsObject(data)) {
			if (cyclients_user_from_json(data, &USER) == 0){
				// we have user structure
				return &USER;
			}
		}
	}
	
	return NULL;	
}












