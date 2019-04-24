// dater.cpp
//

#include "stdafx.h"

#include "../lsMisc/GetLastErrorString.h"
#include "../lsMisc/SetClipboardText.h"

#include "resource.h"



using namespace std;
// using namespace stdwin32;
using namespace Ambiesoft;
using namespace Ambiesoft::stdosd;

static LPCTSTR pDefaultFormat = _T("%x (%a) %X");



void ShowHelp()
{
	tstring msg = _T("dater [/locale locale] [/format format] [/balloon] [/count count]\n\n");
	msg += _T("locale: string passed to setlocale()\n");
	
	msg += _T("format: format string passed to strftime(), default format is \"");
	msg += pDefaultFormat;
	msg += _T("\"\n");

	msg += _T("/balloon: Use balloon\n");
	msg += _T("count: Number of seconds to automatically close\n");

	MessageBox(NULL,
		msg.c_str(),
		APPNAME,
		MB_ICONINFORMATION);

}
void ErrorQuit(LPCWSTR pMessage)
{
	MessageBox(NULL,
		pMessage,
		APPNAME,
		MB_ICONERROR);

	ExitProcess(1);
}
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR     lpCmdLine,
	int       nCmdShow)
{
	tstring localestring;
	tstring format;
	bool isHelp = false;
	bool isBalloon = false;
	int count = 0;
	bool isClip = false;
	tstring clipformat;

	CCommandLineParser parser(_T("dater: Shows Date"));
	parser.AddOption(_T("/locale"), 1, &localestring,
		ArgEncodingFlags::ArgEncodingFlags_Default,_T("Local to set"));
	parser.AddOption(_T("/format"), 1, &format,
		ArgEncodingFlags::ArgEncodingFlags_Default, _T("time format"));
	parser.AddOption(_T("/balloon"), 0, &isBalloon,
		ArgEncodingFlags::ArgEncodingFlags_Default, _T("show balloon instead of default window"));
	parser.AddOption(_T("/h"), _T("/?"), 0, &isHelp,
		ArgEncodingFlags::ArgEncodingFlags_Default, _T("show help"));
	parser.AddOption(_T("/count"), 1, &count,
		ArgEncodingFlags::ArgEncodingFlags_Default, _T("second to close window"));
	parser.AddOption(_T("/clip"), 0, &isClip,
		ArgEncodingFlags::ArgEncodingFlags_Default, _T("copy to the clipboard"));
	parser.AddOption(_T("/clipformat"), 1, &clipformat,
		ArgEncodingFlags::ArgEncodingFlags_Default, _T("time format used for copying to the clipboard"));

	parser.Parse();

	if (isHelp)
	{
		MessageBox(NULL,
			parser.getHelpMessage().c_str(),
			APPNAME,
			MB_ICONINFORMATION); 
		return 0;
	}
	if (parser.hadUnknownOption())
	{
		tstring msg;
		msg += I18N(_T("Unknow Option:\n\n"));
		msg += parser.getUnknowOptionStrings();
		ErrorQuit(msg.c_str());
	}
	_tsetlocale(LC_ALL, localestring.c_str());

	tstring outmessage;

	TCHAR buff[256] = {};

	time_t now = time(NULL);
	struct tm tmnow;
	localtime_s(&tmnow, &now);

	_tcsftime(buff, _countof(buff), format.empty() ? 
		pDefaultFormat : format.c_str(), 
		&tmnow);
	outmessage += buff;

	if (isClip)
	{
		_tcsftime(buff, _countof(buff), clipformat.empty() ?
			pDefaultFormat : clipformat.c_str(),
			&tmnow);
		if (!SetClipboardText(nullptr,buff))
		{
			tstring message = stdFormat(_T("Failed to set to the clipboard. (%s)"),
				GetLastErrorString(GetLastError()).c_str());
			ErrorQuit(message.c_str());
		}
		
	}
	count = count <= 0 ? 10 : count;
	const int millisec = count * 1000;
	if (isBalloon)
	{
		tstring strarg = stdFormat(_T("/title:%s /icon:\"%s\" /duration %d /balloonicon:1 \"%s\""),
			APPNAME,
			stdGetModuleFileName<TCHAR>().c_str(),
			millisec,
			Utf8UrlEncode(outmessage).c_str()
		);

		wstring balloonexe = stdCombinePath(
			stdGetParentDirectory(stdGetModuleFileName<TCHAR>()),
			L"showballoon.exe");
		//	L"argCheck.exe");


		HANDLE hProcess = NULL;
		if (!OpenCommon(NULL, balloonexe.c_str(), strarg.c_str(), NULL, &hProcess))
		{
			return 1;
		}

		WaitForSingleObject(hProcess, millisec);
		CloseHandle(hProcess);
	}
	else
	{
		HMODULE hModule = LoadLibrary(L"TimedMessageBox.dll");
		if (!hModule)
			ErrorQuit(L"Failed to load TimedMessageBox.dll");

		FNTimedMessageBox2 func2 = NULL;
		func2 = (FNTimedMessageBox2)GetProcAddress(hModule, "fnTimedMessageBox2");
		if (!func2)
			ErrorQuit(L"Faied GetProcAddress");

		TIMEDMESSAGEBOX_PARAMS tp;
		tp.size = sizeof(tp);
		tp.flags = TIMEDMESSAGEBOX_FLAGS_POSITION | TIMEDMESSAGEBOX_FLAGS_SHOWCMD | TIMEDMESSAGEBOX_FLAGS_TOPMOST;
		tp.hWndCenterParent = NULL;
		tp.position = TIMEDMESSAGEBOX_POSITION_BOTTOMRIGHT;
		tp.nShowCmd = SW_SHOWNOACTIVATE;
		func2(NULL, count, APPNAME, outmessage.c_str(), &tp);
	}
	return 0;
}


