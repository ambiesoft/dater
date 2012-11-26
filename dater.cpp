// dater.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include <tchar.h>
#include <time.h>
#include <string>
using namespace std;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	 char buff[256];
     time_t now = time(NULL);
     struct tm *pnow = localtime(&now);
     char week[][3] = {"日","月","火","水","木","金","土"};

     sprintf(buff, "今日は%2d年%2d月%2d日(%s)です。\n",
        pnow->tm_year+1900,
	    pnow->tm_mon + 1,
	    pnow->tm_mday,
	    week[pnow->tm_wday]);

	string outmessage;
	outmessage = buff;


	sprintf(buff,"時刻は %d:%d:%d です。",pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	
	outmessage += buff;

	MessageBox(NULL, outmessage.c_str(), _T("dater"), MB_ICONINFORMATION);
	return 0;
}



