// dater.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "resource.h"

using namespace std;

BOOL NotifyIconize(DWORD dwMessage, LPCTSTR pInfoTitle , LPCTSTR pInfo);

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

#pragma comment(lib,"Comctl32.lib")
	InitCommonControls();
	HWND hBalloon = CreateWindow(_T("tooltips_class32"),
		NULL,
		WS_POPUP|0x02|0x40|0x01,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		NULL,
		NULL);
	if(!hBalloon)
	{
		MessageBox(NULL, _T("balloon"),NULL,MB_ICONERROR);
		return __LINE__;
	}
	if(!SendMessage(hBalloon,
		TTM_SETTITLE, // Adds a standard icon and title string to a ToolTip    
		1,
		(LPARAM)_T("title")))
	{
		MessageBox(NULL, _T("balloon sendmessage"),NULL,MB_ICONERROR);
		return __LINE__;
	}
	if(!NotifyIconize(NIM_ADD, NULL, NULL))
	{
		MessageBox(NULL, _T("NotifyAdd"),NULL,MB_ICONERROR);
		return __LINE__;
	}
	if(!NotifyIconize(NIM_MODIFY, _T("dater"), outmessage.c_str()))
	{
		MessageBox(NULL, _T("NotifyModify"),NULL,MB_ICONERROR);
		return __LINE__;
	}
	Sleep(10000);
	NotifyIconize(NIM_DELETE, NULL, NULL);
	//MessageBox(NULL, outmessage.c_str(), _T("dater"), MB_ICONINFORMATION);
	return 0;
}



BOOL NotifyIconize(DWORD dwMessage, LPCTSTR pInfoTitle , LPCTSTR pInfo)
{
	NOTIFYICONDATA nid;
	ZeroMemory(&nid,sizeof(nid));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = NULL;
	nid.uID = 123;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | 0x00000010;
	nid.dwInfoFlags      = 0x00000001;
	nid.uTimeout         = 300;
	nid.uCallbackMessage = 0; //WM_APP_TRAYMESSAGE;
	nid.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_MAIN));
	lstrcpy(nid.szTip, _T("dater"));
	if(pInfoTitle)
		lstrcpy( nid.szInfoTitle, pInfoTitle );
	if(pInfo)
		lstrcpy( nid.szInfo, pInfo );
	
	return Shell_NotifyIcon( dwMessage,&nid);
}