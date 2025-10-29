/*
 *  curl_transport.h
 *  cYclients
 *
 *  Created by Igor Sementsov on 30.10.25.
 *  Copyright 2025 ProZubi. All rights reserved.
 *
 */

#ifndef CURL_TRANSPORT_H
#define CURL_TRANSPORT_H

#include "cJSON.h"

cJSON *
curl_transport_post(const char *url,
					const char *auth,
					const char *post);
						  

#endif // CURL_TRANSPORT_H
