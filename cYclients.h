#ifndef CYCLIENTS_H
#define CYCLIENTS_H

#include "src/structs.h"

typedef int CYCLIENTS_COUNTER;

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
// Categogies
//////////////////////////////////////////////////////////

/* return number of all service categories for company_id 
 * and make callback for each while callback return is null */
CYCLIENTS_COUNTER
cyclients_service_categories(const char *token,
                             int company_id,
                             void *userdata,
                             int (*callback)(void *userdata, 
                                             const CYCServiceCategory *category));

/* return allocated service category with category_id or NULL on error */
CYCServiceCategory *
cyclients_service_category_get(const char *token,
							   int company_id,
							   int category_id);

/* return allocated new service category or NULL on error */
CYCServiceCategory *
cyclients_service_category_new(const char *token,
							   int company_id,
							   const char *title,
							   const char *api_id,
							   int weight,
							   int nstaff,
							   int staff[]);

/* update service category and return non-null on error */
int
cyclients_service_category_update(const char *token,
                                  int company_id,
                                  int category_id,
                                  const char *title,
                                  const char *api_id,
                                  int weight,
                                  int nstaff,
                                  int staff[]);

/* remove service category and return non-null on error */
int
cyclients_service_category_delete(const char *token,
                                  int company_id,
                                  int category_id);


//////////////////////////////////////////////////////////
// Services
//////////////////////////////////////////////////////////

typedef enum {
  CYCLIENTS_SERVICE_TYPE_OFFLINE,
  CYCLIENTS_SERVICE_TYPE_ONLINE,
} CYCLIENTS_SERVICE_TYPE;

/* return number of all services for company_id or with
 * service_id (if not NULL) and make callback for each 
 * while callback return is null */
CYCLIENTS_COUNTER
cyclients_services(const char *token,
                   int company_id,
                   void *userdata,
                   int (*callback)(void *userdata, 
                                   const CYCService *service));

/* return allocated service with service_id or NULL on error */
CYCService *
cyclients_service_get(const char *token,
                      int company_id,
                      int service_id);

struct staff {int id; int seance_length;};

/* return allocated new created service or NULL on error */
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
                      struct staff staff[]);


/* update service and return non-null on error */
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
                         struct staff staff[]);

/* remove service and return non-null on error */
int
cyclients_service_delete(const char *token,
                         int company_id,
                         int service_id);

struct master_cofig {
	int master_id;
	int technological_card_id;
	int hours;
	int minutes;
	struct price {
		double min;
		double max;
	} price;
};
struct translation {
	int language_id;
	char translation[256];
};

/* update service resources, staff, language translations and 
 * return non-null on error */
int
cyclients_service_set_links(const char *token,
                            int company_id,
                            int service_id,
						    int nmaster_configs,
                            struct master_cofig master_cofigs[],
                            int nresources,
                            int resources[],
                            int ntranslations,
                            struct translation translations[]);

/* set service staff and return non-null on error */
int
cyclients_service_set_staff(const char *token,
                            int company_id,
                            int service_id,
						    int master_id,
                            int seance_length,
                            int technological_card_id);

/* update service staff and return non-null on error */
int
cyclients_service_update_staff(const char *token,
                               int company_id,
                               int service_id,
						       int master_id,
                               int seance_length,
                               int technological_card_id);

/* remove service staff and return non-null on error */
int
cyclients_service_delete_staff(const char *token,
                               int company_id,
                               int service_id,
						       int master_id);

#endif // CYCLIENTS_H
