#ifndef CYCLIENTS_H
#define CYCLIENTS_H

#include "src/structs.h"

//////////////////////////////////////////////////////////
// Authorization
//////////////////////////////////////////////////////////
typedef	enum{
	CYCLIENTS_AUTH_ERROR,
	CYCLIENTS_AUTH_AUTHORIZED,
	CYCLIENTS_AUTH_2FA, // 2-factor authorization is needed
} CYCLIENTS_AUTH;

CYCLIENTS_AUTH
cyclients_login(const char *login, 
								const char *password,
								const cyclients_user_t **user,
								const cyclients_2fa_t  **user2fa);

CYCLIENTS_AUTH
cyclients_login_2fa(const char *login, 
										const char *password,
										const char *uuid,
                    const char *secret,
										const cyclients_user_t **user);


int
cyclients_companies(const char *token,
									  char *company_id,
										void *userdata,
										int (*callback)(void *userdata, 
																		const cyclients_company_t *company));
int
cyclients_services(const char *token,
									 int company_id,
									 char *service_id,
									 void *userdata,
									 int (*callback)(void *userdata, 
																	 const cyclients_service_t *service));


#endif // CYCLIENTS_H






