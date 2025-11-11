#include "config.h"
#include "../cYclients.h"
#include "log.h"
#include "alloc.h"
#include "structs.h"
#include "cJSON.h"
#include "../partner_token.h"
#include "curl_transport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static CYCService SERVICE;

CYCLIENTS_COUNTER
cyclients_services(const char *token,
		               int company_id,
									 void *userdata,
									 int (*callback)(void *userdata, 
										               const CYCService *service))
{
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/services", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(
			requestString,
		 	auth, "GET",
		 	NULL, &json);

	if (http_code == 200){ // good
		if (cJSON_IsObject(json))
		{
			cJSON *data = cJSON_GetObjectItem(json, "data");
			if (cJSON_IsArray(data))
			{
				int i = 0;
				cJSON *service;
				cJSON_ArrayForEach(service, data)
				{
					memset(&SERVICE, 0, sizeof(SERVICE));
					cyc_service_fr_json(
							&SERVICE, service);
					if (callback)
						if (callback(userdata, &SERVICE))
							break;

					i++;
				}
				
				return i;
			}
		}
	}
	
	return 0;
}

CYCService *
cyclients_service_get(const char *token,
                      int company_id,
                      int service_id)
{
	cJSON *json = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/services/%d", 
			URL, company_id, service_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);
	
	http_code = curl_transport_exec(
			requestString,
		 	auth, "GET",
		 	NULL, &json);

	if (http_code == 200){ // good
		if (cJSON_IsObject(json))
		{
			cJSON *data = cJSON_GetObjectItem(json, "data");
			if (cJSON_IsObject(data))
			{
				CYCService *service = NEW(CYCService);
				if (service){
					cyc_service_fr_json(
							service, data);
					return service;
				}
			}
		}
	}
	
	return NULL;
}

CYCService *
cyclients_service_new(const char *token,
                      int company_id,
                      const char *title,
                      int category_id,
                      double price_min,
                      double price_max,
                      int duration,
                      int technical_break_duration,
                      double discount,
                      const char *comment,
                      int weight,
                      CYCLIENTS_SERVICE_TYPE service_type,
                      const char *api_service_id,
											int nstaff,
											struct staff staff[])
{
	int i;
	cJSON *json = NULL, *astaff = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/services/%d", 
			URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);

	json = cJSON_CreateObject();
	astaff = cJSON_CreateArray();	

	if (title)
		cJSON_AddStringToObject(json, "title", title);
	cJSON_AddNumberToObject(json, "category_id", category_id);
	cJSON_AddNumberToObject(json, "price_min", price_min);
	cJSON_AddNumberToObject(json, "price_max", price_max);
	cJSON_AddNumberToObject(json, "duration", duration);
	if (technical_break_duration)
		cJSON_AddNumberToObject(json, "technical_break_duration", technical_break_duration);
	cJSON_AddNumberToObject(json, "discount", discount);
	if (comment)
		cJSON_AddStringToObject(json, "comment", comment);
	cJSON_AddNumberToObject(json, "weight", weight);
	cJSON_AddNumberToObject(json, "service_type", service_type);
	if (api_service_id)
		cJSON_AddStringToObject(json, "api_service_id", api_service_id);

	for (i = 0; i < nstaff; ++i) {
		cJSON *staff_obj = cJSON_CreateObject();
		cJSON_AddNumberToObject(
				staff_obj, "id", staff[i].id);
		cJSON_AddNumberToObject(
				staff_obj, "seance_length", staff[i].seance_length);
		cJSON_AddItemToArray(astaff, staff_obj);			
	}
	cJSON_AddItemToObject(json, "staff", astaff);

	post_data = cJSON_Print(json);
	if (post_data == NULL){
		ERR("%s: can't generate post data", __func__);
		return NULL;
	}
	cJSON_free(json);

	http_code = curl_transport_exec(
			requestString,
		 	auth, "POST",
		 	cJSON_Print(json), &json);
	free(post_data);

	if (http_code == 201){ // created
		if (cJSON_IsObject(json))
		{
			cJSON *data = cJSON_GetObjectItem(json, "data");
			if (cJSON_IsObject(data))
			{
				CYCService *service = NEW(CYCService);
				if (service){
					cyc_service_fr_json(
							service, data);
					return service;
				}
			}
		}
	}

	return NULL;
}

int
cyclients_service_update(const char *token,
                         int company_id,
                         int service_id,
                         const char *title,
                         const char *booking_title,
                         int category_id,
                         double price_min,
                         double price_max,
                         int duration,
                         int technical_break_duration,
                         double discount,
                         bool is_multi,
                         int tax_variant,
                         int vat_id,
                         bool is_need_limit_date,
                         const char *date_from,
                         const char *date_to,
                         const char *dates[],
                         int seance_search_start,
                         int seance_search_finish,
                         int seance_search_step,
                         int weight,
                         CYCLIENTS_SERVICE_TYPE service_type,
                         const char *api_service_id,
                         int online_invoicing_status,
                         int price_prepaid_percent,
                         int price_prepaid_amount,
                         int abonement_restriction_value,
                         int is_abonement_autopayment_enabled,
                         int autopayment_before_visit_time,
                         int nstaff,
                         struct staff staff[])
{
	int i;
	cJSON *json = NULL, *astaff = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/services/%d"
			,URL, company_id, service_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);

	json = cJSON_CreateObject();
	astaff = cJSON_CreateArray();	

	if (title)
		cJSON_AddStringToObject(json, "title", title);
	if (booking_title)
		cJSON_AddStringToObject(json, "booking_title", booking_title);
	cJSON_AddNumberToObject(json, "category_id", category_id);
	cJSON_AddNumberToObject(json, "price_min", price_min);
	cJSON_AddNumberToObject(json, "price_max", price_max);
	cJSON_AddNumberToObject(json, "duration", duration);
	if (technical_break_duration)
		cJSON_AddNumberToObject(json, "technical_break_duration", technical_break_duration);
	cJSON_AddNumberToObject(json, "discount", discount);
	cJSON_AddBoolToObject(json, "is_multi", is_multi);
	cJSON_AddNumberToObject(json, "tax_variant", tax_variant);
	cJSON_AddNumberToObject(json, "vat_id", vat_id);
	cJSON_AddBoolToObject(json, "is_need_limit_date", is_need_limit_date);
	if (date_from)
		cJSON_AddStringToObject(json, "date_from", date_from);
	if (date_to)
		cJSON_AddStringToObject(json, "date_to", date_to);
	if (dates){
		char **datesp = (char **)dates;
		cJSON *datesa = cJSON_CreateArray();
		while (*datesp && datesa){
			cJSON *item = cJSON_CreateString(*datesp++);
			cJSON_AddItemToArray(datesa, item);
		}
		cJSON_AddItemToObject(json, "dates", datesa);
	}
	cJSON_AddNumberToObject(json, "seance_search_start", seance_search_start);
	cJSON_AddNumberToObject(json, "seance_search_finish", seance_search_finish);
	cJSON_AddNumberToObject(json, "seance_search_step", seance_search_step);
	cJSON_AddNumberToObject(json, "weight", weight);
	cJSON_AddNumberToObject(json, "service_type", service_type);
	if (api_service_id)
		cJSON_AddStringToObject(json, "api_service_id", api_service_id);
	cJSON_AddNumberToObject(json, "online_invoicing_status", online_invoicing_status);
	cJSON_AddNumberToObject(json, "price_prepaid_percent", price_prepaid_percent);
	cJSON_AddNumberToObject(json, "price_prepaid_amount", price_prepaid_amount);
	cJSON_AddNumberToObject(json, "abonement_restriction_value", abonement_restriction_value);
	cJSON_AddNumberToObject(json, "is_abonement_autopayment_enabled", is_abonement_autopayment_enabled);
	cJSON_AddNumberToObject(json, "autopayment_before_visit_time", autopayment_before_visit_time);

	for (i = 0; i < nstaff; ++i) {
		cJSON *staff_obj = cJSON_CreateObject();
		cJSON_AddNumberToObject(
				staff_obj, "id", staff[i].id);
		cJSON_AddNumberToObject(
				staff_obj, "seance_length", staff[i].seance_length);
		cJSON_AddItemToArray(astaff, staff_obj);			
	}
	cJSON_AddItemToObject(json, "staff", astaff);

	post_data = cJSON_Print(json);
	if (post_data == NULL){
		ERR("%s: can't generate post data", __func__);
		return 1;
	}
	cJSON_free(json);

	http_code = curl_transport_exec(
			requestString,
		 	auth, "PATCH",
		 	post_data, NULL);
	free(post_data);

	if (http_code == 200){ // updated
		return 0; 
	}

	return 1;
}

int
cyclients_service_delete(const char *token,
                         int company_id,
                         int service_id)
{
	long http_code = 0;
	char requestString[BUFSIZ], auth[128];
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/services/%d/%d", 
			URL, company_id, service_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);

	http_code = curl_transport_exec(
			requestString,
		 	auth, "DELETE",
		 	NULL, NULL);

	if (http_code == 204){ // deleted
		return 0; 
	}

	return 1;
}

int
cyclients_service_links(const char *token,
                        int company_id,
                        int service_id,
												int nmaster_configs,
												struct master_cofig master_cofigs[],
                        int nresources,
                        int resources[],
												int ntranslations,
												struct translation translations[])
{
	int i;
	cJSON *json = NULL, *array = NULL, 
        *master_settings = NULL, 
				*resource_ids = NULL,
				*array_translations = NULL;
	long http_code = 0;
	char requestString[BUFSIZ], auth[128], *post_data = NULL;
	char * SETUP_PARTNER_TOKEN(partner_token);

	sprintf(requestString, "%s/company/%d/services/links"
			,URL, company_id);
	sprintf(auth, "Authorization: Bearer %s, User %s"
			, partner_token, token);

	json = cJSON_CreateObject();
	master_settings = cJSON_CreateArray();
	cJSON_AddNumberToObject(json, "service_id", service_id);
	for (i = 0; i < nmaster_configs; ++i) {
		cJSON *setting = cJSON_CreateObject();		
		cJSON_AddNumberToObject(setting, "master_id", master_cofigs[i].master_id);
		cJSON_AddNumberToObject(setting, "technological_card_id", master_cofigs[i].technological_card_id);
		cJSON_AddNumberToObject(setting, "hours", master_cofigs[i].hours);
		cJSON_AddNumberToObject(setting, "minutes", master_cofigs[i].minutes);
		cJSON *price = cJSON_CreateObject();		
		cJSON_AddNumberToObject(price, "min", master_cofigs[i].price.min);
		cJSON_AddNumberToObject(price, "max", master_cofigs[i].price.max);
		cJSON_AddItemToObject(setting, "price", price);
		cJSON_AddItemToArray(master_settings, setting);
	}
	cJSON_AddItemToObject(json, "master_settings", master_settings);

	resource_ids = cJSON_CreateIntArray(resources, nresources);
	cJSON_AddItemToObject(json, "resource_ids", resource_ids);

	array_translations = cJSON_CreateArray();
	for (i = 0; i < ntranslations; ++i){
		cJSON *translation = cJSON_CreateObject();
		cJSON_AddNumberToObject(translation, "language_id", translations[i].language_id);
		cJSON_AddStringToObject(translation, "translation", translations[i].translation);
		cJSON_AddItemToArray(array_translations, translation);
	} 
	cJSON_AddItemToObject(json, "translations", array_translations);

	array = cJSON_CreateArray();
	cJSON_AddItemToArray(array, json);

	http_code = curl_transport_exec(
			requestString,
		 	auth, "DELETE",
		 	NULL, NULL);

	if (http_code == 200){
		return 0; 
	}

	return 1;
}
