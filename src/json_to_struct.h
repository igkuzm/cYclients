#ifndef CYCLIENTS_JSON_TO_STRUCT
#define CYCLIENTS_JSON_TO_STRUCT
#include "cJSON.h"
#include "log.h"

#define STRCPY(dst, src) \
	strncpy(dst, src, sizeof(dst) - 1); dst[sizeof(dst)-1]=0;

#define JSON_TO_INT(_json, _struct, _name) \
	do { \
		cJSON *_obj = cJSON_GetObjectItem(_json, #_name); \
		if (_obj){ \
			_struct->_name = _obj->valueint; \
		} \
	}	while(0);

#define JSON_TO_BOL(_json, _struct, _name) \
	JSON_TO_INT(_json, _struct, _name)

#define JSON_TO_DOB(_json, _struct, _name) \
	do { \
		cJSON *_obj = cJSON_GetObjectItem(_json, #_name); \
		if (_obj){ \
			_struct->_name = _obj->valuedouble; \
		} \
	}	while(0);

#define JSON_TO_STR(_json, _struct, _name) \
	do { \
		cJSON *_obj = cJSON_GetObjectItem(_json, #_name); \
		if (_obj){ \
			STRCPY(_struct->_name, _obj->valuestring); \
		} \
	}	while(0);

#define JSON_TO_AST(_json, _struct, _name, _len) \
	do { \
		cJSON *_obj = cJSON_GetObjectItem(_json, #_name); \
		if (cJSON_IsArray(_obj)){ \
			int i = 0; \
			cJSON *_item = NULL; \
			cJSON_ArrayForEach(_item, _obj){ \
				if (_item){ \
					STRCPY(_struct->_name[i++], _item->valuestring); \
				} \
			} \
		} \
	}	while(0);

#define JSON_TO_AIN(_json, _struct, _name, _len) \
	do { \
		cJSON *_obj = cJSON_GetObjectItem(_json, #_name); \
		if (cJSON_IsArray(_obj)){ \
			int i = 0; \
			cJSON *_item = NULL; \
			cJSON_ArrayForEach(_item, _obj){ \
				if (_item){ \
					_struct->_name[i++] = _obj->valueint; \
				} \
			} \
		} \
	}	while(0);


#define JSON_FROM_INT(_json, _struct, _name) \
		cJSON_AddNumberToObject(_json, #_name, (double)_struct->_name);

#define JSON_FROM_DOB(_json, _struct, _name) \
	JSON_FROM_INT(_json, _struct, _name)

#define JSON_FROM_STR(_json, _struct, _name) \
		cJSON_AddStringToObject(_json, #_name, _struct->_name);

#define JSON_FROM_BOL(_json, _struct, _name) \
		cJSON_AddBoolToObject(_json, #_name, _struct->_name);

#define JSON_FROM_AIN(_json, _struct, _name, _len) \
	do { \
		cJSON *_arr = cJSON_CreateIntArray(_struct->_name, _len); \
		if (_arr){ \
			cJSON_AddItemToObject(_json, #_name, _arr); \
			cJSON_free(_arr); \
		} \
	}	while(0);

#define JSON_FROM_AST(_json, _struct, _name, _len) \
	do { \
		cJSON *_arr = cJSON_CreateArray(); \
		if (_arr){ \
			int i; \
			for (i=0; i < _len; ++i){ \
				if (_struct->_name[i]){ \
					cJSON *_item = cJSON_CreateString(_struct->_name[i]); \
					cJSON_AddItemToArray(_arr, _item); \
					cJSON_free(_item); \
				} \
			} \
			cJSON_AddItemToObject(_json, #_name, _arr); \
			cJSON_free(_arr); \
		} \
	}	while(0);


#endif /* ifndef CYCLIENTS_JSON_TO_STRUCT */
