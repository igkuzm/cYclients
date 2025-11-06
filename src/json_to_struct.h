#ifndef CYCLIENTS_JSON_TO_STRUCT
#define CYCLIENTS_JSON_TO_STRUCT
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

#define JSON_TO_STR(_json, _struct, _name) \
	do { \
		cJSON *_obj = cJSON_GetObjectItem(_json, #_name); \
		if (_obj){ \
			STRCPY(_struct->_name, _obj->valuestring); \
		} \
	}	while(0);

#define JSON_FROM_INT(_json, _struct, _name) \
		cJSON_AddNumberToObject(_json, #_name, (double)_struct->_name);

#define JSON_FROM_STR(_json, _struct, _name) \
		cJSON_AddStringToObject(_json, #_name, _struct->_name);

#define JSON_FROM_BOL(_json, _struct, _name) \
		cJSON_AddBoolToObject(_json, #_name, _struct->_name);

#endif /* ifndef CYCLIENTS_JSON_TO_STRUCT */
