// dater.cpp
//

#include "stdafx.h"
#include "resource.h"

#include "../MyUtility/UTF16toUTF8.h"
#include "../MyUtility/UrlEncode.h"
#include "../MyUtility/OpenCommon.h"
#include "../MyUtility/stdwin32/stdwin32.h"

using namespace std;
using namespace stdwin32;

wstring enc(const wstring& os)
{
	BYTE* p8 = UTF16toUTF8(os.c_str());
	char* pu8 = urlencodenew((char*)p8);
	size_t pu8len = strlen(pu8);
	
	size_t pu8wlen = (pu8len+1)*2;
	WCHAR* pu8w = (WCHAR*)calloc(pu8wlen,1);
	MultiByteToWideChar(CP_ACP,
		0,
		pu8,
		pu8len,
		pu8w,
		pu8wlen);

	wstring ret = pu8w;
	free(pu8w);
	free(pu8);
	free(p8);
	return ret;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR     lpCmdLine,
                     int       nCmdShow )
{
	_tsetlocale(LC_ALL, _T(""));
	tstring outmessage;

	 TCHAR buff[256]; buff[0]=0;
     time_t now = time(NULL);
     struct tm *pnow = localtime(&now);
 
	_tcsftime(buff, countof(buff), _T("%x (%a) %X"), pnow);
	outmessage += buff;

	tstring strarg;
	strarg += _T("/title:dater /icon:");
	strarg += _T("\"");
	strarg += stdGetModuleFileName();
	strarg += _T("\" ");
	strarg += _T("/duration:10000 ");
	strarg += _T("/balloonicon:1 ");
	strarg += _T("\"") + enc(outmessage) + _T("\"");

	wstring balloonexe=stdCombinePath(
		stdGetParentDirectory(stdGetModuleFileName()),
		L"showballoon.exe");
//		L"argCheck.exe");

	// ShellExecute(NULL, L"open", balloonexe.c_str(), strarg.c_str(), NULL, SW_SHOW);
	HANDLE hProcess = NULL;
//	LPCTSTR ppp = _T("/title:dater /icon:\"C:\\Linkout\\dater\\daterD.exe\" /balloonicon:1 \"2016%2f11%2f22+%28%e7%81%ab%29+21%3a04%3a03\"");
//	if (!OpenCommon(NULL, balloonexe.c_str(), ppp, NULL, &hProcess))
	if (!OpenCommon(NULL, balloonexe.c_str(), strarg.c_str(), NULL, &hProcess))
	{
		return 1;
	}

	WaitForSingleObject(hProcess, 10000*10);
	CloseHandle(hProcess);
//	Sleep(10000);
	return 0;
}


