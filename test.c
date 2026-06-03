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

int custom_fields_cb(void *d, const CYCCustomField *f)
{
	printf("CUSTOM FIELD: %s\n", f->title);
	printf("CUSTOM FIELD TYPE: %s\n", f->type.title);
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

int records_cb(void *userdata, const CYCRecord *record)
{
	printf("RECORD ID: %d\t", record->id);
    printf("DATE: %s\t", record->date);
    printf("COMMENT: %s\n", record->comment);
	return 1;
}

int main(int argc, char *argv[])
{
	const CYCUser *user = NULL;
	const CYC2fa  *user2fa = NULL;
	CYCLIENTS_AUTH auth = CYCLIENTS_AUTH_ERROR;
	char secret[16], login[32], password[32];
	int company_id;
	
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

	cyclients_companies(user->user_token,
			NULL,
		 	&company_id, companies_cb);

//	cyclients_service_categories(
//			user->user_token, company_id, 
//			NULL, categories_cb);
//	
//	cyclients_services(user->user_token,
//		 	company_id,
//		 	NULL, services_cb);
//
//
//	CYCService *service = cyclients_service_get(
//			user->user_token, company_id, 3862837);
//	
//	const CYCUserPermissions *permissions =
//	cyclients_user_permissions(user->user_token, company_id, user->id);
//	if (permissions){
//	   printf("USER_PERMISSIONS TIMETABLE ACCESS: %s\n", permissions->timetable_access?"true":"false");
//	   printf("USER_PERMISSIONS AUTH ENABLE CHECK IP: %s\n", permissions->auth_enable_check_ip?"true":"false");
//    }
	
		//int client_id = 0;
	//cyclients_clients_search(user->user_token, company_id, "name, id", "today", &client_id, clients_cb);
		//printf("CLIENT_ID: %d\n", client_id);
	
	/*cyclients_client_remove(user->user_token, company_id, 363089556);*/
	//int client_id = cyclients_client_new(user->user_token, company_id, "тестовый пациент", "+788299329912", 0);
    
    //cyclients_client_files(user->user_token, company_id, client_id, NULL, file_cb);

    //cyclients_client_visits(user->user_token, company_id, client_id, NULL, visit_cb);

//    CYCClient *client = cyclients_client_get(user->user_token, company_id, client_id);
//    if (client)
//    {
//        printf("CLIENT NAME: %s\n", client->name);
//    }

//	int comment_id = cyclients_client_comment_new(user->user_token, company_id, client_id, "hello world!");
//	printf("COMMENT_ID: %d\n", comment_id);
	//cyclients_client_comments(user->user_token, company_id, client_id, NULL, comments_cb);
    
    cyclients_records(user->user_token, company_id, "2026-06-03", "2026-06-03", NULL, records_cb);

//    int staff_id = 3862837;
//	
//    int record_id = cyclients_record_new(user->user_token,company_id,staff_id,"TEST","+79990407731","28.01.2026 13:00",0,"это тестовая запись","api_id afasdfdasf",1, "mykey", "myvalue");
//        
//	printf("RECORD_ID: %d\n", record_id);

	/*cyclients_custom_field_new(user->user_token, CYCLIENTS_CATEGORY_RECORD,company_id, "texthh", "kuzm_field", "kuzmich field", true, true);*/
	
	/*cyclients_custom_fields(user->user_token, CYCLIENTS_CATEGORY_RECORD, company_id, NULL, custom_fields_cb);*/
    
    return 0;
}

// vim:ft=c
