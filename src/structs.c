/*
 *  structs.c
 *  cYclients
 *
 *  Created by Igor Sementsov on 30.10.25.
 *  Copyright 2025 ProZubi. All rights reserved.
 *
 */

#include "structs.h"
#include "config.h"
#include "log.h"
#include <assert.h>

int 
cyclients_user_from_json(const cJSON *json,
						 cyclients_user_t *t)
{
	assert(json != NULL);
	assert(t != NULL);
	if (cJSON_IsObject(json)) {
		cJSON *id, *user_token, *name, *phone, *login, *email, 
			  *avatar, *is_approved, *is_email_confirmed;
		
		id = cJSON_GetObjectItem(json, "id");
		user_token = cJSON_GetObjectItem(json, "user_token");			
		name = cJSON_GetObjectItem(json, "name");			
		phone = cJSON_GetObjectItem(json, "phone");			
		login = cJSON_GetObjectItem(json, "login");			
		email = cJSON_GetObjectItem(json, "email");			
		avatar = cJSON_GetObjectItem(json, "avatar");			
		is_approved = cJSON_GetObjectItem(json, "is_approved");			
		is_email_confirmed = cJSON_GetObjectItem(json, "is_email_confirmed");
		
		if (id == NULL || name == NULL || user_token == NULL){
			ERR("%s", "json has no user structure");
			return -1;
		}
		
		t->id = id->valueint;
		STRCPY(t->user_token, user_token->valuestring);
		STRCPY(t->name, name->valuestring);
		STRCPY(t->phone, phone->valuestring);
		STRCPY(t->login, login->valuestring);
		STRCPY(t->email, email->valuestring);
		STRCPY(t->avatar, avatar->valuestring);
		t->is_approved = is_approved->valueint;
		t->is_email_confirmed = is_email_confirmed->valueint;
		
		return 0;
	}

	return -1;
}
