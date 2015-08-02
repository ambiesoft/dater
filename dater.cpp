// dater.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "resource.h"

#include "../MyUtility/UTF16toUTF8.h"
#include "../MyUtility/UrlEncode.h"
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

	 TCHAR buff[256];
     time_t now = time(NULL);
     struct tm *pnow = localtime(&now);
     TCHAR week[][3] = {_T("日"),_T("月"),_T("火"),_T("水"),_T("木"),_T("金"),_T("土")};

     _stprintf(buff, _T("今日は%2d年%2d月%2d日(%s)です。\n"),
        pnow->tm_year+1900,
	    pnow->tm_mon + 1,
	    pnow->tm_mday,
	    week[pnow->tm_wday]);

	tstring outmessage;
	outmessage = buff;


	_stprintf (buff,_T("時刻は %02d:%02d:%02d です。"),pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	
	outmessage += buff;

	tstring strarg;
	strarg += _T("/title:dater /icon:");
	strarg += _T("\"");
	strarg += stdGetModuleFileName();
	strarg += _T("\"");
	strarg += _T(" /duration:5000 ");
	strarg += enc(outmessage);

	wstring balloonexe=stdCombinePath(
		stdGetParentDirectory(stdGetModuleFileName().c_str()).c_str(),
		L"showballoon.exe");
	ShellExecute(NULL,NULL,	balloonexe.c_str(),	strarg.c_str(),	NULL,	SW_SHOW);

	return 0;
}


