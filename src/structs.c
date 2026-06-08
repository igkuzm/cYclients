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

// FROM JSON
#define CYC_UNKNOWN(_name)
#define CYC_INT(_name) JSON_TO_INT(json, t, _name);
#define CYC_DOUBLE(_name) JSON_TO_DOUBLE(json, t, _name);
#define CYC_BOOL(_name) JSON_TO_BOOL(json, t, _name);
#define CYC_STRING(_name, _size) JSON_TO_STRING(json, t, _name);
#define CYC_INT_ARRAY(_name, _len) \
	JSON_TO_INT_ARRAY(json, t, _name, _len);
#define CYC_DOUBLE_ARRAY(_name, _len) \
	JSON_TO_DOUBLE_ARRAY(json, t, _name, _len);
#define CYC_STRING_ARRAY(_name, _size, _len) \
	JSON_TO_STRING_ARRAY(json, t, _name, _len);

#define CYC_USER_CLASS(_name) \
	cyc_user_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_FILE_CLASS(_name) \
    cyc_file_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_TRANSPORT_CLASS(_name) \
	cyc_transport_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_2FA_CLASS(_name) CYC2fa _name \
	cyc_2fa_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_SOCIAL_CLASS(_name) \
	cyc_social_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_BOOKING_WIDGET_PROMO_CLASS(_name) \
	cyc_booking_widget_promo_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_MAIN_GROUP_CLASS(_name) \
	cyc_main_group_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_SALON_GROUP_SETTINGS_CLASS(_name) \
	cyc_salon_group_settings_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_ACCESS_CLASS(_name) \
	cyc_access_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_COMPANY_CLASS(_name) \
	cyc_company_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_CLIENT_CLASS(_name) \
	cyc_client_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_STAFF_CLASS(_name) \
	cyc_staff_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_SERVICE_CLASS(_name) \
	cyc_service_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_DOCUMENT_CLASS(_name) \
    cyc_document_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_DOCUMENT_CLASS_ARRAY(_name, _len) \
    JSON_TO_CYCSTRUCT_ARRAY(json, t, _name, _len, cyc_document_fr_json);
#define CYC_VISIT_SERVICE_CLASS(_name) \
	cyc_visit_service_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_VISIT_SERVICE_CLASS_ARRAY(_name, _len) \
	JSON_TO_CYCSTRUCT_ARRAY(json, t, _name, _len, cyc_visit_service_fr_json);
#define CYC_CUSTOM_FIELD_TYPE_CLASS(_name) \
	cyc_custom_field_type_fr_json(&t->_name, cJSON_GetObjectItem(json, #_name));
#define CYC_KVPAIR(_name, _len) \
    JSON_TO_KVPAIR(json, t, _name, _len);

#define FROM_JSON_START \
	assert(json != NULL); \
	assert(t != NULL); \
	LOG("Parsing json: %s", cJSON_Print(json)); \
	if (cJSON_IsObject(json)) {

#define FROM_JSON_END \
		return 0; \
	} \
	return -1;

int cyc_user_fr_json(CYCUser *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_USER;
	CYC_USER
	FROM_JSON_END
}

int cyc_transport_fr_json(CYCTransport *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_TRANSPORT;
	CYC_TRANSPORT
	FROM_JSON_END
}

int cyc_2fa_fr_json(CYC2fa *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_2FA;
	CYC_2FA
	FROM_JSON_END
}

int cyc_social_fr_json(CYCSocial *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_SOCIAL;
	CYC_SOCIAL
	FROM_JSON_END
}

int cyc_booking_widget_promo_fr_json(
		CYCBookingWidgetPromo *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_BOOKING_WIDGET_PROMO;
	CYC_BOOKING_WIDGET_PROMO
	FROM_JSON_END
}

int cyc_main_group_fr_json(CYCMainGroup *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_MAIN_GROUP;
	CYC_MAIN_GROUP
	FROM_JSON_END
}

int cyc_salon_group_settings_fr_json(
		CYCSalonGroupSettings *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_SALON_GROUP_SETTINGS;
	CYC_SALON_GROUP_SETTINGS
	FROM_JSON_END
}

int cyc_access_fr_json(CYCAccess *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_ACCESS;
	CYC_ACCESS
	FROM_JSON_END
}

int cyc_company_fr_json(CYCCompany *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_COMPANY;
	CYC_COMPANY
	FROM_JSON_END
}

int cyc_service_category_fr_json(CYCServiceCategory *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_SERVICE_CATEGORY;
	CYC_SERVICE_CATEGORY
	FROM_JSON_END
}

int cyc_staff_fr_json(CYCStaff *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_STAFF;
	CYC_STAFF
	FROM_JSON_END
}

int cyc_service_fr_json(CYCService *t, const cJSON *json)
{
	FROM_JSON_START
		t->_type = CYC_TYPE_SERVICE;
	CYC_SERVICE
	FROM_JSON_END
}

int cyc_user_role_fr_json(CYCUserRole *t, const cJSON *json)
{
	FROM_JSON_START
	t->_type = CYC_TYPE_USER_ROLE;
	CYC_USER_ROLE
    FROM_JSON_END		
}

int cyc_user_permissions_fr_json(CYCUserPermissions *t, const cJSON *p)
{
	cJSON *json;
	
	assert(p != NULL); \
	assert(t != NULL); \
	
	if (cJSON_IsArray(p)) {
		t->_type = CYC_TYPE_USER_PERMISSIONS;
		cJSON_ArrayForEach(json, p)
		{
			if (cJSON_IsObject(json))
			{
				const char *name = NULL;
				cJSON *slug = cJSON_GetObjectItem(json, "slug");
				cJSON *value = cJSON_GetObjectItem(json, "value");
				if (slug == NULL || value == NULL)
					continue;
				name = slug->valuestring;
				LOG("parse permission: %s", name);
				value->string = (char *)name;
				CYC_USER_PERMISSIONS
				//cJSON_free(object);
			}
		}
        return 0; \
    } \
   return -1;		
}

int cyc_file_fr_json(CYCFile *t, const cJSON *json)
{
	FROM_JSON_START
	t->_type = CYC_TYPE_FILE;
	CYC_FILE
    FROM_JSON_END		
}

int cyc_visit_service_fr_json(CYCVisitService *t, const cJSON *json)
{
	FROM_JSON_START
	t->_type = CYC_TYPE_VISIT_SERVICE;
	CYC_VISIT_SERVICE
    FROM_JSON_END		
}

int cyc_document_fr_json(CYCDocument *t, const cJSON *json)
{
	FROM_JSON_START
	t->_type = CYC_TYPE_DOCUMENT;
	CYC_DOCUMENT
  FROM_JSON_END		
}

int cyc_record_fr_json(CYCRecord *t, const cJSON *json)
{
	FROM_JSON_START
	t->_type = CYC_TYPE_RECORD;
	CYC_RECORD
  FROM_JSON_END		
}

int cyc_client_fr_json(CYCClient *t, const cJSON *json)
{
	FROM_JSON_START
	t->_type = CYC_TYPE_CLIENT;
	CYC_CLIENT
  FROM_JSON_END		
}

int cyc_comment_fr_json(CYCComment *t, const cJSON *json)
{
	FROM_JSON_START
	t->_type = CYC_TYPE_COMMENT;
	CYC_COMMENT
  FROM_JSON_END		
}

int cyc_custom_field_type_fr_json(CYCCustomFieldType *t, const cJSON *json)
{
	FROM_JSON_START
	t->_type = CYC_TYPE_CUSTOM_FIELD_TYPE;
	CYC_CUSTOM_FIELD_TYPE
  FROM_JSON_END		
}

int cyc_custom_field_fr_json(CYCCustomField *t, const cJSON *json)
{
	FROM_JSON_START
	t->_type = CYC_TYPE_CUSTOM_FIELD;
	CYC_CUSTOM_FIELD
  FROM_JSON_END		
}

#undef CYC_UNKNOWN
#undef CYC_INT
#undef CYC_DOUBLE
#undef CYC_BOOL
#undef CYC_STRING
#undef CYC_INT_ARRAY
#undef CYC_DOUBLE_ARRAY
#undef CYC_STRING_ARRAY

#undef CYC_USER_CLASS
#undef CYC_FILE_CLASS
#undef CYC_TRANSPORT_CLASS
#undef CYC_2FA_CLASS
#undef CYC_SOCIAL_CLASS
#undef CYC_BOOKING_WIDGET_PROMO_CLASS
#undef CYC_MAIN_GROUP_CLASS
#undef CYC_SALON_GROUP_SETTINGS_CLASS
#undef CYC_ACCESS_CLASS
#undef CYC_COMPANY_CLASS
#undef CYC_CLIENT_CLASS
#undef CYC_STAFF_CLASS
#undef CYC_SERVICE_CLASS
#undef CYC_VISIT_SERVICE_CLASS
#undef CYC_VISIT_SERVICE_CLASS_ARRAY
#undef CYC_DOCUMENT_CLASS
#undef CYC_DOCUMENT_CLASS_ARRAY
#undef CYC_CUSTOM_FIELD_TYPE_CLASS
#undef CYC_KVPAIR

// TO JSON
#define CYC_UNKNOWN(_name)
#define CYC_INT(_name) JSON_FROM_INT(json, t, _name);
#define CYC_DOUBLE(_name) JSON_FROM_DOUBLE(json, t, _name);
#define CYC_BOOL(_name) JSON_FROM_BOOL(json, t, _name);
#define CYC_STRING(_name, _size) JSON_FROM_STRING(json, t, _name);
#define CYC_INT_ARRAY(_name, _len) \
	JSON_FROM_INT_ARRAY(json, t, _name, _len);
#define CYC_DOUBLE_ARRAY(_name, _len) \
	JSON_FROM_DOUBLE_ARRAY(json, t, _name, _len);
#define CYC_STRING_ARRAY(_name, _size, _len) \
	JSON_FROM_STRING_ARRAY(json, t, _name, _len);

#define CYC_FILE_CLASS(_name) \
    do { \
        cJSON *_obj = \
        cyc_file_to_json(&t->_name); \
        cJSON_AddItemToObject(json, #_name, _obj); \
    }	while(0);

#define CYC_USER_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_user_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);
#define CYC_TRANSPORT_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_transport_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);
#define CYC_2FA_CLASS(_name) CYC2fa _name \
	do { \
		cJSON *_obj = \
		cyc_2fa_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);
#define CYC_SOCIAL_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_social_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);
#define CYC_BOOKING_WIDGET_PROMO_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_booking_widget_promo_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);
#define CYC_MAIN_GROUP_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_main_group_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);
#define CYC_SALON_GROUP_SETTINGS_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_salon_group_settings_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);
#define CYC_ACCESS_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_access_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);
#define CYC_COMPANY_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_company_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);
#define CYC_CLIENT_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_client_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);
#define CYC_STAFF_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_staff_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);
#define CYC_SERVICE_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_service_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);

#define CYC_VISIT_SERVICE_CLASS(_name) \
	do { \
		cJSON *_obj = \
		cyc_visit_service_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
	}	while(0);

#define CYC_VISIT_SERVICE_CLASS_ARRAY(_name, _len) \
	JSON_FROM_CYCSTRUCT_ARRAY(json, t, _name, _len, cyc_visit_service_to_json);

#define CYC_DOCUMENT_CLASS(_name) \
do { \
    cJSON *_obj = \
    cyc_document_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
}	while(0);

#define CYC_DOCUMENT_CLASS_ARRAY(_name, _len) \
JSON_FROM_CYCSTRUCT_ARRAY(json, t, _name, _len, cyc_document_to_json);

#define CYC_CUSTOM_FIELD_TYPE_CLASS(_name) \
do { \
    cJSON *_obj = \
    cyc_custom_field_type_to_json(&t->_name); \
		cJSON_AddItemToObject(json, #_name, _obj); \
}	while(0);

#define CYC_KVPAIR(_name, _len) \

#define TO_JSON_START \
	cJSON *json = NULL; \
	assert(t != NULL); \
	json = cJSON_CreateObject(); \
	if (json) {

#define TO_JSON_END \
		return json; \
	} \
	return NULL;

cJSON * cyc_user_to_json(CYCUser *t)
{
	TO_JSON_START
	CYC_USER
	TO_JSON_END
}

cJSON * cyc_transport_to_json(CYCTransport *t)
{
	TO_JSON_START
	CYC_TRANSPORT
	TO_JSON_END
}

cJSON * cyc_2fa_to_json(CYC2fa *t)
{
	TO_JSON_START
	CYC_2FA
	TO_JSON_END
}

cJSON * cyc_social_to_json(CYCSocial *t)
{
	TO_JSON_START
	CYC_SOCIAL
	TO_JSON_END
}

cJSON * cyc_booking_widget_promo_to_json(CYCBookingWidgetPromo *t)
{
	TO_JSON_START
	CYC_BOOKING_WIDGET_PROMO
	TO_JSON_END
}

cJSON * cyc_main_group_to_json(CYCMainGroup *t)
{
	TO_JSON_START
	CYC_MAIN_GROUP
	TO_JSON_END
}

cJSON * cyc_salon_group_settings_to_json(CYCSalonGroupSettings *t)
{
	TO_JSON_START
	CYC_SALON_GROUP_SETTINGS
	TO_JSON_END
}

cJSON * cyc_access_to_json(CYCAccess *t)
{
	TO_JSON_START
	CYC_ACCESS
	TO_JSON_END
}

cJSON * cyc_company_to_json(CYCCompany *t)
{
	TO_JSON_START
	CYC_COMPANY
	TO_JSON_END
}

cJSON * cyc_service_category_to_json(CYCServiceCategory *t)
{
	TO_JSON_START
	CYC_SERVICE_CATEGORY
	TO_JSON_END
}

cJSON * cyc_staff_to_json(CYCStaff *t)
{
	TO_JSON_START
	CYC_STAFF
	TO_JSON_END
}

cJSON * cyc_service_to_json(CYCService *t)
{
	TO_JSON_START
	CYC_SERVICE
	TO_JSON_END
}

cJSON * cyc_user_role_to_json(CYCUserRole *t)
{
	TO_JSON_START
	CYC_USER_ROLE
	TO_JSON_END	
}

cJSON * cyc_user_permissions_to_json(CYCUserPermissions *t)
{
	TO_JSON_START
	CYC_USER_PERMISSIONS
	TO_JSON_END	
}

cJSON * cyc_file_to_json(CYCFile *t)
{
	TO_JSON_START
	CYC_FILE
	TO_JSON_END	
}

cJSON * cyc_visit_service_to_json(CYCVisitService *t)
{
	TO_JSON_START
	CYC_VISIT_SERVICE
	TO_JSON_END	
}

cJSON * cyc_document_to_json(CYCDocument *t)
{
	TO_JSON_START
	CYC_DOCUMENT
	TO_JSON_END	
}

cJSON * cyc_record_to_json(CYCRecord *t)
{
	TO_JSON_START
	CYC_RECORD
	TO_JSON_END	
}

cJSON * cyc_client_to_json(CYCClient *t)
{
	TO_JSON_START
	CYC_CLIENT
	TO_JSON_END	
}

cJSON * cyc_comment_to_json(CYCComment *t)
{
	TO_JSON_START
	CYC_COMMENT
	TO_JSON_END	
}

cJSON * cyc_custom_field_type_to_json(CYCCustomFieldType *t)
{
	TO_JSON_START
	CYC_CUSTOM_FIELD_TYPE
	TO_JSON_END	
}

cJSON * cyc_custom_field_to_json(CYCCustomField *t)
{
	TO_JSON_START
	CYC_CUSTOM_FIELD
	TO_JSON_END	
}

#undef CYC_UNKNOWN
#undef CYC_INT
#undef CYC_DOUBLE
#undef CYC_BOOL
#undef CYC_STRING
#undef CYC_INT_ARRAY
#undef CYC_DOUBLE_ARRAY
#undef CYC_STRING_ARRAY

#undef CYC_USER_CLASS
#undef CYC_FILE_CLASS
#undef CYC_TRANSPORT_CLASS
#undef CYC_2FA_CLASS
#undef CYC_SOCIAL_CLASS
#undef CYC_BOOKING_WIDGET_PROMO_CLASS
#undef CYC_MAIN_GROUP_CLASS
#undef CYC_SALON_GROUP_SETTINGS_CLASS
#undef CYC_ACCESS_CLASS
#undef CYC_COMPANY_CLASS
#undef CYC_CLIENT_CLASS
#undef CYC_STAFF_CLASS
#undef CYC_SERVICE_CLASS
#undef CYC_VISIT_SERVICE_CLASS
#undef CYC_VISIT_SERVICE_CLASS_ARRAY
#undef CYC_CUSTOM_FIELD_TYPE_CLASS
#undef CYC_KVPAIR

