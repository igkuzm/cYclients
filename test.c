#include "cYclients.h"

int main(int argc, char *argv[])
{
	if (argc < 2){
		printf("usage: %s login password\n", argv[0]);
		return 0;
	}
	const char *token = cyclients_get_user_token(argv[1], argv[2]);
	printf("TOKEN: %s\n", token);
	if (token == NULL) {
		return 1;
	}
 
    return 0;
}
