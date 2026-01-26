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
#include <stdlib.h>
#include <time.h>
#include "cJSON.h"
#include "config.h"

struct kvpair{char *key; char *value;};

typedef	enum {
	CYC_TYPE_NULL,
	CYC_TYPE_USER,
	CYC_TYPE_TRANSPORT,
	CYC_TYPE_2FA,
	CYC_TYPE_SOCIAL,
	CYC_TYPE_MAIN_GROUP,
	CYC_TYPE_SALON_GROUP_SETTINGS,
	CYC_TYPE_BOOKING_WIDGET_PROMO,
	CYC_TYPE_ACCESS,
	CYC_TYPE_COMPANY,
	CYC_TYPE_SERVICE_CATEGORY,
	CYC_TYPE_STAFF,
	CYC_TYPE_SERVICE,
	CYC_TYPE_USER_ROLE,
	CYC_TYPE_USER_PERMISSIONS,
  CYC_TYPE_FILE,
  CYC_TYPE_VISIT_SERVICE,
  CYC_TYPE_DOCUMENT,
  CYC_TYPE_RECORD,
  CYC_TYPE_CLIENT,
	CYC_TYPE_COMMENT,
	CYC_NTYPES,
} CYC_TYPE;

// user
#define CYC_USER \
	CYC_INT(id) \
	CYC_STRING(user_token, 64) \
	CYC_STRING(name, 64) \
	CYC_STRING(phone, 32) \
	CYC_STRING(login, 32) \
	CYC_STRING(email, 64) \
	CYC_STRING(avatar, 256) \
	CYC_BOOL(is_approved) \
	CYC_BOOL(is_email_confirmed) \

// transport
#define CYC_TRANSPORT \
	CYC_STRING(type, 64) \
	CYC_STRING(recipient, 128) \

// 2 FA
#define CYC_2FA \
	CYC_STRING(uuid, 64) \
	CYC_STRING(flow, 32) \
	CYC_TRANSPORT_CLASS(transport) \
	CYC_INT(refresh_ttl_sec) \
	CYC_INT(attempts_left) \

// SOCIAL
#define CYC_SOCIAL \
	CYC_STRING(facebook, 64) \
	CYC_STRING(vk, 64) \
	CYC_STRING(instagram, 64) \
	CYC_STRING(telegram, 64) \
	CYC_STRING(whatsapp, 64) \
	CYC_STRING(viber, 64) \

// BOOKING WIDGET PROMO
#define CYC_BOOKING_WIDGET_PROMO \
	CYC_STRING(flocktory_url, 256) \

// Main Group
#define CYC_MAIN_GROUP \
	CYC_INT(id) \
	CYC_STRING(title, 64) \

// Salon Group Settings
#define CYC_SALON_GROUP_SETTINGS \
	CYC_INT(id) \
	CYC_INT(salonGroupId) \
	CYC_BOOL(isActiveAutofillMaster) \
	CYC_BOOL(isActiveAddMasterOnlyPhone) \
	CYC_BOOL(isActiveSettings) \

// ACCESS
#define CYC_ACCESS \
	CYC_BOOL(timetable_access) \
	CYC_INT(master_id) \
	CYC_INT(position_id) \
	CYC_INT(last_days_count) \
	CYC_BOOL(schedule_edit_access) \
	CYC_BOOL(timetable_phones_access) \
	CYC_BOOL(timetable_transferring_record_access) \
	CYC_BOOL(timetable_statistics_access) \
	CYC_BOOL(timetable_waiting_list_access) \
	CYC_BOOL(record_form_access) \
	CYC_BOOL(record_form_client_access) \
	CYC_BOOL(record_form_client_add_access) \
	CYC_BOOL(records_autocomplete_access) \
	CYC_BOOL(records_autocomplete_phone_access) \
	CYC_BOOL(create_records_access) \
	CYC_BOOL(edit_records_access) \
	CYC_INT(records_edit_last_days_count) \
	CYC_BOOL(records_edit_date_and_master_access) \
	CYC_BOOL(records_edit_duration_access) \
	CYC_BOOL(records_edit_comment_access) \
	CYC_BOOL(records_edit_services_access) \
	CYC_BOOL(edit_records_attendance_access) \
	CYC_BOOL(records_services_cost_access) \
	CYC_BOOL(records_services_discount_access) \
	CYC_BOOL(record_edit_full_paid_access) \
	CYC_BOOL(record_edit_full_paid_client_came_access) \
	CYC_BOOL(record_edit_full_paid_client_confirm_access) \
	CYC_BOOL(delete_records_access) \
	CYC_BOOL(delete_customer_came_records_access) \
	CYC_BOOL(delete_paid_records_access) \
	CYC_BOOL(records_goods_access) \
	CYC_BOOL(records_goods_create_transaction_access) \
	CYC_INT(records_goods_create_last_days_count) \
	CYC_BOOL(records_goods_edit_transaction_access) \
	CYC_INT(records_goods_edit_last_days_count) \
	CYC_BOOL(records_goods_cost_access) \
	CYC_BOOL(records_goods_discount_access) \
	CYC_BOOL(records_finances_access) \
	CYC_INT(records_finances_last_days_count) \
	CYC_BOOL(records_finances_accounts_limited_access) \
	CYC_INT_ARRAY(records_finances_limited_accounts_ids, 32) \
	CYC_BOOL(records_finances_pay_from_deposits_access) \
	CYC_BOOL(records_group_id_access) \
	CYC_INT(records_group_id) \
	CYC_BOOL(records_consumables_edit_access) \
	CYC_BOOL(custom_fields_record_values_read_access) \
	CYC_BOOL(custom_fields_record_values_edit_access) \
	CYC_BOOL(custom_fields_client_values_read_access) \
	CYC_BOOL(custom_fields_client_values_edit_access) \
	CYC_BOOL(finances_access) \
	CYC_BOOL(finances_accounts_limited_access) \
	CYC_INT_ARRAY(finances_accounts_ids, 32) \
	CYC_BOOL(finances_transactions_access) \
	CYC_INT(finances_last_days_count) \
	CYC_BOOL(finances_create_transactions_access) \
	CYC_INT(finances_create_last_days_count) \
	CYC_BOOL(finances_edit_transactions_access) \
	CYC_BOOL(finances_edit_last_days_count) \
	CYC_BOOL(finances_delete_transactions_access) \
	CYC_BOOL(finances_transactions_excel_access) \
	CYC_INT_ARRAY(finances_expenses_ids, 32) \
	CYC_BOOL(finances_accounts_access) \
	CYC_BOOL(finances_accounts_banalce_access) \
	CYC_BOOL(finances_suppliers_read_access) \
	CYC_BOOL(finances_suppliers_create_access) \
	CYC_BOOL(finances_suppliers_update_access) \
	CYC_BOOL(finances_suppliers_delete_access) \
	CYC_BOOL(finances_suppliers_excel_access) \
	CYC_BOOL(finances_expenses_read_access) \
	CYC_BOOL(expenses_read_access) \
	CYC_BOOL(finances_expenses_create_access) \
	CYC_BOOL(expenses_create_access) \
	CYC_BOOL(finances_expenses_update_access) \
	CYC_BOOL(expenses_update_access) \
	CYC_BOOL(finances_expenses_delete_access) \
	CYC_BOOL(expenses_delete_access) \
	CYC_BOOL(finances_kkm_transactions_access) \
	CYC_BOOL(kkm_transactions_accounts_access) \
	CYC_BOOL(finances_kkm_settings_read_access) \
	CYC_BOOL(kkm_settings_reed_access) \
	CYC_BOOL(finances_kkm_settings_update_access) \
	CYC_BOOL(kkm_settings_update_access) \
	CYC_BOOL(finances_settings_invoicing_read_access) \
	CYC_BOOL(settings_invoicing_read_access) \
	CYC_BOOL(finances_settings_invoicing_update_access) \
	CYC_BOOL(settings_invoicing_update_access) \
	CYC_BOOL(finances_options_read_access) \
	CYC_BOOL(options_read_access) \
	CYC_BOOL(finances_options_update_access) \
	CYC_BOOL(options_update_access) \
	CYC_BOOL(finances_salary_schemes_access) \
	CYC_BOOL(finances_salary_calc_access) \
	CYC_BOOL(finances_salary_not_limitation_today_access) \
	CYC_BOOL(finances_payroll_calculation_create_access) \
	CYC_BOOL(finances_payroll_calculation_create_not_limitation_today_access) \
	CYC_BOOL(finances_salary_access_master_checkbox) \
	CYC_INT(finances_salary_access_master_id) \
	CYC_INT(get_salary_access_master_id) \
	CYC_BOOL(finances_salary_master_not_limitation_today_access) \
	CYC_BOOL(finances_payroll_calculation_create_by_master_access) \
	CYC_BOOL(calculation_create_by_master_not_limitation_today_access) \
	CYC_BOOL(finances_period_report_access) \
	CYC_BOOL(finances_period_report_excel_access) \
	CYC_BOOL(finances_year_report_access) \
	CYC_BOOL(finances_year_report_excel_access) \
	CYC_BOOL(finances_print_check_access) \
	CYC_BOOL(finances_z_report_access) \
	CYC_BOOL(finances_z_report_no_limit_today_access) \
	CYC_BOOL(finances_z_report_excel_access) \
	CYC_BOOL(clients_access) \
	CYC_BOOL(client_phones_access) \
	CYC_BOOL(clients_phones_access) \
	CYC_BOOL(clients_phones_email_access) \
	CYC_BOOL(clients_surname_patronymic_access) \
	CYC_BOOL(clients_surname_patronymic_edit_access) \
	CYC_BOOL(clients_edit_access) \
	CYC_BOOL(clients_loyalty_read_access) \
	CYC_BOOL(clients_card_phone_access) \
	CYC_BOOL(clients_card_comment_access) \
	CYC_BOOL(clients_card_comment_edit_access) \
	CYC_BOOL(clients_delete_access) \
	CYC_BOOL(clients_excel_access) \
	CYC_BOOL(excel_access) \
	CYC_BOOL(client_comments_list_access) \
	CYC_BOOL(client_comments_add_access) \
	CYC_BOOL(client_comments_own_edit_access) \
	CYC_BOOL(client_comments_other_edit_access) \
	CYC_BOOL(client_files_list_access) \
	CYC_BOOL(client_files_upload_access) \
	CYC_BOOL(client_files_delete_access) \
	CYC_INT(clients_visit_master_id) \
	CYC_INT(get_visit_master_id) \
	CYC_BOOL(clients_show_attendance_history_access) \
	CYC_BOOL(clients_deposits_access) \
	CYC_BOOL(clients_deposits_create_access) \
	CYC_BOOL(clients_deposits_topup_access) \
	CYC_BOOL(clients_deposits_history_access) \
	CYC_BOOL(clients_loyalty_settings_access) \
	CYC_BOOL(dashboard_access) \
	CYC_BOOL(dash_access) \
	CYC_BOOL(dash_phones_access) \
	CYC_BOOL(dash_records_access) \
	CYC_INT(dash_records_last_days_count) \
	CYC_BOOL(dash_records_excel_access) \
	CYC_BOOL(dash_records_phones_access) \
	CYC_BOOL(dash_message_access) \
	CYC_BOOL(dash_message_excel_access) \
	CYC_BOOL(dash_message_phones_access) \
	CYC_BOOL(dash_reviews_access) \
	CYC_BOOL(dash_reviews_delete_access) \
	CYC_BOOL(dashboard_calls_access) \
	CYC_BOOL(dashboard_calls_excel_access) \
	CYC_BOOL(dashboard_calls_phones_access) \
	CYC_BOOL(security_access) \
	CYC_BOOL(security_2fa_access) \
	CYC_BOOL(security_data_changes_access) \
	CYC_BOOL(security_export_import_access) \
	CYC_BOOL(security_logins_access) \
	CYC_BOOL(security_employee_changes_access) \
	CYC_BOOL(loyalty_access) \
	CYC_BOOL(has_loyalty_access) \
	CYC_BOOL(loyalty_cards_manual_transactions_access) \
	CYC_BOOL(loyalty_abonement_balance_edit_access) \
	CYC_BOOL(loyalty_abonement_period_edit_access) \
	CYC_BOOL(loyalty_abonement_history_access) \
	CYC_BOOL(loyalty_certificate_balance_edit_access) \
	CYC_BOOL(loyalty_certificate_period_edit_access) \
	CYC_BOOL(loyalty_cards_issue_and_removal_access) \
	CYC_BOOL(has_loyalty_cards_manual_transactions_access) \
	CYC_BOOL(loyalty_certificate_and_abonement_manual_transactions_access) \
	CYC_BOOL(storages_access) \
	CYC_BOOL(storages_limited_access) \
	CYC_INT_ARRAY(storages_ids, 32) \
	CYC_BOOL(storages_goods_prime_cost_view_access) \
	CYC_BOOL(storages_transactions_access) \
	CYC_INT(storages_last_days_count) \
	CYC_BOOL(storages_move_goods_access) \
	CYC_BOOL(storages_create_transactions_access) \
	CYC_INT(storages_create_last_days_count) \
	CYC_BOOL(storages_create_transactions_buy_access) \
	CYC_BOOL(storages_create_transactions_sale_access) \
	CYC_BOOL(storages_edit_transactions_access) \
	CYC_INT(storages_edit_last_days_count) \
	CYC_BOOL(storages_edit_transactions_buy_access) \
	CYC_BOOL(storages_edit_transactions_sale_access) \
	CYC_BOOL(storages_delete_transactions_access) \
	CYC_BOOL(storages_transactions_excel_access) \
	CYC_INT_ARRAY(storages_transactions_types, 32) \
	CYC_BOOL(storages_inventory_access) \
	CYC_BOOL(storages_inventory_create_edit_access) \
	CYC_BOOL(storages_inventory_delete_access) \
	CYC_BOOL(storages_inventory_excel_access) \
	CYC_BOOL(storages_remnants_report_access) \
	CYC_BOOL(storages_remnants_report_excel_access) \
	CYC_BOOL(storages_sales_report_access) \
	CYC_BOOL(storages_sales_report_excel_access) \
	CYC_BOOL(storages_consumable_report_access) \
	CYC_BOOL(storages_consumable_report_excel_access) \
	CYC_BOOL(storages_write_off_report_access) \
	CYC_BOOL(storages_write_off_report_excel_access) \
	CYC_BOOL(storages_turnover_report_access) \
	CYC_BOOL(storages_turnover_report_excel_access) \
	CYC_BOOL(storages_goods_crud_access) \
	CYC_BOOL(storages_goods_create_access) \
	CYC_BOOL(storages_goods_update_access) \
	CYC_BOOL(storages_goods_title_edit_access) \
	CYC_BOOL(storages_goods_category_edit_access) \
	CYC_BOOL(storages_goods_selling_price_edit_access) \
	CYC_BOOL(storages_goods_cost_price_edit_access) \
	CYC_BOOL(storages_goods_units_edit_access) \
	CYC_BOOL(storages_goods_critical_balance_edit_access) \
	CYC_BOOL(storages_goods_masses_edit_access) \
	CYC_BOOL(storages_goods_comment_edit_access) \
	CYC_BOOL(storages_goods_archive_access) \
	CYC_BOOL(storages_goods_delete_access) \
	CYC_BOOL(settings_access) \
	CYC_BOOL(settings_basis_access) \
	CYC_BOOL(settings_information_access) \
	CYC_BOOL(users_access) \
	CYC_BOOL(delete_users_access) \
	CYC_BOOL(create_users_access) \
	CYC_BOOL(edit_users_access) \
	CYC_BOOL(limited_users_access) \
	CYC_BOOL(settings_user_notifications_access) \
	CYC_BOOL(settings_services_access) \
	CYC_BOOL(settings_services_create_access) \
	CYC_BOOL(services_edit) \
	CYC_BOOL(settings_services_edit_title_access) \
	CYC_BOOL(settings_services_relation_category_access) \
	CYC_BOOL(settings_services_edit_price_access) \
	CYC_BOOL(settings_services_edit_image_access) \
	CYC_BOOL(settings_services_edit_online_seance_date_time_access) \
	CYC_BOOL(settings_services_edit_online_pay_access) \
	CYC_BOOL(settings_services_edit_services_related_resource_access) \
	CYC_BOOL(settings_positions_read) \
	CYC_BOOL(settings_positions_create) \
	CYC_BOOL(settings_positions_delete) \
	CYC_BOOL(edit_master_service_and_duration) \
	CYC_BOOL(tech_card_edit) \
	CYC_BOOL(services_delete) \
	CYC_BOOL(settings_master_access) \
	CYC_BOOL(master_create) \
	CYC_BOOL(master_edit) \
	CYC_BOOL(master_delete) \
	CYC_BOOL(settings_master_dismiss_access) \
	CYC_BOOL(schedule_edit) \
	CYC_BOOL(settings_notifications_access) \
	CYC_BOOL(settings_email_notifications_access) \
	CYC_BOOL(settings_template_notifications_access) \
	CYC_BOOL(webhook_read_access) \
	CYC_BOOL(is_salon_tips_manager) \
	CYC_BOOL(settings_close_docs_access) \
	CYC_BOOL(settings_clients_labels_access) \
	CYC_BOOL(stat_access) \
	CYC_BOOL(analytics_constructor_access) \
	CYC_BOOL(billing_access) \
	CYC_BOOL(billing_invoices_access) \
	CYC_BOOL(tips_setup_access) \
	CYC_BOOL(send_sms) \
	CYC_BOOL(salon_to_salon_group_add_access) \
	CYC_BOOL(auth_enable_check_ip) \
	CYC_STRING_ARRAY(auth_list_allowed_ip, 16, 32) \
	CYC_BOOL(online_record_access) \
	CYC_BOOL(online_record_privacy_policy_access) \
	CYC_BOOL(comers_access) \
	CYC_BOOL(comers_info_vehicle_view_access) \
	CYC_BOOL(comers_info_vehicle_edit_access) \

// COMPANY
#define CYC_COMPANY \
	CYC_INT(id) \
	CYC_STRING(title, 64) \
	CYC_STRING(public_title, 64) \
	CYC_STRING(short_descr, 64) \
	CYC_STRING(logo, 256) \
	CYC_INT(country_id) \
	CYC_STRING(country, 32) \
	CYC_INT(city_id) \
	CYC_STRING(city, 32) \
	CYC_INT(active) \
	CYC_STRING(phone, 32) \
	CYC_STRING_ARRAY(phones, 32, 32) \
	CYC_STRING(email, 32) \
	CYC_INT(timezone) \
	CYC_STRING(timezone_name, 32) \
	CYC_STRING(schedule, 32) \
	CYC_STRING(address, 256) \
	CYC_DOUBLE(coordinate_lat) \
	CYC_DOUBLE(coordinate_lon) \
	CYC_STRING(app_ios, 32) \
	CYC_STRING(app_android, 32) \
	CYC_BOOL(phone_confirmation) \
	CYC_STRING(currency_short_title, 8) \
	CYC_BOOL(reminds_sms_disabled) \
	CYC_INT(reminds_sms_default) \
	CYC_INT(group_priority) \
	CYC_INT(bookform_group_priority) \
	CYC_STRING(description, BUFSIZ) \
	CYC_STRING_ARRAY(photos, 256, 32) \
	CYC_STRING_ARRAY(company_photos, 256, 32) \
	CYC_INT(seance_delay_step) \
	CYC_BOOL(show_any_master) \
	CYC_BOOL(allow_delete_record) \
	CYC_BOOL(allow_change_record) \
	CYC_BOOL(allow_change_prepaid_record) \
	CYC_BOOL(allow_delete_prepaid_record) \
	CYC_INT(prepayment_waiting_duration_ms) \
	CYC_INT(allow_change_record_delay_step) \
	CYC_INT(allow_delete_record_delay_step) \
	CYC_BOOL(timetable_off) \
	CYC_STRING(site, 128) \
	CYC_STRING(zip, 16) \
	CYC_INT(business_group_id) \
	CYC_INT(business_type_id) \
	CYC_BOOL(is_charge_active) \
	CYC_BOOL(is_charge_optional) \
	CYC_BOOL(is_abonement_restriction_enabled) \
	CYC_INT(print_bill_on) \
	CYC_STRING(print_bill_type, 32) \
	CYC_INT(record_type_id) \
	CYC_INT(split_records_by_resources) \
	CYC_INT(auto_pay_account_id) \
	CYC_INT(auto_pay_bank_account_id) \
	CYC_INT(is_admin_app) \
	CYC_INT(push_notification_phone_confirm) \
	CYC_BOOL(switched_to_tariff) \
	CYC_BOOL(sms_enabled) \
	CYC_BOOL(is_offline_record_notification_enabled) \
	CYC_INT(activity_record_clients_count_max) \
	CYC_INT(activity_online_record_clients_count_max) \
	CYC_BOOL(is_individual) \
	CYC_BOOL(is_tips_enabled) \
	CYC_INT(email_hours_default) \
	CYC_BOOL(is_show_privacy_policy) \
	CYC_BOOL(is_surname_field_enabled) \
	CYC_BOOL(is_patronymic_field_enabled) \
	CYC_STRING(master_name, 32) \
	CYC_BOOL(is_client_search_by_loyalty_enabled) \
	CYC_BOOL(is_show_timetable_record_master_resources) \
	CYC_SOCIAL_CLASS(social) \
	CYC_INT(main_group_id) \
	CYC_MAIN_GROUP_CLASS(main_group) \
	CYC_SALON_GROUP_SETTINGS_CLASS(salon_group_settings) \
	CYC_BOOL(booking_comment_required) \
	CYC_BOOL(booking_email_required) \
	CYC_BOOL(booking_comment_hidden) \
	CYC_BOOL(booking_surname_required) \
	CYC_BOOL(booking_patronymic_required) \
	CYC_BOOKING_WIDGET_PROMO_CLASS(booking_widget_promo) \
	CYC_INT(balance) \
	CYC_DOUBLE(sms_price) \
	CYC_ACCESS_CLASS(access) \

#define CYC_SERVICE_CATEGORY \
	CYC_INT(id) \
	CYC_INT(category_id) \
	CYC_INT(salon_service_id) \
	CYC_STRING(title, 64) \
	CYC_INT(weight) \
	CYC_STRING(api_id, 16) \
	CYC_INT_ARRAY(staff, 32) \
	CYC_STRING(booking_title, 64) \
	CYC_DOUBLE(price_min) \
	CYC_DOUBLE(price_max) \
	CYC_INT(sex) \
	CYC_BOOL(is_chain) \

#define CYC_STAFF \
	CYC_INT(id) \
	CYC_INT(seance_length) \
	CYC_INT(technological_card_id) \
	CYC_STRING(image_url, 256) \
	CYC_INT(price) \
	CYC_STRING(name, 64) \
	CYC_INT(company_id) \
	CYC_INT(user_id) \
	CYC_STRING(avatar, 256) \
	CYC_STRING(avatar_big, 256) \
	CYC_INT(position) \
	CYC_STRING(specialization, 64) \

#define CYC_SERVICE \
	CYC_STRING(booking_title, 256) \
	CYC_INT(tax_variant) \
	CYC_INT(vat_id) \
	CYC_STRING(print_title, 256) \
	CYC_INT(service_type) \
	CYC_INT(api_service_id) \
	CYC_INT(repeat_visit_days_step) \
	CYC_INT(seance_search_start) \
	CYC_INT(seance_search_finish) \
	CYC_INT(seance_search_step) \
	CYC_INT(step) \
	CYC_BOOL(is_need_limit_date) \
	CYC_STRING(date_from, 16) \
	CYC_STRING(date_to, 16) \
	CYC_INT(schedule_template_type) \
	CYC_INT(online_invoicing_status) \
	CYC_INT(is_abonement_autopayment_enabled) \
	CYC_INT(autopayment_before_visit_time) \
	CYC_INT(abonement_restriction_value) \
	CYC_BOOL(is_chain) \
	CYC_BOOL(is_price_managed_only_in_chain) \
	CYC_BOOL(is_comment_managed_only_in_chain) \
	CYC_INT(price_prepaid_amount) \
	CYC_INT(price_prepaid_percent) \
	CYC_BOOL(is_composite) \
	CYC_INT(technical_break_duration) \
	CYC_INT(default_technical_break_duration) \
	CYC_INT(id) \
	CYC_INT(salon_service_id) \
	CYC_STRING(title, 256) \
	CYC_INT(category_id) \
	CYC_DOUBLE(price_min) \
	CYC_DOUBLE(price_max) \
	CYC_DOUBLE(discount) \
	CYC_STRING(comment, 256) \
	CYC_INT(weight) \
	CYC_INT(active) \
	CYC_STRING(api_id, 16) \
	CYC_STRING(prepaid, 16) \
	CYC_BOOL(is_multi) \
	CYC_INT(capacity) \
	CYC_UNKNOWN(image_group) \
	CYC_STAFF_CLASS(staff) \
	CYC_STRING_ARRAY(dates, 16, 32) \
	CYC_INT(duration) \
	CYC_UNKNOWN(resources) \
	CYC_BOOL(is_online) \

#define CYC_USER_ROLE \
   CYC_STRING(slug, 64) \
   CYC_STRING(title, 128) \
   CYC_STRING(description, 256) \
   CYC_INT(weight) \
   CYC_STRING(paid_status, 64) \

#define CYC_USER_PERMISSIONS \
   CYC_BOOL(timetable_access) \
   CYC_INT(timetable_position_id) \
   CYC_INT(timetable_staff_id) \
   CYC_INT(timetable_last_days_count) \
   CYC_BOOL(timetable_schedule_edit_access) \
   CYC_BOOL(timetable_phones_access) \
   CYC_BOOL(timetable_transferring_record_access) \
   CYC_BOOL(timetable_statistics_access) \
   CYC_BOOL(timetable_waiting_list_access) \
   CYC_BOOL(records_access) \
   CYC_BOOL(records_clients_access) \
   CYC_BOOL(records_clients_add_access) \
   CYC_BOOL(records_autocomplete_access) \
   CYC_BOOL(records_autocomplete_phones_access) \
   CYC_BOOL(records_custom_fields_values_access) \
   CYC_BOOL(records_create_access) \
   CYC_BOOL(records_edit_access) \
   CYC_INT(records_edit_last_days_count) \
   CYC_BOOL(records_edit_client_came_access) \
   CYC_BOOL(records_edit_full_paid_client_came_access) \
   CYC_BOOL(records_edit_full_paid_client_confirm_access) \
   CYC_BOOL(records_services_cost_access) \
   CYC_BOOL(records_services_discount_access) \
   CYC_BOOL(records_custom_fields_values_edit_access) \
   CYC_BOOL(records_edit_date_and_master_access) \
   CYC_BOOL(records_edit_duration_access) \
   CYC_BOOL(records_edit_comment_access) \
   CYC_BOOL(records_edit_services_access) \
   CYC_BOOL(records_delete_access) \
   CYC_BOOL(records_delete_client_came_access) \
   CYC_BOOL(records_delete_paid_access) \
   CYC_BOOL(records_goods_access) \
   CYC_BOOL(records_goods_transaction_create_access) \
   CYC_INT(records_goods_transaction_create_last_days_count) \
   CYC_BOOL(records_goods_transaction_edit_access) \
   CYC_INT(records_goods_transaction_edit_last_days_count) \
   CYC_BOOL(records_goods_cost_access) \
   CYC_BOOL(records_goods_discount_access) \
   CYC_BOOL(records_finances_access) \
   CYC_INT(records_finances_last_days_count) \
   CYC_INT(records_finances_accounts_limited_access) \
   CYC_INT_ARRAY(records_finances_limited_account_ids, 32) \
   CYC_BOOL(records_finances_pay_from_deposits_access) \
   CYC_BOOL(records_consumables_edit_access) \
   CYC_BOOL(records_clients_statistics_chain_access) \
   CYC_INT(records_clients_statistics_chain_id) \
   CYC_BOOL(finances_access) \
   CYC_INT(finances_accounts_limited_access) \
   CYC_INT_ARRAY(finances_accounts_ids, 32) \
   CYC_BOOL(finances_transactions_access) \
   CYC_INT(finances_transactions_last_days_count) \
   CYC_BOOL(finances_transactions_create_access) \
   CYC_INT(finances_transactions_create_last_days_count) \
   CYC_BOOL(finances_transactions_edit_access) \
   CYC_INT(finances_transactions_edit_last_days_count) \
   CYC_BOOL(finances_transactions_delete_access) \
   CYC_BOOL(finances_transactions_export_access) \
   CYC_INT(finances_expenses_limited_access) \
   CYC_INT_ARRAY(finances_expenses_ids, 32) \
   CYC_BOOL(finances_accounts_access) \
   CYC_BOOL(finances_accounts_balance_access) \
   CYC_BOOL(finances_suppliers_access) \
   CYC_BOOL(finances_suppliers_create_access) \
   CYC_BOOL(finances_suppliers_edit_access) \
   CYC_BOOL(finances_suppliers_delete_access) \
   CYC_BOOL(finances_suppliers_export_access) \
   CYC_BOOL(finances_expenses_access) \
   CYC_BOOL(finances_expenses_create_access) \
   CYC_BOOL(finances_expenses_edit_access) \
   CYC_BOOL(finances_expenses_delete_access) \
   CYC_BOOL(finances_kkm_transactions_access) \
   CYC_BOOL(finances_kkm_settings_access) \
   CYC_BOOL(finances_kkm_settings_edit_access) \
   CYC_BOOL(finances_settings_invoicing_access) \
   CYC_BOOL(finances_settings_invoicing_edit_access) \
   CYC_BOOL(finances_settings_access) \
   CYC_BOOL(finances_settings_edit_access) \
   CYC_BOOL(finances_salary_schemes_access) \
   CYC_BOOL(finances_salary_access) \
   CYC_INT(finances_salary_no_limit_today_access) \
   CYC_BOOL(finances_salary_payroll_access) \
   CYC_INT(finances_salary_payroll_no_limit_today_access) \
   CYC_BOOL(finances_salary_staff_access) \
   CYC_INT(finances_salary_staff_id) \
   CYC_INT(finances_salary_staff_no_limit_today_access) \
   CYC_BOOL(finances_salary_staff_payroll_access) \
   CYC_INT(finances_salary_staff_payroll_no_limit_today_access) \
   CYC_BOOL(finances_period_report_access) \
   CYC_BOOL(finances_period_report_export_access) \
   CYC_BOOL(finances_year_report_access) \
   CYC_BOOL(finances_year_report_export_access) \
   CYC_BOOL(finances_bill_print_access) \
   CYC_BOOL(finances_z_report_access) \
   CYC_INT(finances_z_report_no_limit_today_access) \
   CYC_BOOL(finances_z_report_export_access) \
   CYC_BOOL(storages_access) \
   CYC_INT(storages_limited_access) \
   CYC_INT_ARRAY(storages_ids, 32) \
   CYC_BOOL(storages_goods_prime_cost_view_access) \
   CYC_BOOL(storages_goods_transactions_access) \
   CYC_INT(storages_goods_transactions_last_days_count) \
   CYC_BOOL(storages_goods_move_access) \
   CYC_BOOL(storages_goods_transactions_create_access) \
   CYC_INT(storages_goods_transactions_create_last_days_count) \
   CYC_BOOL(storages_goods_transactions_create_buy_access) \
   CYC_BOOL(storages_goods_transactions_create_sale_access) \
   CYC_BOOL(storages_goods_transactions_edit_access) \
   CYC_INT(storages_goods_transactions_edit_last_days_count) \
   CYC_BOOL(storages_goods_transactions_edit_buy_access) \
   CYC_BOOL(storages_goods_transactions_edit_sale_access) \
   CYC_BOOL(storages_goods_transactions_delete_access) \
   CYC_BOOL(storages_goods_transactions_export_access) \
   CYC_INT(storages_goods_transactions_types_limited_access) \
   CYC_INT_ARRAY(storages_goods_transactions_types, 32) \
   CYC_BOOL(storages_inventory_access) \
   CYC_BOOL(storages_inventory_create_edit_access) \
   CYC_BOOL(storages_inventory_delete_access) \
   CYC_BOOL(storages_inventory_export_access) \
   CYC_BOOL(storages_remnants_report_access) \
   CYC_BOOL(storages_remnants_report_export_access) \
   CYC_BOOL(storages_sales_report_access) \
   CYC_BOOL(storages_sales_report_export_access) \
   CYC_BOOL(storages_consumable_report_access) \
   CYC_BOOL(storages_consumable_report_export_access) \
   CYC_BOOL(storages_write_off_report_access) \
   CYC_BOOL(storages_write_off_report_export_access) \
   CYC_BOOL(storages_turnover_report_access) \
   CYC_BOOL(storages_turnover_report_export_access) \
   CYC_BOOL(storages_goods_access) \
   CYC_BOOL(storages_goods_create_access) \
   CYC_BOOL(storages_goods_edit_access) \
   CYC_BOOL(storages_goods_edit_title_access) \
   CYC_BOOL(storages_goods_edit_category_access) \
   CYC_BOOL(storages_goods_edit_selling_price_access) \
   CYC_BOOL(storages_goods_edit_cost_price_access) \
   CYC_BOOL(storages_goods_edit_units_access) \
   CYC_BOOL(storages_goods_edit_critical_balance_access) \
   CYC_BOOL(storages_goods_edit_masses_access) \
   CYC_BOOL(storages_goods_edit_comment_access) \
   CYC_BOOL(storages_goods_archive_access) \
   CYC_BOOL(storages_goods_delete_access) \
   CYC_BOOL(settings_access) \
   CYC_BOOL(settings_basis_access) \
   CYC_BOOL(settings_information_access) \
   CYC_BOOL(settings_users_access) \
   CYC_BOOL(settings_users_delete_access) \
   CYC_BOOL(settings_users_create_access) \
   CYC_BOOL(settings_users_notifications_access) \
   CYC_BOOL(settings_users_edit_access) \
   CYC_INT(settings_users_limited_access) \
   CYC_BOOL(settings_services_access) \
   CYC_BOOL(settings_services_create_access) \
   CYC_BOOL(settings_services_edit_access) \
   CYC_BOOL(settings_services_edit_title_access) \
   CYC_BOOL(settings_services_edit_category_access) \
   CYC_BOOL(settings_services_edit_price_access) \
   CYC_BOOL(settings_services_edit_image_access) \
   CYC_BOOL(settings_services_edit_online_seance_date_time_access) \
   CYC_BOOL(settings_services_edit_online_pay_access) \
   CYC_BOOL(settings_services_edit_services_related_resource_access) \
   CYC_BOOL(settings_services_edit_staff_and_duration_access) \
   CYC_BOOL(settings_services_edit_technological_card_access) \
   CYC_BOOL(settings_services_delete_access) \
   CYC_BOOL(settings_staff_access) \
   CYC_BOOL(settings_staff_create_access) \
   CYC_BOOL(settings_staff_edit_access) \
   CYC_BOOL(settings_staff_delete_access) \
   CYC_BOOL(settings_staff_dismiss_access) \
   CYC_BOOL(settings_positions_access) \
   CYC_BOOL(settings_positions_create_access) \
   CYC_BOOL(settings_positions_delete_access) \
   CYC_BOOL(settings_schedule_edit_access) \
   CYC_BOOL(settings_notifications_sms_access) \
   CYC_BOOL(settings_notifications_email_access) \
   CYC_BOOL(settings_notifications_templates_access) \
   CYC_BOOL(settings_webhook_access) \
   CYC_BOOL(settings_billing_documents_access) \
   CYC_BOOL(settings_clients_labels_access) \
   CYC_BOOL(clients_access) \
   CYC_BOOL(clients_phones_email_access) \
   CYC_BOOL(clients_card_phone_access) \
   CYC_BOOL(clients_surname_patronymic_access) \
   CYC_BOOL(clients_surname_patronymic_edit_access) \
   CYC_BOOL(clients_edit_access) \
   CYC_BOOL(clients_loyalty_access) \
   CYC_BOOL(clients_card_comment_access) \
   CYC_BOOL(clients_card_comment_edit_access) \
   CYC_BOOL(clients_delete_access) \
   CYC_BOOL(clients_export_access) \
   CYC_BOOL(clients_comments_access) \
   CYC_BOOL(clients_comments_add_access) \
   CYC_BOOL(clients_comments_own_edit_access) \
   CYC_BOOL(clients_comments_other_edit_access) \
   CYC_BOOL(clients_files_access) \
   CYC_BOOL(clients_files_upload_access) \
   CYC_BOOL(clients_files_delete_access) \
   CYC_BOOL(clients_custom_fields_values_access) \
   CYC_BOOL(clients_custom_fields_values_edit_access) \
   CYC_INT(clients_visit_staff_id) \
   CYC_BOOL(clients_attendance_history_access) \
   CYC_BOOL(clients_deposits_access) \
   CYC_BOOL(clients_deposits_create_access) \
   CYC_BOOL(clients_deposits_topup_access) \
   CYC_BOOL(clients_deposits_history_access) \
   CYC_BOOL(clients_loyalty_settings_access) \
   CYC_BOOL(dashboard_access) \
   CYC_BOOL(dashboard_overview_access) \
   CYC_BOOL(dashboard_overview_phones_access) \
   CYC_BOOL(dashboard_records_access) \
   CYC_INT(dashboard_records_last_days_count) \
   CYC_BOOL(dashboard_records_export_access) \
   CYC_BOOL(dashboard_records_phones_access) \
   CYC_BOOL(dashboard_messages_access) \
   CYC_BOOL(dashboard_messages_export_access) \
   CYC_BOOL(dashboard_messages_phones_access) \
   CYC_BOOL(dashboard_reviews_access) \
   CYC_BOOL(dashboard_reviews_delete_access) \
   CYC_BOOL(dashboard_calls_access) \
   CYC_BOOL(dashboard_calls_export_access) \
   CYC_BOOL(dashboard_calls_phones_access) \
   CYC_BOOL(security_access) \
   CYC_BOOL(security_2fa_access) \
   CYC_BOOL(security_export_import_access) \
   CYC_BOOL(security_data_changes_access) \
   CYC_BOOL(security_employee_changes_access) \
   CYC_BOOL(security_logins_access) \
   CYC_BOOL(medicine_access) \
   CYC_BOOL(medicine_card_access) \
   CYC_BOOL(medicine_card_view_access) \
   CYC_BOOL(medicine_card_print_access) \
   CYC_BOOL(medicine_card_edit_access) \
   CYC_BOOL(medicine_appointment_access) \
   CYC_BOOL(medicine_appointment_view_access) \
   CYC_INT(medicine_appointment_view_settings_position_id) \
   CYC_INT(medicine_appointment_view_settings_staff_id) \
   CYC_BOOL(medicine_appointment_print_access) \
   CYC_BOOL(medicine_appointment_edit_access) \
   CYC_INT(medicine_appointment_edit_settings_position_id) \
   CYC_BOOL(medicine_appointment_edit_settings_staff_id) \
   CYC_BOOL(medicine_treatment_plan_access) \
   CYC_BOOL(medicine_treatment_plan_view_access) \
   CYC_BOOL(medicine_treatment_plan_print_access) \
   CYC_BOOL(medicine_treatment_plan_edit_access) \
   CYC_BOOL(loyalty_access) \
   CYC_BOOL(loyalty_cards_issue_and_removal_access) \
   CYC_BOOL(loyalty_cards_manual_transactions_access) \
   CYC_BOOL(loyalty_abonement_balance_edit_access) \
   CYC_BOOL(loyalty_abonement_period_edit_access) \
   CYC_BOOL(loyalty_abonement_history_access) \
   CYC_BOOL(loyalty_certificate_balance_edit_access) \
   CYC_BOOL(loyalty_certificate_period_edit_access) \
   CYC_BOOL(loyalty_certificate_and_abonement_manual_transactions_access) \
   CYC_BOOL(billing_access) \
   CYC_BOOL(billing_invoices_access) \
   CYC_BOOL(tips_access) \
   CYC_BOOL(tips_setup_access) \
   CYC_BOOL(online_record_access) \
   CYC_BOOL(online_record_privacy_policy_access) \
   CYC_BOOL(auth_enable_check_ip) \
   CYC_STRING(auth_list_allowed_ip, 32) \
   CYC_BOOL(statistics_access) \
   CYC_BOOL(analytics_constructor_access) \
   CYC_BOOL(send_sms_access) \
   CYC_BOOL(company_to_chain_add_access) \
   
#define CYC_FILE \
   CYC_INT(id) \
   CYC_INT(client_id) \
   CYC_STRING(name, 256) \
   CYC_STRING(description, 256) \
   CYC_STRING(extension, 32) \
   CYC_STRING(mime, 64) \
   CYC_STRING(link, 256) \
   CYC_STRING(full_link, 512) \
   CYC_STRING(date_create, 32) \
   CYC_STRING(size, 32) \
   CYC_STRING(user_name, 64) \
   CYC_STRING(user_avatar, 256) \
   CYC_BOOL(can_edit) \

#define CYC_VISIT_SERVICE \
	CYC_INT(id) \
	CYC_STRING(title, 32) \
	CYC_INT(first_cost) \
	CYC_INT(discount_percent) \
	CYC_INT(cost_to_pay) \
	CYC_INT(paid_sum) \
	CYC_STRING(payment_status, 32) \
	CYC_INT(paid_abonements_count) \
	CYC_INT(amount) \
	CYC_INT(payed_cost) \
	CYC_BOOL(is_paid_full) \
	CYC_BOOL(is_multi) \

#define CYC_DOCUMENT \
    CYC_INT(id) \
    CYC_INT(type_id) \
    CYC_INT(storage_id) \
    CYC_INT(user_id) \
    CYC_INT(company_id) \
    CYC_INT(number) \
    CYC_STRING(comment, 32) \
    CYC_STRING(date_created, 32) \
    CYC_INT(category_id) \
    CYC_INT(visit_id) \
    CYC_INT(record_id) \
    CYC_STRING(type_title, 32) \
    CYC_BOOL(is_sale_bill_printed) \

#define CYC_RECORD \
    CYC_INT(id) \
    CYC_INT(company_id) \
    CYC_INT(staff_id) \
    CYC_INT(clients_count) \
    CYC_STRING(date, 32) \
    CYC_STRING(datetime, 64) \
    CYC_STRING(create_date, 64) \
    CYC_STRING(comment, 256) \
    CYC_BOOL(online) \
    CYC_INT(visit_attendance) \
    CYC_INT(attendance) \
    CYC_INT(confirmed) \
    CYC_INT(seance_length) \
    CYC_INT(length) \
    CYC_INT(technical_break_duration) \
    CYC_INT(sms_now) \
    CYC_INT(sms_before) \
    CYC_STRING(sms_now_text, 256) \
    CYC_INT(email_now) \
    CYC_INT(notified) \
    CYC_INT(master_request) \
    CYC_STRING(api_id, 128) \
    CYC_STRING(from_url, 256) \
    CYC_INT(review_requested) \
    CYC_INT(visit_id) \
    CYC_INT(created_user_id) \
    CYC_BOOL(deleted) \
    CYC_INT(paid_full) \
    CYC_INT(payment_status) \
    CYC_BOOL(prepaid) \
    CYC_BOOL(prepaid_confirmed) \
    CYC_STRING(last_change_date, 64) \
    CYC_STRING(custom_color, 32) \
    CYC_STRING(custom_font_color, 32) \
    CYC_INT(activity_id) \
    CYC_VISIT_SERVICE_CLASS_ARRAY(services, 32) \
    CYC_STAFF_CLASS(staff) \
    CYC_COMPANY_CLASS(company) \
    CYC_DOCUMENT_CLASS_ARRAY(documents, 32) \
    CYC_KVPAIR(custom_fields, 32) \

#define CYC_CLIENT \
   CYC_INT(id) \
   CYC_STRING(name, 64) \
   CYC_STRING(surname, 64) \
   CYC_STRING(patronymic, 64) \
   CYC_STRING(display_name, 128) \
   CYC_STRING(phone, 16) \
   CYC_STRING(email, 64) \
   CYC_INT(sex_id) \
   CYC_STRING(sex, 16) \
   CYC_INT(discount) \
   CYC_STRING(importance, 32) \
   CYC_STRING(card, 32) \
   CYC_STRING(birth_date, 32) \
   CYC_STRING(comment, 256) \
   CYC_INT(visits) \
   CYC_INT(sms_check) \
   CYC_INT(sms_bot) \
   CYC_INT(sms_not) \
   CYC_INT(spent) \
   CYC_INT(paid) \
   CYC_INT(balance) \
   CYC_INT(importance_id) \
   CYC_STRING_ARRAY(categories, 32, 32) \
   CYC_STRING(last_change_date, 32) \
   CYC_KVPAIR(custom_fields, 32) \

#define CYC_COMMENT \
   CYC_INT(id) \
   CYC_STRING(create_date, 32) \
   CYC_STRING(upate_date, 32) \
   CYC_STRING(type, 32) \
   CYC_STRING(text, 512) \
   CYC_USER_CLASS(user) \
   CYC_FILE_CLASS(file) \

// structure 
#define CYC_UNKNOWN(_name)
#define CYC_INT(_name) int _name;
#define CYC_DOUBLE(_name) double _name;
#define CYC_BOOL(_name) bool _name;
#define CYC_STRING(_name, _size) char _name[_size];
#define CYC_INT_ARRAY(_name, _len) int _name[_len]; int n##_name;
#define CYC_DOUBLE_ARRAY(_name, _len) double _name[_len]; int n##_name;
#define CYC_STRING_ARRAY(_name, _size, _len) char _name[_len][_size]; int n##_name;

#define CYC_USER_CLASS(_name) CYCUser _name;
#define CYC_FILE_CLASS(_name) CYCFile _name;
#define CYC_TRANSPORT_CLASS(_name) CYCTransport _name;
#define CYC_2FA_CLASS(_name) CYC2fa _name;
#define CYC_SOCIAL_CLASS(_name) CYCSocial _name;
#define CYC_BOOKING_WIDGET_PROMO_CLASS(_name) \
	CYCBookingWidgetPromo _name;
#define CYC_MAIN_GROUP_CLASS(_name) CYCMainGroup _name;
#define CYC_SALON_GROUP_SETTINGS_CLASS(_name) \
	CYCSalonGroupSettings _name;
#define CYC_ACCESS_CLASS(_name) CYCAccess _name;
#define CYC_COMPANY_CLASS(_name) CYCCompany _name;
#define CYC_STAFF_CLASS(_name) CYCStaff _name;
#define CYC_SERVICE_CLASS(_name) CYCService _name;
#define CYC_VISIT_SERVICE_CLASS(_name) CYCVisitService _name;
#define CYC_VISIT_SERVICE_CLASS_ARRAY(_name, _len) CYCVisitService _name[_len]; int n##_name;
#define CYC_DOCUMENT_CLASS(_name) CYCDocument _name;
#define CYC_DOCUMENT_CLASS_ARRAY(_name, _len) CYCDocument _name[_len]; int n##_name;
#define CYC_KVPAIR(_name, _len) struct kvpair _name[_len]; int n##_name;

typedef struct {
	CYC_TYPE _type;
	CYC_USER
} CYCUser;
int     cyc_user_fr_json(CYCUser *t, const cJSON *json);
cJSON * cyc_user_to_json(CYCUser *t);

typedef struct {
	CYC_TYPE _type;
	CYC_TRANSPORT
} CYCTransport;
int     cyc_transport_fr_json(CYCTransport *t, const cJSON *json);
cJSON * cyc_transport_to_json(CYCTransport *t);

typedef struct {
	CYC_TYPE _type;
	CYC_2FA
} CYC2fa;
int     cyc_2fa_fr_json(CYC2fa *t, const cJSON *json);
cJSON * cyc_2fa_to_json(CYC2fa *t);

typedef struct {
	CYC_TYPE _type;
	CYC_SOCIAL
} CYCSocial;
int     cyc_social_fr_json(CYCSocial *t, const cJSON *json);
cJSON * cyc_social_to_json(CYCSocial *t);

typedef struct {
	CYC_TYPE _type;
	CYC_BOOKING_WIDGET_PROMO
} CYCBookingWidgetPromo;
int     cyc_booking_widget_promo_fr_json(
		CYCBookingWidgetPromo *t, const cJSON *json);
cJSON * cyc_booking_widget_promo_to_json(CYCBookingWidgetPromo *t);

typedef struct {
	CYC_TYPE _type;
	CYC_MAIN_GROUP
} CYCMainGroup;
int     cyc_main_group_fr_json(CYCMainGroup *t, const cJSON *json);
cJSON * cyc_main_group_to_json(CYCMainGroup *t);

typedef struct {
	CYC_TYPE _type;
	CYC_SALON_GROUP_SETTINGS
} CYCSalonGroupSettings;
int     cyc_salon_group_settings_fr_json(
		CYCSalonGroupSettings *t, const cJSON *json);
cJSON * cyc_salon_group_settings_to_json(CYCSalonGroupSettings *t);

typedef struct {
	CYC_TYPE _type;
	CYC_ACCESS
} CYCAccess;
int     cyc_access_fr_json(CYCAccess *t, const cJSON *json);
cJSON * cyc_access_to_json(CYCAccess *t);

typedef struct {
	CYC_TYPE _type;
	CYC_COMPANY
} CYCCompany;
int     cyc_company_fr_json(CYCCompany *t, const cJSON *json);
cJSON * cyc_company_to_json(CYCCompany *t);

typedef struct {
	CYC_TYPE _type;
	CYC_STAFF
} CYCStaff;
int     cyc_staff_fr_json(CYCStaff *t, const cJSON *json);
cJSON * cyc_staff_to_json(CYCStaff *t);

typedef struct {
	CYC_TYPE _type;
	CYC_SERVICE_CATEGORY
} CYCServiceCategory;
int     cyc_service_category_fr_json(CYCServiceCategory *t, const cJSON *json);
cJSON * cyc_service_category_to_json(CYCServiceCategory *t);

typedef struct {
	CYC_TYPE _type;
	CYC_SERVICE
} CYCService;
int     cyc_service_fr_json(CYCService *t, const cJSON *json);
cJSON * cyc_service_to_json(CYCService *t);

typedef struct {
	CYC_TYPE _type;
	CYC_USER_ROLE
} CYCUserRole;
int     cyc_user_role_fr_json(CYCUserRole *t, const cJSON *json);
cJSON * cyc_user_role_to_json(CYCUserRole *t);

typedef struct {
	CYC_TYPE _type;
	CYC_USER_PERMISSIONS
} CYCUserPermissions;
int     cyc_user_permissions_fr_json(CYCUserPermissions *t, const cJSON *json);
cJSON * cyc_user_permissions_to_json(CYCUserPermissions *t);

typedef struct {
	CYC_TYPE _type;
	CYC_FILE
} CYCFile;
int     cyc_file_fr_json(CYCFile *t, const cJSON *json);
cJSON * cyc_file_to_json(CYCFile *t);

typedef struct {
	CYC_TYPE _type;
	CYC_VISIT_SERVICE
} CYCVisitService;
int     cyc_visit_service_fr_json(CYCVisitService *t, const cJSON *json);
cJSON * cyc_visit_service_to_json(CYCVisitService *t);

typedef struct {
	CYC_TYPE _type;
	CYC_DOCUMENT
} CYCDocument;
int     cyc_document_fr_json(CYCDocument *t, const cJSON *json);
cJSON * cyc_document_to_json(CYCDocument *t);

typedef struct {
	CYC_TYPE _type;
	CYC_RECORD
} CYCRecord;
int     cyc_record_fr_json(CYCRecord *t, const cJSON *json);
cJSON * cyc_record_to_json(CYCRecord *t);

typedef struct {
	CYC_TYPE _type;
	CYC_CLIENT
} CYCClient;
int     cyc_client_fr_json(CYCClient *t, const cJSON *json);
cJSON * cyc_client_to_json(CYCClient *t);

typedef struct {
	CYC_TYPE _type;
	CYC_COMMENT
} CYCComment;
int     cyc_comment_fr_json(CYCComment *t, const cJSON *json);
cJSON * cyc_comment_to_json(CYCComment *t);

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
#undef CYC_STAFF_CLASS
#undef CYC_SERVICE_CLASS
#undef CYC_VISIT_SERVICE_CLASS
#undef CYC_VISIT_SERVICE_CLASS_ARRAY
#undef CYC_DOCUMENT_CLASS
#undef CYC_DOCUMENT_CLASS_ARRAY
#undef CYC_KVPAIR

// default_fields 
enum DEFAULT_FIELD_TYPE {
	DEFAULT_FIELD_TYPE_NULL = 0,
	DEFAULT_FIELD_TYPE_INT,
	DEFAULT_FIELD_TYPE_DOUBLE,
	DEFAULT_FIELD_TYPE_BOOL,
	DEFAULT_FIELD_TYPE_STRING,
	DEFAULT_FIELD_TYPE_JSON,
};
#define CYC_UNKNOWN(_name)
#define CYC_INT(_name) #_name, DEFAULT_FIELD_TYPE_INT,
#define CYC_DOUBLE(_name) #_name, DEFAULT_FIELD_TYPE_DOUBLE,
#define CYC_BOOL(_name) #_name, DEFAULT_FIELD_TYPE_BOOL,
#define CYC_STRING(_name, _size) #_name, DEFAULT_FIELD_TYPE_STRING,
#define CYC_INT_ARRAY(_name, _len) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_DOUBLE_ARRAY(_name, _len) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_STRING_ARRAY(_name, _size, _len) #_name, DEFAULT_FIELD_TYPE_JSON,

#define CYC_USER_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_FILE_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_TRANSPORT_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_2FA_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_SOCIAL_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_BOOKING_WIDGET_PROMO_CLASS(_name) \
	#_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_MAIN_GROUP_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_SALON_GROUP_SETTINGS_CLASS(_name) \
	#_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_ACCESS_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_COMPANY_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_STAFF_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_SERVICE_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_VISIT_SERVICE_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_VISIT_SERVICE_CLASS_ARRAY(_name, _len) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_DOCUMENT_CLASS(_name) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_DOCUMENT_CLASS_ARRAY(_name, _len) #_name, DEFAULT_FIELD_TYPE_JSON,
#define CYC_KVPAIR(_name, _len)

struct default_field {
	char *name;
	enum DEFAULT_FIELD_TYPE type;
};

static const struct default_field service_fields[] = 
{
	CYC_SERVICE
	NULL, DEFAULT_FIELD_TYPE_NULL
};

static const struct default_field client_fields[] = 
{
	CYC_CLIENT
	NULL, DEFAULT_FIELD_TYPE_NULL
};

static const struct default_field record_fields[] = 
{
	CYC_RECORD
	"client_agreements", DEFAULT_FIELD_TYPE_JSON,
	"client", DEFAULT_FIELD_TYPE_JSON,
	NULL, DEFAULT_FIELD_TYPE_NULL
};

static cJSON * json_from_default_field(
		struct default_field *field, const char *value)
{
	cJSON *json = NULL;
	switch (field->type) {
		case DEFAULT_FIELD_TYPE_INT:
			{
				int v = atoi(value);
				json = cJSON_CreateNumber(v);
			}
			break;
		case DEFAULT_FIELD_TYPE_DOUBLE:
			{
				int v = atof(value);
				json = cJSON_CreateNumber(v);
			}
			break;
		case DEFAULT_FIELD_TYPE_BOOL:
			{
				int v = atoi(value);
				json = cJSON_CreateBool(v);
			}
			break;
		case DEFAULT_FIELD_TYPE_STRING:
			{
				json = cJSON_CreateString(value);
			}
			break;
		case DEFAULT_FIELD_TYPE_JSON:
			{
				json = cJSON_Parse(value);
			}
			break;
		
		default:
			break;
	}

	return json;
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
#undef CYC_STAFF_CLASS
#undef CYC_SERVICE_CLASS
#undef CYC_VISIT_SERVICE_CLASS
#undef CYC_VISIT_SERVICE_CLASS_ARRAY
#undef CYC_DOCUMENT_CLASS
#undef CYC_DOCUMENT_CLASS_ARRAY
#undef CYC_KVPAIR


#endif // STRUCTS_H
