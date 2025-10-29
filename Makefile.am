AUTOMAKE_OPTIONS = subdir-objects

lib_LTLIBRARIES = libcyclients.la
libcyclients_la_CFLAGS =
libcyclients_la_LDFLAGS =

nobase_include_HEADERS = \
	src/cJSON.h \
	src/config.h \
	src/curl_transport.h \
	cYclients.h

libcyclients_la_SOURCES = \
  src/cJSON.c \
  src/curl_transport.c \
  src/token.c	

libcyclients_la_LIBADD = 

if BUILD_TEST
bin_PROGRAMS = cYclients_test
cYclients_test_CFLAGS = 
cYclients_test_LDFLAGS = 
cYclients_test_SOURCES = test.c
cYclients_test_LDADD = libcyclients.la -lcurl 
endif
