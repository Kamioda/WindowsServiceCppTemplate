#include "ServiceInformation.h"
#include "CloseServiceHandles.h"
#include "GetErrorMessage.h"
#include <ShlObj.h>
#include <stdexcept>

void Uninstall() {
	if (FALSE == IsUserAnAdmin()) throw std::runtime_error("This process must execute as administrators");
	SC_HANDLE scm = NULL, Service = NULL;
	if ((scm = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT)) == NULL) {
		CloseServiceHandles(Service, scm);
		throw std::runtime_error(
			"Failed In OpenSCManager Function\n"
			+ GetErrorMessageA()
		);
	}
	if ((Service = OpenService(scm, ServiceInfo::Name, DELETE)) == NULL) {
		CloseServiceHandles(Service, scm);
		throw std::runtime_error(
			"Failed In OpenService Function\n"
			+ GetErrorMessageA()
		);
	}
	if (FALSE == DeleteService(Service)) {
		CloseServiceHandles(Service, scm);
		throw std::runtime_error(
			"Failed In DeleteService Function\n"
			+ GetErrorMessageA()
		);
	}
	CloseServiceHandles(Service, scm);
}