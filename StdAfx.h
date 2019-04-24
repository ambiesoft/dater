
#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN

#if _MSC_VER < 1500
#include <checkaccess.h>
#endif

#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>


#include <tchar.h>
#include <time.h>
#include <string>

#include "C:\\Linkout\\CommonDLL\\TimedMessageBox.h"

#include "../lsMisc/tstring.h"
#include "../lsMisc/UTF16toUTF8.h"
#include "../lsMisc/UrlEncode.h"
#include "../lsMisc/OpenCommon.h"
#include "../lsMisc/stdwin32/stdwin32.h"
#include "../lsMisc/stdosd/stdosd.h"
#include "../lsMisc/CommandLineParser.h"

#define APPNAME L"dater"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ 


#define I18N(s)	(s)

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
