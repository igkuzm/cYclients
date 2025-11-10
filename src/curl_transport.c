/*
 *  curl_transport.c
 *  cYclients
 *
 *  Created by Igor Sementsov on 30.10.25.
 *  Copyright 2025 ProZubi. All rights reserved.
 *
 */

#include "curl_transport.h"
#include "../partner_token.h"
#include "cJSON.h"
#include "config.h"
#include "log.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static char CURL_ERROR[256];

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

HTTP_RESPONCE
curl_transport_post(const char *request_url, 
										const char *auth_header, 
										const char *http_method,
										const char *post_data,
										cJSON **json)
{
	CURL *curl, *partner_token;
	struct string s;

	assert(request_url);
	assert(auth_header);
	assert(http_method);
	
#ifdef DEBUG
		LOG("%s: URL: %s", __FILE__, request_url);
		LOG("%s: METHOD: %s", __FILE__, http_method);
#endif
	SETUP_PARTNER_TOKEN(partner_token);
	curl = curl_easy_init();
	if (curl){
		struct curl_slist *header = NULL;
		CURLcode res = 0;
		long http_code = 0;
		cJSON *responce;
		
		init_string(&s);
	
		curl_easy_setopt(curl, CURLOPT_URL, request_url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, http_method);		
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		
		header = curl_slist_append(header, "Accept: application/vnd.yclients.v2+json");		
	    header = curl_slist_append(header, "Connection: close");		
	    header = curl_slist_append(header, "Content-Type: application/json");		
	    header = curl_slist_append(header, auth_header);		
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
		
		if (post_data){
#ifdef DEBUG
		LOG("%s: POST data: %s", __FILE__, post_data);
#endif
		  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
		  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(post_data));
		}

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, CURL_SSL_VERIFY); 

		res = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
#ifdef DEBUG
		LOG("%s: http returned: %d", __FILE__, http_code);
#endif
		
		curl_easy_cleanup(curl);
		curl_slist_free_all(header);
		if (res) { //handle erros
      sprintf(CURL_ERROR, "CURL ERROR: %d", res);
			ERR("%s",CURL_ERROR);
      return http_code;			
		}		
		
		responce = cJSON_ParseWithLength(s.ptr, s.len);
#ifdef DEBUG
		if (responce){
			LOG("%s: %s", __FILE__, cJSON_Print(responce));
		}
	    else {
			LOG("%s: %s", __FILE__, "RESPONCE JSON IS NULL");
		}
#endif
		free(s.ptr);
		
		if (cJSON_IsObject(responce)){
			cJSON *success, *meta;
			success = cJSON_GetObjectItem(responce, "success");
			meta = cJSON_GetObjectItem(responce, "meta");

			// handle answer
			if (success && success->valueint == true){
				// return json
				if (json && responce){
					*json = responce;
				} else {
					cJSON_free(responce);
				}
				return http_code;
			}
		
			// handle errors
			if (success && success->valueint == false){
				if (cJSON_IsObject(meta)){
					cJSON *message;
					message = cJSON_GetObjectItem(
							meta, "message");
					if (message){
						ERR("%s", message->valuestring);
						cJSON_free(responce);
						return http_code;
					}
				}
			}
			
			ERR("%s", "unknown error!");
			return http_code;
		}
		return http_code;
	}
	
	return -1;
}
