// dater.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"


using namespace std;

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


	_stprintf (buff,_T("時刻は %d:%d:%d です。"),pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	
	outmessage += buff;

	HWND hBalloon = CreateWindow(TOOLTIPS_CLASS,
		NULL,
		WS_POPUP|TTS_NOPREFIX|TTS_BALLOON|TTS_ALWAYSTIP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		NULL);
	MessageBox(NULL, outmessage.c_str(), _T("dater"), MB_ICONINFORMATION);
	return 0;
}



