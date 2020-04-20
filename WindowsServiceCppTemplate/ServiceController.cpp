#include "ServiceController.h"
#include "GetErrorMessage.h"
#include <ShlObj.h>
#include <stdexcept>

ServiceController::ServiceController(ServiceControlManager& SvcCtrlMgr, const std::string& ServiceName, const bool OpenServiceInConstructor)
	: SCM(SvcCtrlMgr), ServiceName(ServiceName), Service(NULL), Status() {
	if (OpenServiceInConstructor) this->Open();
}

ServiceController::~ServiceController() {
	CloseServiceHandle(this->Service);
	CloseServiceHandle(this->SCM.get());
}

void ServiceController::Open() {
	if (this->Service != NULL) return;
	if (this->Service = OpenServiceA(this->SCM.get(), this->ServiceName.c_str(), SERVICE_ALL_ACCESS); this->Service == NULL) {
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

DWORD ServiceController::Show() const noexcept { return this->Status.dwCurrentState; }

void ServiceController::Update() {
	this->Open();
	if (FALSE == QueryServiceStatus(this->Service, &this->Status)) {
		throw std::runtime_error(
			"Failed In QueryServiceStatus Function\n"
			+ GetErrorMessageA()
		);
	}
}
