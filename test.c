#include "cYclients.h"

int main(int argc, char *argv[])
{
	cyclients_user_t *user;
	
	if (argc < 2){
		printf("usage: %s login password\n", argv[0]);
		return 0;
	}
	
	user = cyclients_login(argv[1], argv[2]);
	if (user == NULL) {
		return 1;
	}
	printf("TOKEN: %s\n", user->user_token);
 
    return 0;
}
