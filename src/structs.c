/*
 *  structs.c
 *  cYclients
 *
 *  Created by Igor Sementsov on 30.10.25.
 *  Copyright 2025 ProZubi. All rights reserved.
 *
 */

#include "structs.h"
#include "cJSON.h"
#include "config.h"
#include "log.h"
#include "json_to_struct.h"
#include <assert.h>

int 
cyclients_user_from_json(const cJSON *json,
												 cyclients_user_t *t)
{
	assert(json != NULL);
	assert(t != NULL);
	if (cJSON_IsObject(json)) {
		t->_type = CYCLIENTS_STRUCT_TYPE_USER;
#define CYCLIENTS_STRUCT_USER_INT(_name) JSON_TO_INT(json, t, _name);
#define CYCLIENTS_STRUCT_USER_STR(_name, _size) JSON_TO_STR(json, t, _name);
#define CYCLIENTS_STRUCT_USER_BOL(_name) JSON_TO_INT(json, t, _name);
		CYCLIENTS_STRUCT_USER
#undef CYCLIENTS_STRUCT_USER_INT
#undef CYCLIENTS_STRUCT_USER_STR
#undef CYCLIENTS_STRUCT_USER_BOL		
		return 0;
	}
	return -1;
}

cJSON * 
cyclients_user_to_json(cyclients_user_t *t)
{
	cJSON *json = NULL;
	assert(t != NULL);
	json = cJSON_CreateObject();
	if (json) {
#define CYCLIENTS_STRUCT_USER_INT(_name) JSON_FROM_INT(json, t, _name);
#define CYCLIENTS_STRUCT_USER_STR(_name, _size) JSON_FROM_STR(json, t, _name);
#define CYCLIENTS_STRUCT_USER_BOL(_name) JSON_FROM_BOL(json, t, _name);
		CYCLIENTS_STRUCT_USER
#undef CYCLIENTS_STRUCT_USER_INT
#undef CYCLIENTS_STRUCT_USER_STR
#undef CYCLIENTS_STRUCT_USER_BOL		
		return json;
	}
	return NULL;
}

int 
cyclients_transport_from_json(const cJSON *json,
															cyclients_transport_t *t)
{
	assert(json != NULL);
	assert(t != NULL);
	if (cJSON_IsObject(json)) {
		t->_type = CYCLIENTS_STRUCT_TYPE_TRANSPORT;
#define CYCLIENTS_STRUCT_TRANSPORT_STR(_name, _size) JSON_TO_STR(json, t, _name);
		CYCLIENTS_STRUCT_TRANSPORT
#undef CYCLIENTS_STRUCT_TRANSPORT_STR
		return 0;
	}
	return -1;
}

cJSON * 
cyclients_transport_to_json(cyclients_transport_t *t)
{
	cJSON *json = NULL;
	assert(t != NULL);
	json = cJSON_CreateObject();
	if (json) {
#define CYCLIENTS_STRUCT_TRANSPORT_STR(_name, _size) JSON_FROM_STR(json, t, _name);
		CYCLIENTS_STRUCT_TRANSPORT
#undef CYCLIENTS_STRUCT_TRANSPORT_STR
		return json;
	}
	return NULL;
}

int 
cyclients_2fa_from_json(const cJSON *json,
												cyclients_2fa_t *t)
{
	assert(json != NULL);
	assert(t != NULL);
	if (cJSON_IsObject(json)) {
		t->_type = CYCLIENTS_STRUCT_TYPE_2FA;
#define CYCLIENTS_STRUCT_2FA_STR(_name, _size) JSON_TO_STR(json, t, _name);
#define CYCLIENTS_STRUCT_2FA_TRANSPORT(_name) \
	cyclients_transport_from_json(json, &t->_name);
#define CYCLIENTS_STRUCT_2FA_INT(_name) JSON_TO_INT(json, t, _name);
		CYCLIENTS_STRUCT_2FA
#undef CYCLIENTS_STRUCT_2FA_STR
#undef CYCLIENTS_STRUCT_2FA_TRANSPORT
#undef CYCLIENTS_STRUCT_2FA_INT
		return 0;
	}
	return -1;
}

cJSON * 
cyclients_2fa_to_json(cyclients_2fa_t *t)
{
	cJSON *json = NULL;
	assert(t != NULL);
	json = cJSON_CreateObject();
	if (json) {
#define CYCLIENTS_STRUCT_2FA_STR(_name, _size) JSON_FROM_STR(json, t, _name);
#define CYCLIENTS_STRUCT_2FA_TRANSPORT(_name) \
		cJSON_AddItemToObject(json, #_name, cyclients_transport_to_json(&t->_name));
#define CYCLIENTS_STRUCT_2FA_INT(_name) JSON_FROM_INT(json, t, _name);
		CYCLIENTS_STRUCT_2FA
#undef CYCLIENTS_STRUCT_2FA_STR
#undef CYCLIENTS_STRUCT_2FA_TRANSPORT
#undef CYCLIENTS_STRUCT_2FA_INT
		return json;
	}
	return NULL;
}
