// dater.cpp : �A�v���P�[�V�����p�̃G���g�� �|�C���g�̒�`
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
     TCHAR week[][3] = {_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("�y")};

     _stprintf(buff, _T("������%2d�N%2d��%2d��(%s)�ł��B\n"),
        pnow->tm_year+1900,
	    pnow->tm_mon + 1,
	    pnow->tm_mday,
	    week[pnow->tm_wday]);

	tstring outmessage;
	outmessage = buff;


	_stprintf (buff,_T("������ %d:%d:%d �ł��B"),pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	
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



