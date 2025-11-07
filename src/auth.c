#include "../cYclients.h"
#include "../partner_token.h"
#include "cJSON.h"
#include "log.h"
#include "config.h"
#include "curl_transport.h"
#include <string.h>

static cyclients_user_t USER;
static cyclients_2fa_t  USER_2FA;

static const cyclients_user_t *
get_user(cJSON *json)
{
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

static const cyclients_2fa_t *
get_2fa(cJSON *json)
{
	if (cJSON_IsObject(json)) {
		cJSON *data = cJSON_GetObjectItem(json, "data");
		if (cJSON_IsObject(data)) {
			if (cyclients_2fa_from_json(data, &USER_2FA) == 0){
				// we have user structure
				return &USER_2FA;
			}
		}
	}
	return NULL;
}

CYCLIENTS_AUTH
cyclients_login(const char *login,
								const char *password,
								const cyclients_user_t **user,
								const cyclients_2fa_t  **user2fa)
{
	CYCLIENTS_AUTH ret = CYCLIENTS_AUTH_ERROR;
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], post[BUFSIZ];
	char * SETUP_PARTNER_TOKEN(partner_token);

	memset(&USER, 0, sizeof(USER));
	memset(&USER_2FA, 0, sizeof(USER_2FA));
		
	sprintf(requestString, "%s/auth", URL);
	sprintf(auth, "Authorization: Bearer %s", partner_token);
	sprintf(post, "{\"login\":\"%s\",\"password\":\"%s\"}", login, password);		
	
	http_code = curl_transport_post(
			requestString,
		 	auth, "POST",
		 	post, &json);
	if (http_code == 201){ // is authorized
#ifdef DEBUG
	LOG("%s: %s", __FILE__, "authorized!");
#endif
		if (user)
			*user = get_user(json);
		ret = CYCLIENTS_AUTH_AUTHORIZED;
	
	} else if (http_code == 200){
#ifdef DEBUG
	LOG("%s: %s", __FILE__, "2-factor authorization is needed");
#endif
		if (user2fa){
			*user2fa = get_2fa(json);
			ret = CYCLIENTS_AUTH_2FA;
		}
	}
	
	cJSON_free(json);
	return ret;
}

CYCLIENTS_AUTH
cyclients_login_2fa(const char *login, 
										const char *password,
										const char *uuid,
                    const char *secret,
										const cyclients_user_t **user)
{
	CYCLIENTS_AUTH ret = CYCLIENTS_AUTH_ERROR;
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], post[BUFSIZ];
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	memset(&USER, 0, sizeof(USER));
	
	sprintf(requestString, "%s/auth", URL);
	sprintf(auth, "Authorization: Bearer %s", partner_token);
	sprintf(post, "{\"login\":\"%s\",\"password\":\"%s\",\"2fa:{\"uuid\":\"%s\",\"secret\":\"%s\"}\"}"
			, login, password, uuid, secret);		
	
	http_code = curl_transport_post(requestString,
		 	auth, "POST", 
			post, &json);

	if (http_code == 201){ // is authorized
#ifdef DEBUG
	LOG("%s: %s", __FILE__, "authorized!");
#endif
		if (user)
			*user = get_user(json);

		ret = CYCLIENTS_AUTH_AUTHORIZED;
	}
	
	cJSON_free(json);
	return ret;	
}
