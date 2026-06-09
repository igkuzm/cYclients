cmake_minimum_required(VERSION 3.9)
set(TARGET cYclients)

project(${TARGET} VERSION 1.0
  DESCRIPTION "Yclients API in c"
  LANGUAGES C)

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/partner_token.h)
  message("To get partner token - register in https://yclients.com/appstore/developers - see ReadMe")
  message(FATAL_ERROR "no partner_token.h")
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
  src/curl_transport.c	
  src/structs.c		
  src/companies.c		
  src/categories.c		
  src/services.c		
  src/users.c	
  src/clients.c	
  src/records.c	
  src/stb_ds.c	
  src/custom_fields.c	
  src/auth.c
)

# Determine the location of the libraries to use based on the platform.
if(ANDROID)
	ADD_LIBRARY(curl STATIC IMPORTED)
	SET_TARGET_PROPERTIES(curl PROPERTIES IMPORTED_LOCATION
		${CMAKE_CURRENT_SOURCE_DIR}/android/curl/${ANDROID_ABI}/libcurl.a)
	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/android/curl/include)
	set(LIBZ z)
elseif(IOS)
	ADD_LIBRARY(curl STATIC IMPORTED)
	SET_TARGET_PROPERTIES(curl PROPERTIES IMPORTED_LOCATION 
		${CMAKE_CURRENT_SOURCE_DIR}/iOS/curl/libcurl.a)
	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/iOS/curl/include)
elseif(WIN32)
	if (CMAKE_BUILD_TYPE STREQUAL "WINNT")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DTARGETWINNT")
		set(WINDIR winnt)
	else()
		set(WINDIR win32)
	endif()
#libz
	add_library(z STATIC IMPORTED)
	set_target_properties(z PROPERTIES IMPORTED_LOCATION
		${CMAKE_CURRENT_SOURCE_DIR}/${WINDIR}/libz.a)
#curl
add_library(curl STATIC IMPORTED)
set_target_properties(curl PROPERTIES 
		IMPORTED_LOCATION
		${CMAKE_CURRENT_SOURCE_DIR}/${WINDIR}/curl/lib/libcurl.dll.a)	
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${WINDIR}/curl/include)
else()
	find_package(CURL)
	include_directories(${CURL_INCLUDE_DIRS})
endif()

add_library(${TARGET} ${SOURCES} ${HEADERS})
target_link_libraries(${TARGET} curl)
include_directories(${TARGET} ${CMAKE_SOURCE_DIR})

if(${WITH_TEST})
  add_executable(${TARGET}_test test.c)
  target_link_libraries(${TARGET}_test ${TARGET})
endif()

#copy files
if (WIN32)
	#curl libs
	#Copy DLLs
	file(GLOB files 
		"${CMAKE_CURRENT_SOURCE_DIR}/${WINDIR}/curl/bin/*.dll"
		"${CMAKE_CURRENT_SOURCE_DIR}/${WINDIR}/curl/lib/*.dll"
		"${CMAKE_CURRENT_SOURCE_DIR}/${WINDIR}/pthreads-win32/lib/pthreadGC1.dll"
		"${CMAKE_CURRENT_SOURCE_DIR}/${WINDIR}/pthreads-win32/bin/libwinpthread-1.dll"
		)	
	#Copy
	foreach(_file ${files})
			file(INSTALL
				DESTINATION "${CMAKE_BINARY_DIR}"
				FILES "${_file}"
			)
	endforeach()	
endif()
