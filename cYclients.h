#ifndef CYCLIENTS_H
#define CYCLIENTS_H

#include "src/structs.h"

//return user struct with user token end etc.
const cyclients_user_t *
cyclients_login(const char *login, 
				const char *password);



#endif // CYCLIENTS_H






