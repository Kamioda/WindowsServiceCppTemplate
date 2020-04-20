#pragma once
#include "ServiceControlManager.h"
#include <string>
#include <functional>

class ServiceController {
protected:
	std::reference_wrapper<ServiceControlManager> SCM;
	std::string ServiceName;
	SC_HANDLE Service;
	SERVICE_STATUS Status;
	void Open();
	void Control(const DWORD dwControl);
public:
	ServiceController(ServiceControlManager& SvcCtrlMgr, const std::string& ServiceName, const bool OpenServiceInConstructor = true);
	~ServiceController();
	void Run(DWORD dwArgc = 0, LPCTSTR lpszArgv[] = nullptr);
	void Stop();
	void Pause();
	void Continue();
	DWORD Show() const noexcept;
	void Update();
};
