#ifndef CYCLIENTS_H
#define CYCLIENTS_H

#include "src/structs.h"

typedef int CYCLIENTS_COUNTER;
typedef int CYCLIENTS_ID;
typedef struct {char *key; char *value;} kvpair_t;


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

int
cyclients_service_category_get(const char *token,
							                 int company_id,
							                 int category_id,
                               void *userdata,
                               int (*callback)(void *userdata, 
                                               const CYCServiceCategory *category));

CYCLIENTS_ID
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

int
cyclients_service_get(const char *token,
                      int company_id,
                      int service_id,
                      void *userdata,
                      int (*callback)(void *userdata, 
                                      const CYCService *service));

struct staff {int id; int seance_length;};

CYCLIENTS_ID
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

//////////////////////////////////////////////////////////
// Users
//////////////////////////////////////////////////////////

CYCLIENTS_ID
cyclients_user_new(const char *token,
				           int company_id,
                   const char *name,
                   const char *phone_number);

CYCLIENTS_COUNTER
cyclients_users_roles(const char *token,
                      int company_id,
                      void *userdata,
                      int (*callback)(void *userdata, 
                                      const CYCUserRole *user_role));

CYCLIENTS_COUNTER
cyclients_user_roles(const char *token,
                     int company_id,
                     int user_id,
                     void *userdata,
                     int (*callback)(void *userdata, 
                                     const CYCUserRole *user_role));

int
cyclients_user_permissions(const char *token,
                           int company_id,
                           int user_id,
													 void *userdata,
                           int (*callback)(void *userdata, 
                                           const CYCUserPermissions *permissions));

struct user_company_link {
	int company_id;
	char *user_permissions_json;
};

/* return allocated json c-string with slug and value pairs */
char * 
user_permissions_json_with_slug_and_value_pairs(int nslug_and_value_pairs, ...);

int
cyclients_user_copy_to_companies(const char *token,
                                 int company_id,
								                 int user_id,
								                 int nuser_user_company_links,
                                 struct user_company_link *links);

//////////////////////////////////////////////////////////
// Clients
//////////////////////////////////////////////////////////

CYCLIENTS_COUNTER
cyclients_clients_search(const char *token,
                         int company_id,
                         const char *comma_separeted_fields_to_return,
                         const char *search_query,
                         void *userdata,
                         int (*callback)(void *userdata, 
                                         int nfields,
                                         const kvpair_t *fields));
	
int
cyclients_client_get(const char *token,
                     int company_id,
                     int client_id,
										 void *userdata,
										 int (*callback)(void *userdata,
											               const CYCClient *client));

CYCLIENTS_ID
cyclients_client_new(const char *token,
                     int company_id,
                     const char *name,
                     const char *surname,
                     const char *patronymic,
                     const char *phone,
                     const char *email,
                     const char *birth_date,
                     const char *comment,
                     int number_custom_fields_key_value_pairs,
                     ...);

int
cyclients_client_edit(const char *token,
                      int company_id,
					            int client_id,
                      const char *name,
                      const char *surname,
                      const char *patronymic,
                      const char *phone,
                      const char *email,
					            int sex_id,
					            int importance_id,
					            int discount,
					            int card,
                      const char *birth_date,
                      const char *comment,
					            int spent,
					            int balance,
					            int sms_check,
					            int sms_not,
                      int number_custom_fields_key_value_pairs,
                      ...);

int
cyclients_client_remove(const char *token,
                        int company_id,
                        int client_id);

CYCLIENTS_COUNTER
cyclients_client_files(const char *token,
                       int company_id,
                       int client_id,
                       void *userdata,
                       int (*callback)(void *userdata, 
                                       const CYCFile *file));

int
cyclients_client_file_remove(const char *token,
                             int company_id,
                             int client_id,
                             int file_id);

CYCLIENTS_COUNTER
cyclients_client_visits(const char *token,
                       int company_id,
                       int client_id,
                       void *userdata,
                       int (*callback)(void *userdata, 
                                       const CYCRecord *visit));

CYCLIENTS_COUNTER
cyclients_client_comments(const char *token,
                          int company_id,
                          int client_id,
                          void *userdata,
                          int (*callback)(void *userdata, 
                                          const CYCComment *comment));

CYCLIENTS_ID
cyclients_client_comment_new(const char *token,
                             int company_id,
                             int client_id,
                             const char *comment);

int
cyclients_client_comment_remove(const char *token,
                                int company_id,
                                int client_id,
                                int comment_id);

//////////////////////////////////////////////////////////
// Records and Visits
//////////////////////////////////////////////////////////

CYCLIENTS_COUNTER
cyclients_records(const char *token,
                  int company_id,
                  const char *start_date,
                  const char *end_date,
                  void *userdata,
                  int (*callback)(void *userdata, 
                                  const CYCRecord *record));

CYCLIENTS_ID
cyclients_record_new(const char *token,
                     int company_id,
					           int staff_id,
                     const char *client_name,
                     const char *client_phone,
                     const char *datetime,
					           int seance_length,
                     const char *comment,
                     int number_custom_fields_key_value_pairs,
                     ...);

int
cyclients_record_get(const char *token,
                     int company_id,
                     int record_id,
										 void *userdata,
                     int (*callback)(void *userdata, 
                                     const CYCRecord *record));

struct service {
	int id;
  double price;
  double discount;
};


/*
staff_id		  number  Идентификатор сотрудника 
services[img] Array of objects  Параметры услуг 
                                (id, стоимость, скидка)                  
client[img]   object  Параметры клиента 
                                (телефон, имя, email)                  
save_if_busy  boolean Сохранять ли запись если время 
                      занято или нерабочее, или выдать
										 	ошибку                                            
datetime      string <date-time> Дата и время записи
seance_length number             Длительность записи в секундах
send_sms      boolean            Отправлять ли смс с деталями 
                                 записи клиенту              
comment       string             Комментарий к записи
sms_remain_hours number          За сколько часов до визита 
                                 следует выслать смс
																 напоминание клиенту (0 - если не нужно)
email_remain_hours number        За сколько часов до визита 
                                 следует выслать email напоминание
																 клиенту (0 - если не нужно)
attendance         number        Статус записи (
                                 2 - Пользователь подтвердил запись, 
																 1 - Пользователь пришел, услуги оказаны,
																 0 - ожидание пользователя, 
																 -1 - пользователь не пришел на визит)

api_id             string        Идентификатор внешней системы
custom_color       string        Цвет записи
record_labels      Array of strings Массив идентификаторов 
                                    категорий записи
client_agreements [img] object or null Юридические соглашения клиента
technical_break_durationumber or null  [ 0 .. 3600 ]
                         Технический перерыв.

                         • Строго кратно 300 (5 минутам).
                         • Максимальное значение 3600 (1 час)
                         • Если передан null  или значение не передано — будет
                           задан согласно настройкам в разделе Настройки →
                           Журнал записи → Технические перерывы при наличии
                           услуг с перерывом
*/
int
cyclients_record_update(const char *token,
                        int company_id,
					              int record_id,
                        int number_of_key_value_pairs,
                        ...);



#endif // CYCLIENTS_H
