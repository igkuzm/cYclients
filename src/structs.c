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

int 
cyclients_social_from_json(const cJSON *json,
															cyclients_social_t *t)
{
	assert(json != NULL);
	assert(t != NULL);
	if (cJSON_IsObject(json)) {
		t->_type = CYCLIENTS_STRUCT_TYPE_SOCIAL;
#define CYCLIENTS_STRUCT_SOCIAL_STR(_name, _size) JSON_TO_STR(json, t, _name);
		CYCLIENTS_STRUCT_SOCIAL
#undef CYCLIENTS_STRUCT_SOCIAL_STR
		return 0;
	}
	return -1;
}

cJSON * 
cyclients_social_to_json(cyclients_social_t *t)
{
	cJSON *json = NULL;
	assert(t != NULL);
	json = cJSON_CreateObject();
	if (json) {
#define CYCLIENTS_STRUCT_SOCIAL_STR(_name, _size) JSON_FROM_STR(json, t, _name);
		CYCLIENTS_STRUCT_SOCIAL
#undef CYCLIENTS_STRUCT_SOCIAL_STR
		return json;
	}
	return NULL;
}

int 
cyclients_main_group_from_json(const cJSON *json,
															cyclients_main_group_t *t)
{
	assert(json != NULL);
	assert(t != NULL);
	if (cJSON_IsObject(json)) {
		t->_type = CYCLIENTS_STRUCT_TYPE_MAIN_GROUP;
#define CYCLIENTS_STRUCT_MAIN_GROUP_INT(_name) JSON_TO_INT(json, t, _name);
#define CYCLIENTS_STRUCT_MAIN_GROUP_STR(_name, _size) JSON_TO_STR(json, t, _name);
		CYCLIENTS_STRUCT_MAIN_GROUP
#undef CYCLIENTS_STRUCT_MAIN_GROUP_INT
#undef CYCLIENTS_STRUCT_MAIN_GROUP_STR
		return 0;
	}
	return -1;
}

cJSON * 
cyclients_main_group_to_json(cyclients_main_group_t *t)
{
	cJSON *json = NULL;
	assert(t != NULL);
	json = cJSON_CreateObject();
	if (json) {
#define CYCLIENTS_STRUCT_MAIN_GROUP_INT(_name) JSON_FROM_INT(json, t, _name);
#define CYCLIENTS_STRUCT_MAIN_GROUP_STR(_name, _size) JSON_FROM_STR(json, t, _name);
		CYCLIENTS_STRUCT_MAIN_GROUP
#undef CYCLIENTS_STRUCT_MAIN_GROUP_INT
#undef CYCLIENTS_STRUCT_MAIN_GROUP_STR
		return json;
	}
	return NULL;
}

int 
cyclients_salon_group_settings_from_json(const cJSON *json,
															cyclients_salon_group_settings_t *t)
{
	assert(json != NULL);
	assert(t != NULL);
	if (cJSON_IsObject(json)) {
		t->_type = CYCLIENTS_STRUCT_TYPE_SALON_GROUP_SETTINGS;
#define CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_INT(_name) JSON_TO_INT(json, t, _name);
#define CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_BOL(_name) JSON_TO_INT(json, t, _name);
		CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS
#undef CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_INT
#undef CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_BOL
		return 0;
	}
	return -1;
}

cJSON * 
cyclients_salon_group_settings_to_json(cyclients_salon_group_settings_t *t)
{
	cJSON *json = NULL;
	assert(t != NULL);
	json = cJSON_CreateObject();
	if (json) {
#define CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_INT(_name) JSON_FROM_INT(json, t, _name);
#define CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_BOL(_name) JSON_FROM_BOL(json, t, _name);
		CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS
#undef CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_INT
#undef CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_BOL
		return json;
	}
	return NULL;
}

int 
cyclients_booking_widget_promo_from_json(const cJSON *json,
															cyclients_booking_widget_promo_t *t)
{
	assert(json != NULL);
	assert(t != NULL);
	if (cJSON_IsObject(json)) {
		t->_type = CYCLIENTS_STRUCT_TYPE_BOOKING_WIDGWT_PROMO;
#define CYCLIENTS_STRUCT_BOOKING_WIDGWT_PROMO_STR(_name, _size) JSON_TO_STR(json, t, _name);
		CYCLIENTS_STRUCT_BOOKING_WIDGWT_PROMO
#undef CYCLIENTS_STRUCT_BOOKING_WIDGWT_PROMO_STR
		return 0;
	}
	return -1;
}

cJSON * 
cyclients_booking_widget_promo_to_json(cyclients_booking_widget_promo_t *t)
{
	cJSON *json = NULL;
	assert(t != NULL);
	json = cJSON_CreateObject();
	if (json) {
#define CYCLIENTS_STRUCT_BOOKING_WIDGWT_PROMO_STR(_name, _size) JSON_FROM_STR(json, t, _name);
		CYCLIENTS_STRUCT_BOOKING_WIDGWT_PROMO
#undef CYCLIENTS_STRUCT_BOOKING_WIDGWT_PROMO_STR
		return json;
	}
	return NULL;
}

int 
cyclients_access_from_json(const cJSON *json,
															cyclients_access_t *t)
{
	assert(json != NULL);
	assert(t != NULL);
	if (cJSON_IsObject(json)) {
		t->_type = CYCLIENTS_STRUCT_TYPE_ACCESS;
#define CYCLIENTS_STRUCT_ACCESS_INT(_name) JSON_TO_INT(json, t, _name);
#define CYCLIENTS_STRUCT_ACCESS_BOL(_name) JSON_TO_INT(json, t, _name);
#define CYCLIENTS_STRUCT_ACCESS_AIN(_name, _len) \
		JSON_TO_AIN(json, t, _name, _len);
#define CYCLIENTS_STRUCT_ACCESS_AST(_name, _size, _len) \
		JSON_TO_AST(json, t, _name, _len);
		CYCLIENTS_STRUCT_ACCESS
#undef CYCLIENTS_STRUCT_ACCESS_INT
#undef CYCLIENTS_STRUCT_ACCESS_BOL
#undef CYCLIENTS_STRUCT_ACCESS_AIN
#undef CYCLIENTS_STRUCT_ACCESS_AST
		return 0;
	}
	return -1;
}

cJSON * 
cyclients_access_to_json(cyclients_access_t *t)
{
	cJSON *json = NULL;
	assert(t != NULL);
	json = cJSON_CreateObject();
	if (json) {
#define CYCLIENTS_STRUCT_ACCESS_INT(_name) JSON_FROM_INT(json, t, _name);
#define CYCLIENTS_STRUCT_ACCESS_BOL(_name) JSON_FROM_BOL(json, t, _name);
#define CYCLIENTS_STRUCT_ACCESS_AIN(_name, _len) \
		JSON_FROM_AIN(json, t, _name, _len);
#define CYCLIENTS_STRUCT_ACCESS_AST(_name, _size,  _len) \
		JSON_FROM_AST(json, t, _name, _len);
		CYCLIENTS_STRUCT_ACCESS
#undef CYCLIENTS_STRUCT_ACCESS_INT
#undef CYCLIENTS_STRUCT_ACCESS_BOL
#undef CYCLIENTS_STRUCT_ACCESS_AIN
#undef CYCLIENTS_STRUCT_ACCESS_AST
		return json;
	}
	return NULL;
}

int 
cyclients_company_from_json(const cJSON *json,
														cyclients_company_t *t)
{
	assert(json != NULL);
	assert(t != NULL);
	if (cJSON_IsObject(json)) {
		t->_type = CYCLIENTS_STRUCT_TYPE_COMPANY;
#define CYCLIENTS_STRUCT_COMPANY_INT(_name) JSON_TO_INT(json, t, _name);
#define CYCLIENTS_STRUCT_COMPANY_STR(_name, _size) JSON_TO_STR(json, t, _name);
#define CYCLIENTS_STRUCT_COMPANY_BOL(_name) JSON_TO_INT(json, t, _name);
#define CYCLIENTS_STRUCT_COMPANY_AST(_name, _size, _len) \
		JSON_TO_AST(json, t, _name, _len);
#define CYCLIENTS_STRUCT_COMPANY_DOB(_name) JSON_TO_DOB(json, t, _name);
#define CYCLIENTS_STRUCT_COMPANY_SOCIAL(_name) \
		cyclients_social_from_json(json, &t->_name);
#define CYCLIENTS_STRUCT_COMPANY_MAIN_GROUP(_name) \
		cyclients_main_group_from_json(json, &t->_name);
#define CYCLIENTS_STRUCT_COMPANY_MAIN_SALON_GROUP_SETTINGS(_name) \
		cyclients_salon_group_settings_from_json(json, &t->_name);
#define CYCLIENTS_STRUCT_COMPANY_BOOKING_WIDET_PROMO(_name) \
		cyclients_booking_widget_promo_from_json(json, &t->_name);
#define CYCLIENTS_STRUCT_COMPANY_ACCESS(_name) \
		cyclients_access_from_json(json, &t->_name);
		CYCLIENTS_STRUCT_COMPANY
#undef CYCLIENTS_STRUCT_COMPANY_INT
#undef CYCLIENTS_STRUCT_COMPANY_STR
#undef CYCLIENTS_STRUCT_COMPANY_BOL		
#undef CYCLIENTS_STRUCT_COMPANY_AST
#undef CYCLIENTS_STRUCT_COMPANY_DOB		
#undef CYCLIENTS_STRUCT_COMPANY_SOCIAL
#undef CYCLIENTS_STRUCT_COMPANY_MAIN_GROUP
#undef CYCLIENTS_STRUCT_COMPANY_MAIN_SALON_GROUP_SETTINGS
#undef CYCLIENTS_STRUCT_COMPANY_BOOKING_WIDET_PROMO
#undef CYCLIENTS_STRUCT_COMPANY_ACCESS
		return 0;
	}
	return -1;
}

cJSON * 
cyclients_company_to_json(cyclients_company_t *t)
{
	cJSON *json = NULL;
	assert(t != NULL);
	json = cJSON_CreateObject();
	if (json) {
#define CYCLIENTS_STRUCT_COMPANY_INT(_name) JSON_FROM_INT(json, t, _name);
#define CYCLIENTS_STRUCT_COMPANY_STR(_name, _size) JSON_FROM_STR(json, t, _name);
#define CYCLIENTS_STRUCT_COMPANY_BOL(_name) JSON_FROM_BOL(json, t, _name);
#define CYCLIENTS_STRUCT_COMPANY_AST(_name, _size, _len)
#define CYCLIENTS_STRUCT_COMPANY_DOB(_name) JSON_FROM_INT(json, t, _name);
#define CYCLIENTS_STRUCT_COMPANY_SOCIAL(_name) \
		cJSON_AddItemToObject(json, #_name, cyclients_social_to_json(&t->_name));
#define CYCLIENTS_STRUCT_COMPANY_MAIN_GROUP(_name) \
		cJSON_AddItemToObject(json, #_name, cyclients_main_group_to_json(&t->_name));
#define CYCLIENTS_STRUCT_COMPANY_MAIN_SALON_GROUP_SETTINGS(_name) \
		cJSON_AddItemToObject(json, #_name, cyclients_salon_group_settings_to_json(&t->_name));
#define CYCLIENTS_STRUCT_COMPANY_BOOKING_WIDET_PROMO(_name) \
		cJSON_AddItemToObject(json, #_name, cyclients_booking_widget_promo_to_json(&t->_name));
#define CYCLIENTS_STRUCT_COMPANY_ACCESS(_name) \
		cJSON_AddItemToObject(json, #_name, cyclients_access_to_json(&t->_name));
		CYCLIENTS_STRUCT_COMPANY
#undef CYCLIENTS_STRUCT_COMPANY_INT
#undef CYCLIENTS_STRUCT_COMPANY_STR
#undef CYCLIENTS_STRUCT_COMPANY_BOL		
#undef CYCLIENTS_STRUCT_COMPANY_AST
#undef CYCLIENTS_STRUCT_COMPANY_DOB		
#undef CYCLIENTS_STRUCT_COMPANY_SOCIAL
#undef CYCLIENTS_STRUCT_COMPANY_MAIN_GROUP
#undef CYCLIENTS_STRUCT_COMPANY_MAIN_SALON_GROUP_SETTINGS
#undef CYCLIENTS_STRUCT_COMPANY_BOOKING_WIDET_PROMO
#undef CYCLIENTS_STRUCT_COMPANY_ACCESS
		return json;
	}
	return NULL;
}

