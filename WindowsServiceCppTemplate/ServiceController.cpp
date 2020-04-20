#include "ServiceController.h"
#include "GetErrorMessage.h"
#include <ShlObj.h>
#include <stdexcept>

ServiceController::ServiceController(const std::string& ServiceName, const bool OpenServiceInConstructor)
	: ServiceName(ServiceName), SCM(NULL), Service(NULL), Status() {
	if (FALSE == IsUserAnAdmin()) throw std::runtime_error("This process must execute as administrators");
	if ((this->SCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) {
		throw std::runtime_error(
			"Failed In OpenSCManager Function\n"
			+ GetErrorMessageA()
		);
	}
	if (OpenServiceInConstructor) this->Open();
}

ServiceController::~ServiceController() {
	CloseServiceHandle(this->Service);
	CloseServiceHandle(this->SCM);
}

void ServiceController::Open() {
	if (this->Service != NULL) return;
	if (this->Service = OpenServiceA(this->SCM, this->ServiceName.c_str(), SERVICE_ALL_ACCESS); this->Service == NULL) {
		throw std::runtime_error(
			"Failed In OpenService Function\n"
			+ GetErrorMessageA()
		);
	}
}

void ServiceController::Control(const DWORD dwControl) {
	if (FALSE == ControlService(this->Service, dwControl, &this->Status)) {
		throw std::runtime_error(
			"Failed In ControlService Function\n"
			+ GetErrorMessageA()
		);
	}
}

void ServiceController::Run(DWORD dwArgc, LPCTSTR lpszArgv[]) {
	this->Open();
	if (FALSE == StartService(this->Service, dwArgc, lpszArgv)) {
		throw std::runtime_error(
			"Failed In StartService Function\n"
			+ GetErrorMessageA()
		);
	}
}

void ServiceController::Stop() {
	this->Open();
	this->Control(SERVICE_CONTROL_STOP);
}

void ServiceController::Pause() {
	this->Open();
	this->Control(SERVICE_CONTROL_PAUSE);
}

void ServiceController::Continue() {
	this->Open();
	this->Control(SERVICE_CONTROL_CONTINUE);
}

DWORD ServiceController::Show() {
	this->Open();
	if (FALSE == QueryServiceStatus(this->Service, &this->Status)) {
		throw std::runtime_error(
			"Failed In QueryServiceStatus Function\n"
			+ GetErrorMessageA()
		);
	}
	return this->Status.dwCurrentState;
}
