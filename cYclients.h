#ifndef CYCLIENTS_H
#define CYCLIENTS_H

#ifdef __cplusplus
extern "C" {
#endif

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
cyclients_service_category_set(const char *token,
                               int company_id,
                               int category_id,
                               const char *title,
                               const char *api_id,
                               int weight,
                               int nstaff,
                               int staff[]);

/* remove service category and return non-null on error */
int
cyclients_service_category_remove(const char *token,
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

/* Метод, позволяющий создать услугу 
 * данные передают
 * string "title" Название услуги
 * number "category_id" ID категории услуг
 * number <float> "price_min" Минимальная стоимость услуги
 * number <float> "price_max" Максимальная стоимость услуги
 * number "duration" Длительность услуги, по умолчанию равна 3600 секундам
 * number or null [ 0 .. 3600 ] "technical_break_duration" 
 * Если нпередан. Значение по умолчанию null  Длительность 
 * технического перерыва
 * number <float> "discount" Скидка при оказании услуги
 * string "comment" Комментарий к услуге
 * number "weight" Вес услуги (используется для сортировки 
 * услуг при отображении)
 * number "service_type" Доступна ли для онлайн записи услуга. 
 * 1 - доступна, 0 не доступна.
 * string "api_service_id" Внешний идентификатор услуги
 * Array of objects "staff" Сотрудники, оказываюшие услугу 
 * и длительность оказания услуги каждым из них {"id", "seance_length"} */
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
                      const char *staff_json);

/* update service and return non-null on error */
int
cyclients_service_set(const char *token,
                      int company_id,
                      int service_id,
                      int number_of_key_value_pairs,
                      ...);
/* Метод, позволяющий изменить услугу */ 
int
cyclients_service_remove(const char *token,
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

/* create new client- key/value pairs are strings.
 * If you set keys 
 * "surname", "patronymic",
 * "email", "sex_id", "importance_id", 
 * "discount", "card", "birth_date", "comment",     
 * "spent", "balance", "sms_check", "sms_not" - the 
 * values are simple strings
 * Other key/values pairs are treated as custon_fields */
CYCLIENTS_ID
cyclients_client_new(const char *token,
                     int company_id,
                     const char *name,
                     const char *phone,
                     int number_of_key_value_pairs,
                     ...);

/* set client vars - key/value pairs are strings.
 * If you set keys 
 * "name", "surname", "patronymic", "phone",
 * "email", "sex_id", "importance_id", 
 * "discount", "card", "birth_date", "comment",     
 * "spent", "balance", "sms_check", "sms_not" - the 
 * values are simple strings
 * Other key/values pairs are treated as custon_fields */
int
cyclients_client_set(const char *token,
                     int company_id,
                     int client_id,
                     int number_of_key_value_pairs,
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
                     int number_of_key_value_pairs,
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


/* set record vars - key/value pairs are strings.
 * If you set keys 
 * "staff_id", "save_if_busy", "datetime", "seance_length",
 * "send_sms", "comment", "sms_remain_hours", 
 * "email_remain_hour", "attendance", "api_id", "custom_color",     
 * "record_labels", "technical_break_durationumber" - the 
 * values are simple strings
 * "client_agreements", "services", "client" - values are 
 * JSON strings
 * Other key/values pairs are treated as custon_fields */
int
cyclients_record_set(const char *token,
                     int company_id,
                     int record_id,
                     int number_of_key_value_pairs,
                     ...);

int
cyclients_record_remove(const char *token,
                        int company_id,
                        int record_id);


//////////////////////////////////////////////////////////
// Custom Fields
//////////////////////////////////////////////////////////

/* Дополнительные поля позволяют добавлять к отдельным 
 * объектам системы свойства заданного типа и впоследствии 
 * привязывать к этим полям значения, соответствующие 
 * данному типу. На данный момент функционал реализован 
 * для Записей и Клиентов.
 * При создании дополнительных полей записи и клиента 
 * становится возможным передавать собственные значения для 
 * полей. Дополнительные поля уникальны для каждой компании. 
 * После создания дополнительных полей, их значения для 
 * конкретной записи могут передаваться в необязательном 
 * поле custom_fields в виде пар ключ-значение где ключ 
 * это поле "code" дополнительного поля.
 * Объекты Дополнительных полей:
 * code - string - Код поля по которому устанавливаются 
 * значения для полей записи
 * id - integer - Уникальный идентификатор поля
 * type - CustomFieldType - Тип поля
 * show_in_ui - boolean - Показывать ли поле в интерфейсе
 * title - string - Название поля
 * user_can_edit - boolean - Можно ли редактировать в интерфейсе
 * values - array or null - Список допустимых значений для 
 * типа "список"
 *
 * На данный момент поддерживаются следующие типы (поле code):
 * text - строка длиной до 255 символов
 * number - число
 * select - список
 * date - Дата (Y-m-d)
 * datetime - Дата и время (Y-m-d H:i:s)
 *
 * Следующие коды полей являются зарезервированными:
 * yc_partner_public_key - text - Используется для 
 * определения партнера при создании записи, является более 
 * приоритетным, чем Bearer-токен из авторизации*/

typedef enum {
	CYCLIENTS_CATEGORY_RECORD,
	CYCLIENTS_CATEGORY_CLIENT,
} CYCLIENTS_CATEGORY_TYPE;

/* Получение коллекции полей филиала */
CYCLIENTS_COUNTER
cyclients_custom_fields(const char *token,
                        CYCLIENTS_CATEGORY_TYPE category,
                        int company_id,
                        void *userdata,
                        int (*callback)(void *userdata, 
                                        const CYCCustomField *field));

/* Добавление дополнительного поля 
 * Для добавления поля пользователь должен быть добавлен в 
 * связанной с филиалом сети, и иметь права доступа в разделе:
 * Настройки - Доступ к разделу Дополнительные поля - 
 * Создание доп. полей
 * type - Тип поля
 * code - Идентификатор поля
 * title - Название поля
 * user_can_edit - Может ли пользователь редактировать поле
 * show_in_ui - Показывать ли поле в интерфейсе */
CYCLIENTS_ID
cyclients_custom_field_new(const char *token,
						   CYCLIENTS_CATEGORY_TYPE category,
						   int company_id,
						   const char *type,
						   const char *code,
						   const char *title,
						   bool user_can_edit,
						   bool show_in_ui);

int
cyclients_custom_field_set(const char *token,
                           CYCLIENTS_CATEGORY_TYPE category,
                           int company_id,
                           int field_id,
                           int number_of_key_value_pairs,
                           ...);

int
cyclients_custom_field_remove(const char *token,
                              CYCLIENTS_CATEGORY_TYPE category,
                              int company_id,
                              int field_id);

#ifdef __cplusplus
}
#endif

#endif // CYCLIENTS_H
