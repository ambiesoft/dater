// dater.cpp : �A�v���P�[�V�����p�̃G���g�� �|�C���g�̒�`
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
     char week[][3] = {"��","��","��","��","��","��","�y"};

     sprintf(buff, "������%2d�N%2d��%2d��(%s)�ł��B\n",
        pnow->tm_year+1900,
	    pnow->tm_mon + 1,
	    pnow->tm_mday,
	    week[pnow->tm_wday]);

	string outmessage;
	outmessage = buff;


	sprintf(buff,"������ %d:%d:%d �ł��B",pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	
	outmessage += buff;

	MessageBox(NULL, outmessage.c_str(), _T("dater"), MB_ICONINFORMATION);
	return 0;
}



