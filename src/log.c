#include "log.h"

static char __buf[BUFSIZ];

char *STR(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vsnprintf(__buf, BUFSIZ-1,fmt, args);
	va_end(args);
	return __buf;
}

char * STR_ERR(const char *fmt, ...) {
	char str[BUFSIZ];
	va_list args;
	va_start(args, fmt);
	vsnprintf(str, BUFSIZ-1,fmt, args);
	va_end(args);
	snprintf(__buf, BUFSIZ-1,"E/%s: %d: %s", __FILE__, __LINE__, str);
	return __buf;
}

char * STR_LOG(const char *fmt, ...) {
	char str[BUFSIZ];
	va_list args;
	va_start(args, fmt);
	vsnprintf(str, BUFSIZ-1,fmt, args);
	va_end(args);
	snprintf(__buf, BUFSIZ-1,"E/%s: %d: %s", __FILE__, __LINE__, str);
	return __buf;
}

#ifdef __ANDROID__
#elif defined __APPLE__
#else
void LOG(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);
	vsnprintf(__buf, BUFSIZ-1,fmt, args);
	va_end(args);
	fprintf(stderr, "%s: %d: %s\n",   __FILE__, __LINE__, __buf);
}
void ERR(const char *fmt, ...) {
	char str[BUFSIZ];
	va_list args;
	va_start(args, fmt);
	vsnprintf(__buf, BUFSIZ-1,fmt, args);
	va_end(args);
	snprintf(str, BUFSIZ-1,"E/%s: %d: %s", __FILE__, __LINE__, __buf);
	perror(str);
}
#endif
