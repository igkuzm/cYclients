#ifndef CYCLIENTS_H
#define CYCLIENTS_H

#include "src/structs.h"

//return user struct with user token end etc.
const cyclients_user_t *
cyclients_login(const char *login, 
				const char *password,
                const cyclients_2fa_t **user2fa);

const cyclients_user_t *
cyclients_login_2fa(const char *login, 
				    const char *password,
					const char *uuid,
                    const char *secret);



#endif // CYCLIENTS_H






