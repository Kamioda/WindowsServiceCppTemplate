#include "ServiceControl.h"
#include "CloseServiceHandles.h"
#include "ServiceInformation.h"
#include "GetErrorMessage.h"
#include <ShlObj.h>
#include <string>
#include <stdexcept>

ServiceControl::ServiceControl() : SCM(NULL), Service(NULL) {
	if (FALSE == IsUserAnAdmin()) throw std::runtime_error("This process must execute as administrators");
	if ((this->SCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) {
		throw std::runtime_error(
			"Failed In OpenSCManager Function\n"
			+ GetErrorMessageA()
		);
	}
}

ServiceControl::~ServiceControl() { CloseServiceHandles(this->Service, this->SCM); }

void ServiceControl::Open() {
	if (this->Service = OpenService(this->SCM, ServiceInfo::Name, SERVICE_ALL_ACCESS); this->Service == NULL) {
		throw std::runtime_error(
			"Failed In OpenService Function\n"
			+ GetErrorMessageA()
		);
	}
}

void ServiceControl::Control(const DWORD dwControl) {
	SERVICE_STATUS SvcStatusInControl{};
	if (FALSE == ControlService(this->Service, dwControl, &SvcStatusInControl)) {
		throw std::runtime_error(
			"Failed In ControlService Function\n"
			+ GetErrorMessageA()
		);
	}
}

void ServiceControl::Install() {
	std::basic_string<TCHAR> ModulePath{};
	ModulePath.reserve(MAX_PATH);
	GetModuleFileName(NULL, &ModulePath[0], MAX_PATH);
	SERVICE_DESCRIPTION ServiceDescription;
	if ((this->Service = CreateService(
		this->SCM,
		ServiceInfo::Name,
		ServiceInfo::DisplayName,
		SERVICE_CHANGE_CONFIG,
		SERVICE_WIN32_OWN_PROCESS,
		ServiceInfo::DelayedStart ? SERVICE_AUTO_START : ServiceInfo::StartType,
		SERVICE_ERROR_NORMAL,
		ModulePath.c_str(),
		NULL,
		NULL,
		NULL,
		ServiceInfo::ExecutionUser,
		NULL
	)) == NULL) {
		throw std::runtime_error(
			"Failed In CreateService Function\n"
			+ GetErrorMessageA()
		);
	}
	ServiceDescription.lpDescription = ServiceInfo::Description;
	if (ServiceInfo::DelayedStart) {
		SERVICE_DELAYED_AUTO_START_INFO info = { TRUE };
		if (FALSE == ChangeServiceConfig2(this->Service, SERVICE_CONFIG_DELAYED_AUTO_START_INFO, &info)) {
			throw std::runtime_error(
				"Failed Set Service Delay Start\n"
				+ GetErrorMessageA()
			);
		}
	}
	if (!ServiceInfo::RequireAdministrator) {
		SERVICE_REQUIRED_PRIVILEGES_INFO PrivilegesInfo = {};
		PrivilegesInfo.pmszRequiredPrivileges = SE_INC_BASE_PRIORITY_NAME _T("\0");
		ChangeServiceConfig2(this->Service, SERVICE_CONFIG_REQUIRED_PRIVILEGES_INFO, &PrivilegesInfo);
	}
	if (FALSE == ChangeServiceConfig2(this->Service, SERVICE_CONFIG_DESCRIPTION, &ServiceDescription)) {
		throw std::runtime_error(
			"Failed Set Service Description\n"
			+ GetErrorMessageA()
		);
	}
}

void ServiceControl::Uninstall() {
	this->Open();
	if (const DWORD dwServiceStatus = this->Show(); dwServiceStatus != SERVICE_STOPPED && dwServiceStatus != SERVICE_STOP_PENDING) this->Stop();
	if (FALSE == DeleteService(this->Service)) {
		throw std::runtime_error(
			"Failed In DeleteService Function\n"
			+ GetErrorMessageA()
		);
	}
}

void ServiceControl::Run(DWORD dwArgc, LPCTSTR lpszArgv[]) {
	this->Open();
	if (StartService(this->Service, dwArgc, lpszArgv)) {
		throw std::runtime_error(
			"Failed In StartService Function\n"
			+ GetErrorMessageA()
		);
	}
}

void ServiceControl::Stop() {
	this->Open();
	this->Control(SERVICE_CONTROL_STOP);
}

void ServiceControl::Pause() {
	this->Open();
	this->Control(SERVICE_CONTROL_PAUSE);
}

void ServiceControl::Continue() {
	this->Open();
	this->Control(SERVICE_CONTROL_CONTINUE);
}

DWORD ServiceControl::Show() {
	SERVICE_STATUS SvcStatusInShow{};
	if (FALSE == QueryServiceStatus(this->Service, &SvcStatusInShow)) {
		throw std::runtime_error(
			"Failed In QueryServiceStatus Function\n"
			+ GetErrorMessageA()
		);
	}
	return SvcStatusInShow.dwCurrentState;
}
