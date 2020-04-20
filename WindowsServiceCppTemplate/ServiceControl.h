#pragma once
#include "ServiceController.h"

class ServiceControl : private ServiceController {
public:
	ServiceControl(ServiceControlManager& SCManager);
	void Install();
	void Uninstall();
	void Run(DWORD dwArgc = 0, LPCTSTR lpszArgv[] = nullptr);
	void Stop();
	void Pause();
	void Continue();
	DWORD Show();
};
