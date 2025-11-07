cmake_minimum_required(VERSION 3.9)
set(TARGET cYclients)

project(${TARGET} VERSION 1.0
  DESCRIPTION "Yclients API in c"
  LANGUAGES C)

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/partner_token.h)
  message("To get partner token - register in https://yclients.com/appstore/developers")
  message("create file partner_token.h with content:\n #define SETUP_PARTNER_TOKEN(partner_token) partner_token = \"your_token\";")
  message(FATAL_ERROR "no partner_token.h")
endif()

if (APPLE)
	list(APPEND CMAKE_EXE_LINKER_FLAGS "-framework Foundation")	
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND CMAKE_C_FLAGS "-DDEBUG")
endif()

set(HEADERS
  src/cJSON.h
  src/log.h	
  src/config.h
	src/curl_transport.h
	src/structs.h	
	cYclients.h	
)

set(SOURCES
  src/cJSON.c
  src/log.c	
  src/curl_transport.c	
  src/structs.c		
  src/companies.c		
  src/services.c		
  src/auth.c
)

add_library(${TARGET} ${SOURCES} ${HEADERS})
target_link_libraries(${TARGET} curl)

if(${BUILD_TEST})
	add_executable(${TARGET}_test test.c)
	target_link_libraries(${TARGET}_test ${TARGET})
endif()
