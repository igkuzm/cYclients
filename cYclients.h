#ifndef CYCLIENTS_H
#define CYCLIENTS_H

#include "src/structs.h"

typedef	int CYCLIENTS_COUNTER;

//////////////////////////////////////////////////////////
// Authorization
//////////////////////////////////////////////////////////

typedef enum{
  CYCLIENTS_AUTH_ERROR,
  CYCLIENTS_AUTH_AUTHORIZED,
  CYCLIENTS_AUTH_2FA, // 2-factor authorization is needed
} CYCLIENTS_AUTH;

/* authorize to yClients */
CYCLIENTS_AUTH
cyclients_login(const char *login, 
                const char *password,
                const CYCUser **user,
                const CYC2fa  **user2fa);

CYCLIENTS_AUTH
cyclients_login_2fa(const char *login, 
                    const char *password,
                    const char *uuid,
                    const char *secret,
                    const CYCUser **user);


//////////////////////////////////////////////////////////
// Companies
//////////////////////////////////////////////////////////

/* return number of companies you authorized or with
 * company_id (if not NULL) and make callback for each 
 * while callback return is null */
CYCLIENTS_COUNTER
cyclients_companies(const char *token,
                    char *company_id,
                    void *userdata,
                    int (*callback)(void *userdata, 
                                    const CYCCompany *company));

//////////////////////////////////////////////////////////
// Services
//////////////////////////////////////////////////////////

/* return number of all services for company_id or with
 * service_id (if not NULL) and make callback for each 
 * while callback return is null */
CYCLIENTS_COUNTER
cyclients_services(const char *token,
                   int company_id,
                   char *service_id,
                   void *userdata,
                   int (*callback)(void *userdata, 
                                   const CYCService *service));

/* return new created service or NULL on error */
const CYCService *
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
                      int service_type,
                      const char *api_service_id,
											int staff_count,
											int staff_ids[],
											int staff_seance_length[]);


/* return updated service or NULL on error */
const CYCService *
cyclients_service_update(const char *token,
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
                         const char *datetes[],
                         int seance_search_start,
                         int seance_search_finish,
                         int seance_search_step,
                         int weight,
                         int service_type,
                         const char *api_service_id,
                         int online_invoicing_status,
                         int price_prepaid_percent,
                         int price_prepaid_amount,
                         int abonement_restriction_value,
                         int is_abonement_autopayment_enabled,
                         int autopayment_before_visit_time,
											   int staff_count,
											   int staff_ids[],
											   int staff_seance_length[]);


#endif // CYCLIENTS_H
