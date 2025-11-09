#include "cYclients.h"
#include <string.h>


int companies_cb(void *userdata, const CYCCompany *company)
{
	int *company_id = userdata;
	printf("COMPANY: %s\n", company->title);
	*company_id = company->id;

	return 0;
}


int services_cb(void *userdata, const CYCService *service)
{
	printf("SERVICE: %s\n", service->title);
	return 0;
}

int main(int argc, char *argv[])
{
	const CYCUser *user = NULL;
	const CYC2fa  *user2fa = NULL;
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

	int company_id;
	cyclients_companies(user->user_token,
			NULL,
		 	&company_id, companies_cb);

	cyclients_services(user->user_token,
		 	company_id, "23599584",
		 	NULL, services_cb);
	

	return 0;
}

// vim:ft=c
