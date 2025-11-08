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


#endif // CYCLIENTS_H
