#include "../cYclients.h"
#include "config.h"
#include "cJSON.h"
#include "../partner_token.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char USER_TOKEN[64];
static char ERROR[256];

struct string {
	char *ptr;
	size_t len;
};

static void init_string(struct string *s) {
	s->len = 0;
	s->ptr = malloc(s->len+1);
	if (s->ptr == NULL) {
		perror("string malloc");
		exit(EXIT_FAILURE);
	}
	s->ptr[0] = '\0';
}


static size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
	size_t new_len = s->len + size*nmemb;
	s->ptr = realloc(s->ptr, new_len+1);
	if (s->ptr == NULL) {
		perror("string realloc");
		exit(EXIT_FAILURE);
	}
	memcpy(s->ptr+s->len, ptr, size*nmemb);
	s->ptr[new_len] = '\0';
	s->len = new_len;

	return size*nmemb;
}


const char *
cyclients_get_user_token(const char *login,
						 const char *password)
{
	char * SETUP_PARTNER_TOKEN(partner_token);
	CURL *curl = curl_easy_init();
	struct string s;

	init_string(&s);
	
	if (curl){
		char requestString[BUFSIZ], auth[128], post[BUFSIZ];	
		struct curl_slist *header = NULL;
		CURLcode res = 0;
		cJSON *json;
		
		sprintf(requestString, "%s/auth", URL);
		curl_easy_setopt(curl, CURLOPT_URL, requestString);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");		
		curl_easy_setopt(curl, CURLOPT_HEADER, false);

		sprintf(auth, "Authorization: Bearer %s", partner_token);
	    
		header = curl_slist_append(header, "Accept: application/vnd.yclients.v2+json");		
	    header = curl_slist_append(header, "Connection: close");		
	    header = curl_slist_append(header, "Content-Type: application/json");		
	    header = curl_slist_append(header, auth);		
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

		sprintf(post, "{\"login\":\"%s\",\"password\":\"%s\"}", login, password);		
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(post));
		
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
		
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); //do not verify sertificate		
		
		res = curl_easy_perform(curl);
		
		curl_easy_cleanup(curl);
		curl_slist_free_all(header);
		if (res) { //handle erros
            sprintf(ERROR, "CURL ERROR: %d", res);
			perror(ERROR);
            return NULL;			
		}		
		
		json = cJSON_Parse(s.ptr);
		free(s.ptr);
		if (cJSON_IsObject(json)) {
			cJSON *data = cJSON_GetObjectItem(json, "data");
			if (cJSON_IsObject(data)) {
				cJSON *user_token = cJSON_GetObjectItem(data, "user_token");			
				strncpy(USER_TOKEN, user_token->valuestring, 63);
				USER_TOKEN[63] = '\0';
				return USER_TOKEN;
			}
		}		
		
	}

	return NULL;
}













