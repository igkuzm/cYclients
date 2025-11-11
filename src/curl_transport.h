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

typedef long HTTP_RESPONCE;

// perform POST request and return responce code
HTTP_RESPONCE
curl_transport_exec(const char *request_url,
										const char *auth_header,
										const char *http_method,
										const char *post_data,
										cJSON **json);
						  

#endif // CURL_TRANSPORT_H
