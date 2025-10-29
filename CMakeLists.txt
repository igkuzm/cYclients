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

set(SOURCES
  src/cJSON.c
  src/token.c
)

add_library(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} curl)

if(${BUILD_TEST})
	add_executable(${TARGET}_test test.c)
	target_link_libraries(${TARGET}_test ${TARGET})
endif()
