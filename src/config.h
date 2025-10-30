#ifndef CYCLIENTS_CONFIG_H
#define CYCLIENTS_CONFIG_H

//#ifdef _MSC_VER
//#ifndef bool
//#define bool char
//#define true 1
//#define false 0
//#endif
//#esle
#include <stdbool.h>
//#endif

#define URL "https://api.yclients.com/api/v1"
#define PORT 443

#define STRCPY(dst, src) strncpy(dst, src, sizeof(dst) - 1); dst[sizeof(dst)-1]=0;

#endif // CYCLIENTS_CONFIG_H
