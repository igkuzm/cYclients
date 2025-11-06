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
	CYCLIENTS_STRUCT_TYPE_SOCIAL,
	CYCLIENTS_STRUCT_TYPE_COMPANY,
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

// SOCIAL
#define CYCLIENTS_STRUCT_SOCIAL \
	CYCLIENTS_STRUCT_SOCIAL_STR(facebook, 64) \
	CYCLIENTS_STRUCT_SOCIAL_STR(vk, 64) \
	CYCLIENTS_STRUCT_SOCIAL_STR(instagram, 64) \
	CYCLIENTS_STRUCT_SOCIAL_STR(telegram, 64) \
	CYCLIENTS_STRUCT_SOCIAL_STR(whatsapp, 64) \
	CYCLIENTS_STRUCT_SOCIAL_STR(viber, 64) \

typedef struct cyclients_social_ {
	CYCLIENTS_STRUCT_TYPE _type;
#define CYCLIENTS_STRUCT_SOCIAL_STR(_name, _size) char _name[_size];
CYCLIENTS_STRUCT_SOCIAL
#undef CYCLIENTS_STRUCT_SOCIAL_STR
} cyclients_social_t;

int 
cyclients_social_from_json(const cJSON *json,
						               cyclients_social_t *t);

cJSON * 
cyclients_social_to_json(cyclients_social_t *t);


// COMPANY
#define CYCLIENTS_STRUCT_COMPANY \
	CYCLIENTS_STRUCT_COMPANY_INT(id) \
	CYCLIENTS_STRUCT_COMPANY_STR(title, 64) \
	CYCLIENTS_STRUCT_COMPANY_STR(public_title, 64) \
	CYCLIENTS_STRUCT_COMPANY_STR(short_descr, 64) \
	CYCLIENTS_STRUCT_COMPANY_STR(logo, 256) \
	CYCLIENTS_STRUCT_COMPANY_INT(country_id) \
	CYCLIENTS_STRUCT_COMPANY_STR(country, 32) \
	CYCLIENTS_STRUCT_COMPANY_INT(city_id) \
	CYCLIENTS_STRUCT_COMPANY_STR(city, 32) \
	CYCLIENTS_STRUCT_COMPANY_INT(active) \
	CYCLIENTS_STRUCT_COMPANY_STR(phone, 32) \
	CYCLIENTS_STRUCT_COMPANY_SAR(phones, 32, 10) \
	CYCLIENTS_STRUCT_COMPANY_STR(email, 32) \
	CYCLIENTS_STRUCT_COMPANY_INT(timezone) \
	CYCLIENTS_STRUCT_COMPANY_STR(timezone_name, 32) \
	CYCLIENTS_STRUCT_COMPANY_STR(schedule, 32) \
	CYCLIENTS_STRUCT_COMPANY_STR(address, 256) \
	CYCLIENTS_STRUCT_COMPANY_STR(coordinate_lat, 16) \
	CYCLIENTS_STRUCT_COMPANY_STR(coordinate_lon, 16) \
	CYCLIENTS_STRUCT_COMPANY_STR(app_ios, 32) \
	CYCLIENTS_STRUCT_COMPANY_STR(app_android, 32) \
	CYCLIENTS_STRUCT_COMPANY_BOL(phone_confirmation) \
	CYCLIENTS_STRUCT_COMPANY_STR(currency_short_title, 8) \
	CYCLIENTS_STRUCT_COMPANY_BOL(reminds_sms_disabled) \
	CYCLIENTS_STRUCT_COMPANY_INT(reminds_sms_default) \
	CYCLIENTS_STRUCT_COMPANY_INT(group_priority) \
	CYCLIENTS_STRUCT_COMPANY_INT(bookform_group_priority) \
	CYCLIENTS_STRUCT_COMPANY_STR(description, BUFSIZ) \
	CYCLIENTS_STRUCT_COMPANY_SAR(photos, 256, 10) \
	CYCLIENTS_STRUCT_COMPANY_SAR(company_photos, 256, 10) \
	CYCLIENTS_STRUCT_COMPANY_INT(seance_delay_step) \
	CYCLIENTS_STRUCT_COMPANY_BOL(show_any_master) \
	CYCLIENTS_STRUCT_COMPANY_BOL(allow_delete_record) \
	CYCLIENTS_STRUCT_COMPANY_BOL(allow_change_record) \
	CYCLIENTS_STRUCT_COMPANY_BOL(allow_change_prepaid_record) \
	CYCLIENTS_STRUCT_COMPANY_BOL(allow_delete_prepaid_record) \
	CYCLIENTS_STRUCT_COMPANY_INT(prepayment_waiting_duration_ms) \
	CYCLIENTS_STRUCT_COMPANY_INT(allow_change_record_delay_step) \
	CYCLIENTS_STRUCT_COMPANY_INT(allow_delete_record_delay_step) \
	CYCLIENTS_STRUCT_COMPANY_BOL(timetable_off) \
	CYCLIENTS_STRUCT_COMPANY_STR(site, 128) \
	CYCLIENTS_STRUCT_COMPANY_STR(zip, 16) \
	CYCLIENTS_STRUCT_COMPANY_INT(business_group_id) \
	CYCLIENTS_STRUCT_COMPANY_INT(business_type_id) \
	CYCLIENTS_STRUCT_COMPANY_BOL(is_charge_active) \
	CYCLIENTS_STRUCT_COMPANY_BOL(is_charge_optional) \
	CYCLIENTS_STRUCT_COMPANY_BOL(is_abonement_restriction_enabled) \
	CYCLIENTS_STRUCT_COMPANY_INT(print_bill_on) \
	CYCLIENTS_STRUCT_COMPANY_STR(print_bill_type, 32) \
	CYCLIENTS_STRUCT_COMPANY_INT(record_type_id) \
	CYCLIENTS_STRUCT_COMPANY_INT(split_records_by_resources) \
	CYCLIENTS_STRUCT_COMPANY_INT(auto_pay_account_id) \
	CYCLIENTS_STRUCT_COMPANY_INT(auto_pay_bank_account_id) \
	CYCLIENTS_STRUCT_COMPANY_INT(is_admin_app) \
	CYCLIENTS_STRUCT_COMPANY_INT(push_notification_phone_confirm) \
	CYCLIENTS_STRUCT_COMPANY_BOL(switched_to_tariff) \
	CYCLIENTS_STRUCT_COMPANY_BOL(sms_enabled) \
	CYCLIENTS_STRUCT_COMPANY_BOL(is_offline_record_notification_enabled) \
	CYCLIENTS_STRUCT_COMPANY_INT(activity_record_clients_count_max) \
	CYCLIENTS_STRUCT_COMPANY_INT(activity_online_record_clients_count_max) \
	CYCLIENTS_STRUCT_COMPANY_BOL(is_individual) \
	CYCLIENTS_STRUCT_COMPANY_BOL(is_tips_enabled) \
	CYCLIENTS_STRUCT_COMPANY_INT(email_hours_default) \
	CYCLIENTS_STRUCT_COMPANY_BOL(is_show_privacy_policy) \
	CYCLIENTS_STRUCT_COMPANY_BOL(is_surname_field_enabled) \
	CYCLIENTS_STRUCT_COMPANY_BOL(is_patronymic_field_enabled) \
	CYCLIENTS_STRUCT_COMPANY_STR(master_name, 32) \
	CYCLIENTS_STRUCT_COMPANY_BOL(is_client_search_by_loyalty_enabled) \
	CYCLIENTS_STRUCT_COMPANY_BOL(is_show_timetable_record_master_resources) \
	CYCLIENTS_STRUCT_COMPANY_SOCIAL(social) \
	CYCLIENTS_STRUCT_COMPANY_INT(main_group_id) \

/* TODO:  <07-11-25, yourname> */

typedef struct cyclients_company_ {
	CYCLIENTS_STRUCT_TYPE _type;
#define CYCLIENTS_STRUCT_COMPANY_STR(_name, _size) char _name[_size];
#define CYCLIENTS_STRUCT_COMPANY_INT(_name) int _name;
#define CYCLIENTS_STRUCT_COMPANY_BOL(_name) bool _name;
#define CYCLIENTS_STRUCT_COMPANY_SAR(_name, _size, _len)
#define CYCLIENTS_STRUCT_COMPANY_SOCIAL(_name)
CYCLIENTS_STRUCT_COMPANY
#undef CYCLIENTS_STRUCT_COMPANY_STR
#undef CYCLIENTS_STRUCT_COMPANY_INT
#undef CYCLIENTS_STRUCT_COMPANY_BOL
#undef CYCLIENTS_STRUCT_COMPANY_SAR
#undef CYCLIENTS_STRUCT_COMPANY_SOCIAL
} cyclients_company_t;

int 
cyclients_company_from_json(const cJSON *json,
						               cyclients_company_t *t);

cJSON * 
cyclients_company_to_json(cyclients_company_t *t);



#endif // STRUCTS_H
