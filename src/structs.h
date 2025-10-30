/*
 *  structs.h
 *  cYclients
 *
 *  Created by Igor Sementsov on 30.10.25.
 *  Copyright 2025 ProZubi. All rights reserved.
 *
 */
#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include "cJSON.h"
#include "config.h"

typedef struct cyclients_user_ {
	int id;
	char user_token[64];
	char name[256];
	char phone[32];
	char login[32];
	char email[128];
	char avatar[256];
	bool is_approved;
	bool is_email_confirmed;
} cyclients_user_t;

int 
cyclients_user_from_json(const cJSON *json,
						 cyclients_user_t *t);
							 



#endif // STRUCTS_H
