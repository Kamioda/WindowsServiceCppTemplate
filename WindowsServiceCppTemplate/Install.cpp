#include "ServiceInformation.h"
#include "CloseServiceHandles.h"
#include "GetErrorMessage.h"
#include <ShlObj.h>
#include <string>
#include <stdexcept>

void Install() {
	if (FALSE == IsUserAnAdmin()) throw std::runtime_error("This process must execute as administrators");
	std::basic_string<TCHAR> ModulePath{};
	ModulePath.reserve(MAX_PATH);
	GetModuleFileName(NULL, &ModulePath[0], MAX_PATH);
	SC_HANDLE Service = NULL, scm = NULL;
	SERVICE_DESCRIPTION ServiceDescription;
	if ((scm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE)) == NULL) {
		CloseServiceHandles(Service, scm);
		throw std::runtime_error(
			"Failed In OpenSCManager Function\n"
			+ GetErrorMessageA()
		);
	}
	if ((Service = CreateService(
		scm,
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
		CloseServiceHandles(Service, scm);
		throw std::runtime_error(
			"Failed In CreateService Function\n"
			+ GetErrorMessageA()
		);
	}
	ServiceDescription.lpDescription = ServiceInfo::Description;
	if (ServiceInfo::DelayedStart) {
		SERVICE_DELAYED_AUTO_START_INFO info = { TRUE };
		if (FALSE == ChangeServiceConfig2(Service, SERVICE_CONFIG_DELAYED_AUTO_START_INFO, &info)) {
			CloseServiceHandles(Service, scm);
			throw std::runtime_error(
				"Failed Set Service Delay Start\n"
				+ GetErrorMessageA()
			);
		}
	}
	if (!ServiceInfo::RequireAdministrator) {
		SERVICE_REQUIRED_PRIVILEGES_INFO PrivilegesInfo = {};
		PrivilegesInfo.pmszRequiredPrivileges = SE_INC_BASE_PRIORITY_NAME _T("\0");
		ChangeServiceConfig2(Service, SERVICE_CONFIG_REQUIRED_PRIVILEGES_INFO, &PrivilegesInfo);
	}
	if (FALSE == ChangeServiceConfig2(Service, SERVICE_CONFIG_DESCRIPTION, &ServiceDescription)) {
		CloseServiceHandles(Service, scm);
		throw std::runtime_error(
			"Failed Set Service Description\n"
			+ GetErrorMessageA()
		);
	}
	CloseServiceHandles(Service, scm);
}
