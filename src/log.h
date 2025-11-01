/**
 * File              : log.h
 * Author            : Igor V. Sementsov <ig.kuzm@gmail.com>
 * Date              : 19.03.2023
 * Last Modified Date: 01.11.2025
 * Last Modified By  : Igor V. Sementsov <ig.kuzm@gmail.com>
 */

/**
 * log.h
 * Copyright (c) 2023 Igor V. Sementsov <ig.kuzm@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Debugging in Android/iOS and other platforms
 */

#ifndef k_lib_log_h
#define k_lib_log_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

char *STR(const char *fmt, ...);
char * STR_ERR(const char *fmt, ...);
char * STR_LOG(const char *fmt, ...);

#ifdef __ANDROID__
	#include <android/log.h>
	#define LOG(fmt, ...) __android_log_print(ANDROID_LOG_INFO,  __FILE__, "_%s: " fmt, __func__, __VA_ARGS__)
	#define ERR(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, __FILE__, "_%s: %d: " fmt, __func__, __LINE__, __VA_ARGS__) 	
#elif defined __APPLE__
	#include <CoreFoundation/CoreFoundation.h>
	void NSLog(CFStringRef format, ...);
	#define LOG(fmt, ...) NSLog(CFSTR(fmt), ##__VA_ARGS__)
	#define ERR(fmt, ...) LOG("E/_%s: %d: %s", __func__, __LINE__, STR(fmt, __VA_ARGS__)) 
#else

void LOG(const char *fmt, ...);
void ERR(const char *fmt, ...);

#endif

#ifdef __cplusplus
}
#endif

#endif /* ifndef k_lib_log_h */
