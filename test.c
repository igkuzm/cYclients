#include "cYclients.h"
#include "src/stb_ds.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


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

int categories_cb(void *userdata, const CYCServiceCategory *category)
{
	printf("CATEGORY: %s\n", category->title);
	return 0;
}

int users_roles_cb(void *userdata, const CYCUserRole *user_role)
{
	printf("USER_ROLE: %s\n", user_role->title);
	return 0;
}

int users_permissions_cb(void *userdata, const CYCUserPermissions *user_permissions)
{
	printf("USER_PERMISSIONS RECORDS ACCESS: %s\n", user_permissions->records_access?"true":"false");
	return 0;
}

int clients_cb(void *userdata, int n, const kvpair_t *kvpair)
{
	int i, *client_id = userdata;
	for (i = 0; i < n; ++i) {
		printf("KEY: %s, VALUE: %s\n", 
				kvpair[i].key, kvpair[i].value);
	}
    if (kvpair){
        *client_id = atoi((char *)shget(kvpair, "id"));
    }
	return 0;
}

int file_cb(void *userdata, const CYCFile *file)
{
	printf("FILE NAME: %s\n", file->name);
	return 0;
}

int visit_cb(void *userdata, const CYCRecord *visit)
{
	printf("VISIT COMMENT: %s\n", visit->comment);
	return 0;
}

int comments_cb(void *userdata, const CYCComment *comment)
{
	printf("COMMENT: %s\n", comment->text);
	return 0;
}



int main(int argc, char *argv[])
{
	const CYCUser *user = NULL;
	const CYC2fa  *user2fa = NULL;
	CYCLIENTS_AUTH auth = CYCLIENTS_AUTH_ERROR;
	char secret[16], login[32], password[32];
	
	if (argc < 2){
		//printf("usage: %s login password\n", argv[0]);
		//return 0;
		printf("enter login\n");
		scanf("%31s", login);
		printf("enter password\n");
		scanf("%31s", password);
	} else {
		strncat(login,argv[1],31);
		strncat(password,argv[2],31);
	}
	
	auth = cyclients_login(login, password,
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

	cyclients_service_categories(
			user->user_token, company_id, 
			NULL, categories_cb);
	
	cyclients_services(user->user_token,
		 	company_id,
		 	NULL, services_cb);


	CYCService *service = cyclients_service_get(
			user->user_token, company_id, 3862837);
	
	const CYCUserPermissions *permissions =
	cyclients_user_permissions(user->user_token, company_id, user->id);
	if (permissions){
	   printf("USER_PERMISSIONS TIMETABLE ACCESS: %s\n", permissions->timetable_access?"true":"false");
	   printf("USER_PERMISSIONS AUTH ENABLE CHECK IP: %s\n", permissions->auth_enable_check_ip?"true":"false");
    }
	
    int client_id;
	cyclients_clients_search(user->user_token, company_id, "name, id", "Семенцов Игорь", &client_id, clients_cb);
    printf("CLIENT_ID: %d\n", client_id);
    
    //cyclients_client_files(user->user_token, company_id, client_id, NULL, file_cb);

    //cyclients_client_visits(user->user_token, company_id, client_id, NULL, visit_cb);

    CYCClient *client = cyclients_client_get(user->user_token, company_id, client_id);
    if (client)
    {
        printf("CLIENT NAME: %s\n", client->name);
    }
	cyclients_client_comment_new(user->user_token, company_id, client_id, "hello world!");
	cyclients_client_comments(user->user_token, company_id, client_id, NULL, comments_cb);

    return 0;
}

// vim:ft=c
