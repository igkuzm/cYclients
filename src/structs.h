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
	CYCLIENTS_STRUCT_TYPE_MAIN_GROUP,
	CYCLIENTS_STRUCT_TYPE_SALON_GROUP_SETTINGS,
	CYCLIENTS_STRUCT_TYPE_BOOKING_WIDGWT_PROMO,
	CYCLIENTS_STRUCT_TYPE_ACCESS,
	CYCLIENTS_STRUCT_TYPE_COMPANY,
	CYCLIENTS_STRUCT_TYPE_SERVICE,
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

// BOOKING WIDGET PROMO
#define CYCLIENTS_STRUCT_BOOKING_WIDGWT_PROMO \
	CYCLIENTS_STRUCT_BOOKING_WIDGWT_PROMO_STR(flocktory_url, 256) \

typedef struct cyclients_booking_widget_promo_ {
	CYCLIENTS_STRUCT_TYPE _type;
#define CYCLIENTS_STRUCT_BOOKING_WIDGWT_PROMO_STR(_name, _size) char _name[_size];
CYCLIENTS_STRUCT_BOOKING_WIDGWT_PROMO
#undef CYCLIENTS_STRUCT_BOOKING_WIDGWT_PROMO_STR
} cyclients_booking_widget_promo_t;

int 
cyclients_booking_widget_promo_from_json(const cJSON *json,
						               cyclients_booking_widget_promo_t *t);

cJSON * 
cyclients_booking_widget_promo_to_json(cyclients_booking_widget_promo_t *t);

// Main Group
#define CYCLIENTS_STRUCT_MAIN_GROUP \
	CYCLIENTS_STRUCT_MAIN_GROUP_INT(id) \
	CYCLIENTS_STRUCT_MAIN_GROUP_STR(title, 64) \

typedef struct cyclients_main_group_ {
	CYCLIENTS_STRUCT_TYPE _type;
#define CYCLIENTS_STRUCT_MAIN_GROUP_INT(_name) int _name;
#define CYCLIENTS_STRUCT_MAIN_GROUP_STR(_name, _size) char _name[_size];
CYCLIENTS_STRUCT_MAIN_GROUP
#undef CYCLIENTS_STRUCT_MAIN_GROUP_INT
#undef CYCLIENTS_STRUCT_MAIN_GROUP_STR
} cyclients_main_group_t;

int 
cyclients_main_group_from_json(const cJSON *json,
						               cyclients_main_group_t *t);

cJSON * 
cyclients_main_group_to_json(cyclients_main_group_t *t);

// Salon Group Settings
#define CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS \
	CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_INT(id) \
	CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_INT(salonGroupId) \
	CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_BOL(isActiveAutofillMaster) \
	CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_BOL(isActiveAddMasterOnlyPhone) \
	CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_BOL(isActiveSettings) \

typedef struct cyclients_salon_group_settings_ {
	CYCLIENTS_STRUCT_TYPE _type;
#define CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_INT(_name) int _name;
#define CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_BOL(_name) bool _name;
CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS
#undef CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_INT
#undef CYCLIENTS_STRUCT_SALON_GROUP_SETTINGS_BOL
} cyclients_salon_group_settings_t;

int 
cyclients_salon_group_settings_from_json(const cJSON *json,
						               cyclients_salon_group_settings_t *t);

cJSON * 
cyclients_salon_group_settings_to_json(cyclients_salon_group_settings_t *t);

// ACCESS
#define CYCLIENTS_STRUCT_ACCESS \
	CYCLIENTS_STRUCT_ACCESS_BOL(timetable_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(master_id) \
	CYCLIENTS_STRUCT_ACCESS_INT(position_id) \
	CYCLIENTS_STRUCT_ACCESS_INT(last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(schedule_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(timetable_phones_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(timetable_transferring_record_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(timetable_statistics_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(timetable_waiting_list_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(record_form_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(record_form_client_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(record_form_client_add_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_autocomplete_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_autocomplete_phone_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(create_records_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(edit_records_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(records_edit_last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_edit_date_and_master_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_edit_duration_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_edit_comment_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_edit_services_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(edit_records_attendance_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_services_cost_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_services_discount_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(record_edit_full_paid_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(record_edit_full_paid_client_came_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(record_edit_full_paid_client_confirm_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(delete_records_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(delete_customer_came_records_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(delete_paid_records_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_goods_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_goods_create_transaction_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(records_goods_create_last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_goods_edit_transaction_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(records_goods_edit_last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_goods_cost_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_goods_discount_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_finances_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(records_finances_last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_finances_accounts_limited_access) \
	CYCLIENTS_STRUCT_ACCESS_AIN(records_finances_limited_accounts_ids, 32) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_finances_pay_from_deposits_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_group_id_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(records_group_id) \
	CYCLIENTS_STRUCT_ACCESS_BOL(records_consumables_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(custom_fields_record_values_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(custom_fields_record_values_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(custom_fields_client_values_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(custom_fields_client_values_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_accounts_limited_access) \
	CYCLIENTS_STRUCT_ACCESS_AIN(finances_accounts_ids, 32) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(finances_last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_create_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(finances_create_last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_edit_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_edit_last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_delete_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_transactions_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_AIN(finances_expenses_ids, 32) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_accounts_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_accounts_banalce_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_suppliers_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_suppliers_create_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_suppliers_update_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_suppliers_delete_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_suppliers_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_expenses_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(expenses_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_expenses_create_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(expenses_create_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_expenses_update_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(expenses_update_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_expenses_delete_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(expenses_delete_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_kkm_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(kkm_transactions_accounts_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_kkm_settings_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(kkm_settings_reed_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_kkm_settings_update_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(kkm_settings_update_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_settings_invoicing_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_invoicing_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_settings_invoicing_update_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_invoicing_update_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_options_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(options_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_options_update_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(options_update_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_salary_schemes_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_salary_calc_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_salary_not_limitation_today_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_payroll_calculation_create_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_payroll_calculation_create_not_limitation_today_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_salary_access_master_checkbox) \
	CYCLIENTS_STRUCT_ACCESS_INT(finances_salary_access_master_id) \
	CYCLIENTS_STRUCT_ACCESS_INT(get_salary_access_master_id) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_salary_master_not_limitation_today_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_payroll_calculation_create_by_master_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(calculation_create_by_master_not_limitation_today_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_period_report_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_period_report_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_year_report_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_year_report_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_print_check_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_z_report_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_z_report_no_limit_today_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(finances_z_report_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(client_phones_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_phones_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_phones_email_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_surname_patronymic_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_surname_patronymic_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_loyalty_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_card_phone_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_card_comment_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_card_comment_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_delete_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(client_comments_list_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(client_comments_add_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(client_comments_own_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(client_comments_other_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(client_files_list_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(client_files_upload_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(client_files_delete_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(clients_visit_master_id) \
	CYCLIENTS_STRUCT_ACCESS_INT(get_visit_master_id) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_show_attendance_history_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_deposits_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_deposits_create_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_deposits_topup_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_deposits_history_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(clients_loyalty_settings_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dashboard_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dash_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dash_phones_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dash_records_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(dash_records_last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dash_records_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dash_records_phones_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dash_message_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dash_message_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dash_message_phones_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dash_reviews_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dash_reviews_delete_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dashboard_calls_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dashboard_calls_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(dashboard_calls_phones_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(security_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(security_2fa_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(security_data_changes_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(security_export_import_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(security_logins_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(security_employee_changes_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(loyalty_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(has_loyalty_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(loyalty_cards_manual_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(loyalty_abonement_balance_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(loyalty_abonement_period_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(loyalty_abonement_history_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(loyalty_certificate_balance_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(loyalty_certificate_period_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(loyalty_cards_issue_and_removal_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(has_loyalty_cards_manual_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(loyalty_certificate_and_abonement_manual_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_limited_access) \
	CYCLIENTS_STRUCT_ACCESS_AIN(storages_ids, 32) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_prime_cost_view_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(storages_last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_move_goods_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_create_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(storages_create_last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_create_transactions_buy_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_create_transactions_sale_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_edit_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_INT(storages_edit_last_days_count) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_edit_transactions_buy_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_edit_transactions_sale_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_delete_transactions_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_transactions_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_AIN(storages_transactions_types, 32) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_inventory_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_inventory_create_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_inventory_delete_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_inventory_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_remnants_report_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_remnants_report_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_sales_report_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_sales_report_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_consumable_report_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_consumable_report_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_write_off_report_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_write_off_report_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_turnover_report_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_turnover_report_excel_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_crud_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_create_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_update_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_title_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_category_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_selling_price_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_cost_price_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_units_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_critical_balance_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_masses_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_comment_edit_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_archive_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(storages_goods_delete_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_basis_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_information_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(users_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(delete_users_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(create_users_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(edit_users_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(limited_users_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_user_notifications_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_services_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_services_create_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(services_edit) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_services_edit_title_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_services_relation_category_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_services_edit_price_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_services_edit_image_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_services_edit_online_seance_date_time_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_services_edit_online_pay_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_services_edit_services_related_resource_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_positions_read) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_positions_create) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_positions_delete) \
	CYCLIENTS_STRUCT_ACCESS_BOL(edit_master_service_and_duration) \
	CYCLIENTS_STRUCT_ACCESS_BOL(tech_card_edit) \
	CYCLIENTS_STRUCT_ACCESS_BOL(services_delete) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_master_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(master_create) \
	CYCLIENTS_STRUCT_ACCESS_BOL(master_edit) \
	CYCLIENTS_STRUCT_ACCESS_BOL(master_delete) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_master_dismiss_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(schedule_edit) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_notifications_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_email_notifications_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_template_notifications_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(webhook_read_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(is_salon_tips_manager) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_close_docs_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(settings_clients_labels_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(stat_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(analytics_constructor_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(billing_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(billing_invoices_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(tips_setup_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(send_sms) \
	CYCLIENTS_STRUCT_ACCESS_BOL(salon_to_salon_group_add_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(auth_enable_check_ip) \
	CYCLIENTS_STRUCT_ACCESS_AST(auth_list_allowed_ip, 16, 32) \
	CYCLIENTS_STRUCT_ACCESS_BOL(online_record_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(online_record_privacy_policy_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(comers_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(comers_info_vehicle_view_access) \
	CYCLIENTS_STRUCT_ACCESS_BOL(comers_info_vehicle_edit_access) \

typedef struct cyclients_access_ {
	CYCLIENTS_STRUCT_TYPE _type;
#define CYCLIENTS_STRUCT_ACCESS_INT(_name) int _name;
#define CYCLIENTS_STRUCT_ACCESS_BOL(_name) bool _name;
#define CYCLIENTS_STRUCT_ACCESS_AIN(_name, _len) int _name[_len];
#define CYCLIENTS_STRUCT_ACCESS_AST(_name, _size, _len) char _name[_len][_size];
CYCLIENTS_STRUCT_ACCESS
#undef CYCLIENTS_STRUCT_ACCESS_INT
#undef CYCLIENTS_STRUCT_ACCESS_BOL
#undef CYCLIENTS_STRUCT_ACCESS_AIN
#undef CYCLIENTS_STRUCT_ACCESS_AST
} cyclients_access_t;

int 
cyclients_access_from_json(const cJSON *json,
						               cyclients_access_t *t);

cJSON * 
cyclients_access_to_json(cyclients_access_t *t);

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
	CYCLIENTS_STRUCT_COMPANY_AST(phones, 32, 32) \
	CYCLIENTS_STRUCT_COMPANY_STR(email, 32) \
	CYCLIENTS_STRUCT_COMPANY_INT(timezone) \
	CYCLIENTS_STRUCT_COMPANY_STR(timezone_name, 32) \
	CYCLIENTS_STRUCT_COMPANY_STR(schedule, 32) \
	CYCLIENTS_STRUCT_COMPANY_STR(address, 256) \
	CYCLIENTS_STRUCT_COMPANY_DOB(coordinate_lat) \
	CYCLIENTS_STRUCT_COMPANY_DOB(coordinate_lon) \
	CYCLIENTS_STRUCT_COMPANY_STR(app_ios, 32) \
	CYCLIENTS_STRUCT_COMPANY_STR(app_android, 32) \
	CYCLIENTS_STRUCT_COMPANY_BOL(phone_confirmation) \
	CYCLIENTS_STRUCT_COMPANY_STR(currency_short_title, 8) \
	CYCLIENTS_STRUCT_COMPANY_BOL(reminds_sms_disabled) \
	CYCLIENTS_STRUCT_COMPANY_INT(reminds_sms_default) \
	CYCLIENTS_STRUCT_COMPANY_INT(group_priority) \
	CYCLIENTS_STRUCT_COMPANY_INT(bookform_group_priority) \
	CYCLIENTS_STRUCT_COMPANY_STR(description, BUFSIZ) \
	CYCLIENTS_STRUCT_COMPANY_AST(photos, 256, 32) \
	CYCLIENTS_STRUCT_COMPANY_AST(company_photos, 256, 32) \
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
	CYCLIENTS_STRUCT_COMPANY_MAIN_GROUP(main_group) \
	CYCLIENTS_STRUCT_COMPANY_MAIN_SALON_GROUP_SETTINGS(salon_group_settings) \
	CYCLIENTS_STRUCT_COMPANY_BOL(booking_comment_required) \
	CYCLIENTS_STRUCT_COMPANY_BOL(booking_email_required) \
	CYCLIENTS_STRUCT_COMPANY_BOL(booking_comment_hidden) \
	CYCLIENTS_STRUCT_COMPANY_BOL(booking_surname_required) \
	CYCLIENTS_STRUCT_COMPANY_BOL(booking_patronymic_required) \
	CYCLIENTS_STRUCT_COMPANY_BOOKING_WIDET_PROMO(booking_widget_promo) \
	CYCLIENTS_STRUCT_COMPANY_INT(balance) \
	CYCLIENTS_STRUCT_COMPANY_DOB(sms_price) \
	CYCLIENTS_STRUCT_COMPANY_ACCESS(access) \

typedef struct cyclients_company_ {
	CYCLIENTS_STRUCT_TYPE _type;
#define CYCLIENTS_STRUCT_COMPANY_STR(_name, _size) char _name[_size];
#define CYCLIENTS_STRUCT_COMPANY_INT(_name) int _name;
#define CYCLIENTS_STRUCT_COMPANY_BOL(_name) bool _name;
#define CYCLIENTS_STRUCT_COMPANY_AST(_name, _size, _len) \
	char _name[_len][_size];
#define CYCLIENTS_STRUCT_COMPANY_DOB(_name) double _name;
#define CYCLIENTS_STRUCT_COMPANY_SOCIAL(_name) \
	cyclients_social_t _name;
#define CYCLIENTS_STRUCT_COMPANY_MAIN_GROUP(_name) \
	cyclients_main_group_t _name;
#define CYCLIENTS_STRUCT_COMPANY_MAIN_SALON_GROUP_SETTINGS(_name) \
	cyclients_salon_group_settings_t _name;
#define CYCLIENTS_STRUCT_COMPANY_BOOKING_WIDET_PROMO(_name) \
	cyclients_booking_widget_promo_t _name;
#define CYCLIENTS_STRUCT_COMPANY_ACCESS(_name) \
	cyclients_access_t _name;
CYCLIENTS_STRUCT_COMPANY
#undef CYCLIENTS_STRUCT_COMPANY_STR
#undef CYCLIENTS_STRUCT_COMPANY_INT
#undef CYCLIENTS_STRUCT_COMPANY_BOL
#undef CYCLIENTS_STRUCT_COMPANY_AST
#undef CYCLIENTS_STRUCT_COMPANY_DOB
#undef CYCLIENTS_STRUCT_COMPANY_SOCIAL
#undef CYCLIENTS_STRUCT_COMPANY_MAIN_GROUP
#undef CYCLIENTS_STRUCT_COMPANY_MAIN_SALON_GROUP_SETTINGS
#undef CYCLIENTS_STRUCT_COMPANY_BOOKING_WIDET_PROMO
#undef CYCLIENTS_STRUCT_COMPANY_ACCESS
} cyclients_company_t;

int 
cyclients_company_from_json(const cJSON *json,
						               cyclients_company_t *t);

cJSON * 
cyclients_company_to_json(cyclients_company_t *t);

/*
 "booking_title":        "Предоплата",
 "tax_variant":  null,
 "vat_id":       null,
 "print_title":  "",
 "service_type": 1,
 "api_service_id":       0,
 "repeat_visit_days_step":       null,
 "seance_search_start":  0,
 "seance_search_finish": 86400,
 "seance_search_step":   900,
 "step": 0,
 "is_need_limit_date":   false,
 "date_from":    "0000-00-00",
 "date_to":      "0000-00-00",
 "schedule_template_type":       2,
 "online_invoicing_status":      0,
 "is_abonement_autopayment_enabled":     0,
 "autopayment_before_visit_time":        0,
 "abonement_restriction_value":  0,
 "is_chain":     false,
 "is_price_managed_only_in_chain":       false,
 "is_comment_managed_only_in_chain":     false,
 "price_prepaid_amount": 0,
 "price_prepaid_percent":        100,
 "is_composite": false,
 "technical_break_duration":     null,
 "default_technical_break_duration":     0,
 "id":   18903446,
 "salon_service_id":     21367946,
 "title":        "Предоплата",
 "category_id":  18565171,
 "price_min":    0,
 "price_max":    0,
 "discount":     0,
 "comment":      "",
 "weight":       0,
 "active":       1,
 "api_id":       "0",
 "prepaid":      "forbidden",
 "is_multi":     false,
 "capacity":     0,
 "image_group":  [],
 "staff":        [{
                 "id":   3743417,
                 "seance_length":        0,
                 "technological_card_id":        0,
                 "image_url":    "https://be.cdn.yclients.com/images/no-master-sm.png",
                 "price":        null,
                 "name": "Сухроб Солиевич"
         }, {
                 "id":   3732061,
                 "seance_length":        0,
                 "technological_card_id":        0,
                 "image_url":    "https://be.cdn.yclients.com/images/no-master-sm.png",
                 "price":        null,
                 "name": "Азиз Ибрагимович"
         }, {
                 "id":   3813232,
                 "seance_length":        0,
                 "technological_card_id":        0,
                 "image_url":    "https://be.cdn.yclients.com/images/no-master-sm.png",
                 "price":        null,
                 "name": "Трейбич Маргарита Александровна"
         }, {
                 "id":   3813235,
                 "seance_length":        0,
                 "technological_card_id":        0,
                 "image_url":    "https://be.cdn.yclients.com/images/no-master-sm.png",
                 "price":        null,
                 "name": "Доктор Ху"
         }, {
                 "id":   3862837,
                 "seance_length":        0,
                 "technological_card_id":        0,
                 "image_url":    "https://be.cdn.yclients.com/images/no-master-sm.png",
                 "price":        null,
                 "name": "Доктор Го"
         }],
 "dates":        [],
 "duration":     1800,
 "resources":    [],
 "is_online":    true
*/

typedef struct cyclients_service_ {
	CYCLIENTS_STRUCT_TYPE _type;
} cyclients_service_t;

#endif // STRUCTS_H
