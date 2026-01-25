// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CYCLIENTS__INCLUDED_)
#define AFX_STDAFX_H__CYCLIENTS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Local Header Files
#define _MPRINTF_REPLACE
#include <curl/mprintf.h>
#include <curl/curl.h>
#include "src/log.h"
#include "src/alloc.h"
#include "src/stb_ds.h"
#include "src/strtok_foreach.h"
#include "src/json_to_struct.h"
#include "src/structs.h"

// TODO: reference additional headers your program requires here

#endif // !defined(AFX_STDAFX_H__CYCLIENTS__INCLUDED_)
