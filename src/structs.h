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
	CYC_TYPE_STAFF,
	CYC_TYPE_SERVICE,
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

#define CYC_STAFF \
	CYC_INT(id) \
	CYC_INT(seance_length) \
	CYC_INT(technological_card_id) \
	CYC_STRING(image_url, 256) \
	CYC_INT(price) \
	CYC_STRING(name, 64) \

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
	CYC_INT(price_min) \
	CYC_INT(price_max) \
	CYC_INT(discount) \
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

// structure 
#define CYC_UNKNOWN(_name)
#define CYC_INT(_name) int _name;
#define CYC_DOUBLE(_name) double _name;
#define CYC_BOOL(_name) bool _name;
#define CYC_STRING(_name, _size) char _name[_size];
#define CYC_INT_ARRAY(_name, _len) int _name[_len];
#define CYC_DOUBLE_ARRAY(_name, _len) double _name[_len];
#define CYC_STRING_ARRAY(_name, _size, _len) char _name[_len][_size];

#define CYC_USER_CLASS(_name) CYCUser _name;
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
	CYC_SERVICE
} CYCService;
int     cyc_service_fr_json(CYCService *t, const cJSON *json);
cJSON * cyc_service_to_json(CYCService *t);

#undef CYC_UNKNOWN
#undef CYC_INT
#undef CYC_DOUBLE
#undef CYC_BOOL
#undef CYC_STRING
#undef CYC_INT_ARRAY
#undef CYC_DOUBLE_ARRAY
#undef CYC_STRING_ARRAY

#undef CYC_USER_CLASS
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

#endif // STRUCTS_H
