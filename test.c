#include "cYclients.h"
#include <string.h>

int main(int argc, char *argv[])
{
	const cyclients_user_t *user = NULL;
	const cyclients_2fa_t  *user2fa = NULL;
	CYCLIENTS_AUTH auth = CYCLIENTS_AUTH_ERROR;
	char secret[16];
	
	if (argc < 2){
		printf("usage: %s login password\n", argv[0]);
		return 0;
	}
	
	auth = cyclients_login(argv[1], argv[2],
		 	&user, &user2fa);
	
	if (auth == CYCLIENTS_AUTH_2FA){
		// login with 2fa
		if (user2fa == NULL){
			printf("Unknown ERROR!\n");
			return 1;
		}

		if (user2fa->attempts_left < 1){
			printf("You have no attempts left\n");
			return 1;
		}

		while (user2fa->attempts_left > 0 && 
				auth != CYCLIENTS_AUTH_AUTHORIZED)
		{
			printf("Please enter code, that was send you by %s: %s\n",
				user2fa->transport.type, user2fa->transport.recipient);
			printf("You have %d attempts left\n", 
					user2fa->attempts_left);

			memset(secret, 0, sizeof(secret));
			scanf("%s", secret);
			
			auth = cyclients_login_2fa(
					argv[1], argv[2], 
					user2fa->uuid,
					secret, &user);
		}
	}
	
	if (auth == CYCLIENTS_AUTH_ERROR) {
		printf("can't login to Yclients\n");
		return 1;
	}

	if (user == NULL){
		printf("Unknown error\n");
		return 1;
	}

	printf("Authorized as: %s\n", user->name);
	printf("TOKEN: %s\n", user->user_token);
	return 0;
}

// vim:ft=c
