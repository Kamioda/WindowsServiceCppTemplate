#pragma once
#include <Windows.h>
#include <string>

class ServiceController {
protected:
	std::string ServiceName;
	SC_HANDLE SCM;
	SC_HANDLE Service;
	SERVICE_STATUS Status;
	void Open();
	void Control(const DWORD dwControl);
public:
	ServiceController(const std::string& ServiceName, const bool OpenServiceInConstructor = true);
	~ServiceController();
	void Run(DWORD dwArgc = 0, LPCTSTR lpszArgv[] = nullptr);
	void Stop();
	void Pause();
	void Continue();
	DWORD Show() const noexcept;
	void Update();
};
