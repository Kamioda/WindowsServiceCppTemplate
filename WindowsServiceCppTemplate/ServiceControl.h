#pragma once
#include "ServiceController.h"

class ServiceControl : private ServiceController {
private:
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
