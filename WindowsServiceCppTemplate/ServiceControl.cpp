#include "ServiceControl.h"
#include "CommandLineManager.h"
#include "ServiceInformation.h"
#include "GetErrorMessage.h"
#include <ShlObj.h>
#include <string>
#include <stdexcept>

ServiceControl::ServiceControl(ServiceControlManager& SCManager) : ServiceController(SCManager, CommandLineManagerA::AlignCmdLineStrType(ServiceInfo::Name), false) {}

void ServiceControl::Install() {
	std::basic_string<TCHAR> ModulePath{};
	ModulePath.reserve(MAX_PATH);
	GetModuleFileName(NULL, &ModulePath[0], MAX_PATH);
	SERVICE_DESCRIPTION ServiceDescription;
	if (ServiceController::Service = HandleManager<SC_HANDLE>(
		CreateService(this->SCM.get(), ServiceInfo::Name, ServiceInfo::DisplayName, SERVICE_CHANGE_CONFIG,
			SERVICE_WIN32_OWN_PROCESS, ServiceInfo::DelayedStart ? SERVICE_AUTO_START : ServiceInfo::StartType,	SERVICE_ERROR_NORMAL,
			ModulePath.c_str(),	NULL, NULL,	NULL, ServiceInfo::ExecutionUser, NULL
			),
			[](SC_HANDLE& handle) { CloseServiceHandle(handle); }
		); ServiceController::Service == nullptr) {
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
	ServiceController::Open();
	if (const DWORD dwServiceStatus = this->Show(); dwServiceStatus != SERVICE_STOPPED && dwServiceStatus != SERVICE_STOP_PENDING) this->Stop();
	if (FALSE == DeleteService(this->Service)) {
		throw std::runtime_error(
			"Failed In DeleteService Function\n"
			+ GetErrorMessageA()
		);
	}
}

void ServiceControl::Run(DWORD dwArgc, LPCTSTR lpszArgv[]) {
	ServiceController::Run(dwArgc, lpszArgv);
}

void ServiceControl::Stop() {
	ServiceController::Stop();
}

void ServiceControl::Pause() {
	ServiceController::Pause();
}

void ServiceControl::Continue() {
	ServiceController::Continue();
}

DWORD ServiceControl::Show() {
	return ServiceController::Show();
}
