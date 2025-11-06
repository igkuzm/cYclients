/*
 *  structs.h
 *  cYclients
 *
 *  Created by Igor Sementsov on 30.10.25.
 *  Copyright 2025 ProZubi. All rights reserved.
 *
 */
#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include "cJSON.h"
#include "config.h"

typedef	enum {
	CYCLIENTS_STRUCT_TYPE_NULL,
	CYCLIENTS_STRUCT_TYPE_USER,
	CYCLIENTS_STRUCT_TYPE_TRANSPORT,
	CYCLIENTS_STRUCT_TYPE_2FA,
} CYCLIENTS_STRUCT_TYPE;

// user
#define CYCLIENTS_STRUCT_USER \
	CYCLIENTS_STRUCT_USER_INT(id) \
	CYCLIENTS_STRUCT_USER_STR(user_token, 64) \
	CYCLIENTS_STRUCT_USER_STR(name, 64) \
	CYCLIENTS_STRUCT_USER_STR(phone, 32) \
	CYCLIENTS_STRUCT_USER_STR(login, 32) \
	CYCLIENTS_STRUCT_USER_STR(email, 64) \
	CYCLIENTS_STRUCT_USER_STR(avatar, 256) \
	CYCLIENTS_STRUCT_USER_BOL(is_approved) \
	CYCLIENTS_STRUCT_USER_BOL(is_email_confirmed) \

typedef struct cyclients_user_ {
	CYCLIENTS_STRUCT_TYPE _type;
#define CYCLIENTS_STRUCT_USER_INT(_name) int _name;
#define CYCLIENTS_STRUCT_USER_STR(_name, _size) char _name[_size];
#define CYCLIENTS_STRUCT_USER_BOL(_name) bool _name;
CYCLIENTS_STRUCT_USER
#undef CYCLIENTS_STRUCT_USER_INT
#undef CYCLIENTS_STRUCT_USER_STR
#undef CYCLIENTS_STRUCT_USER_BOL
} cyclients_user_t;

int 
cyclients_user_from_json(const cJSON *json,
						             cyclients_user_t *t);
	
cJSON * 
cyclients_user_to_json(cyclients_user_t *t);
							 
// transport
#define CYCLIENTS_STRUCT_TRANSPORT \
	CYCLIENTS_STRUCT_TRANSPORT_STR(type, 64) \
	CYCLIENTS_STRUCT_TRANSPORT_STR(recipient, 128) \


typedef struct cyclients_transport_ {
	CYCLIENTS_STRUCT_TYPE _type;
#define CYCLIENTS_STRUCT_TRANSPORT_STR(_name, _size) char _name[_size];
CYCLIENTS_STRUCT_TRANSPORT
#undef CYCLIENTS_STRUCT_TRANSPORT_STR
} cyclients_transport_t;

int 
cyclients_transport_from_json(const cJSON *json,
						                  cyclients_transport_t *t);

cJSON * 
cyclients_transport_to_json(cyclients_transport_t *t);

// 2 FA
#define CYCLIENTS_STRUCT_2FA \
	CYCLIENTS_STRUCT_2FA_STR(uuid, 64) \
	CYCLIENTS_STRUCT_2FA_STR(flow, 32) \
	CYCLIENTS_STRUCT_2FA_TRANSPORT(transport) \
	CYCLIENTS_STRUCT_2FA_INT(refresh_ttl_sec) \
	CYCLIENTS_STRUCT_2FA_INT(attempts_left) \

typedef struct cyclients_2fa_ {
	CYCLIENTS_STRUCT_TYPE _type;
#define CYCLIENTS_STRUCT_2FA_STR(_name, _size) char _name[_size];
#define CYCLIENTS_STRUCT_2FA_TRANSPORT(_name) cyclients_transport_t _name;
#define CYCLIENTS_STRUCT_2FA_INT(_name) int _name;
CYCLIENTS_STRUCT_2FA
#undef CYCLIENTS_STRUCT_2FA_STR
#undef CYCLIENTS_STRUCT_2FA_TRANSPORT
#undef CYCLIENTS_STRUCT_2FA_INT
} cyclients_2fa_t;

int 
cyclients_2fa_from_json(const cJSON *json,
												cyclients_2fa_t *t);

cJSON * 
cyclients_2fa_to_json(cyclients_2fa_t *t);

#endif // STRUCTS_H
