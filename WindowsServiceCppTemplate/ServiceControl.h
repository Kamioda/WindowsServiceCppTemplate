#pragma once
#include <Windows.h>

class ServiceControl {
private:
	SC_HANDLE SCM;
	SC_HANDLE Service;
	void Open();
	void Control(const DWORD dwControl);
public:
	ServiceControl();
	~ServiceControl();
	void Install();
	void Uninstall();
	void Run(DWORD dwArgc = 0, LPCTSTR lpszArgv[] = nullptr);
	void Stop();
	void Pause();
	void Continue();
	DWORD Show();
};
