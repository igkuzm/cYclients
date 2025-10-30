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
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

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

cJSON *
curl_transport_post(const char *request_url, 
					const char *auth_header, 
					const char *post_data)
{
	CURL *curl;
	struct string s;
	char * SETUP_PARTNER_TOKEN(partner_token);
	
	curl = curl_easy_init();
	if (curl){
		struct curl_slist *header = NULL;
		CURLcode res = 0;
		cJSON *json;
		
		init_string(&s);
	
		curl_easy_setopt(curl, CURLOPT_URL, request_url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");		
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		
		header = curl_slist_append(header, "Accept: application/vnd.yclients.v2+json");		
	    header = curl_slist_append(header, "Connection: close");		
	    header = curl_slist_append(header, "Content-Type: application/json");		
	    header = curl_slist_append(header, auth_header);		
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
		
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(post_data));

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); //do not verify sertificate		

		res = curl_easy_perform(curl);
		
		curl_easy_cleanup(curl);
		curl_slist_free_all(header);
		if (res) { //handle erros
            sprintf(CURL_ERROR, "CURL ERROR: %d", res);
			perror(CURL_ERROR);
            return NULL;			
		}		
		
		json = cJSON_Parse(s.ptr);
#ifdef DEBUG
		if (json){
			printf("%s\n", cJSON_Print(json));
		}
	    else {
			printf("JSON IS NULL");
		}
#endif
		free(s.ptr);
		
		return json;
	}
	
	return NULL;
}