#ifndef CYCLIENTS_CONFIG_H
#define CYCLIENTS_CONFIG_H

#ifdef _MSC_VER
#ifndef bool
#define bool char
#define true 1
#define false 0
#endif
#else
#include <stdbool.h>
#endif

#define URL "https://api.yclients.com/api/v1"
#define PORT 443
#define CURL_SSL_VERIFY 0L

#endif // CYCLIENTS_CONFIG_H
