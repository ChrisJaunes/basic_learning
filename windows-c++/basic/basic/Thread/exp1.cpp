/*
* designed a exp about process
* help url : https://baike.baidu.com/item/CreateProcess/11050419?fr=aladdin
* @author ChrisJaunes
*/
#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include"thread.h"
namespace CJ_Thread {
	void exp1() {
		STARTUPINFO si;
		memset(&si, 0, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOW;
		PROCESS_INFORMATION pi;
		if (!CreateProcess(TEXT("c:\\windows\\system32\\notepad.exe"),
			NULL,
			NULL,
			NULL,
			FALSE,
			CREATE_NO_WINDOW,
			NULL,
			NULL,
			&si,
			&pi
		)) {
			std::cout << "CreateFail!" << std::endl;
			exit(1);
		}
		else {
			std::cout << "Success!" << std::endl;
		}
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
}