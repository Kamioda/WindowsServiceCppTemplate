#include "ServiceControlManager.h"
#include "GetErrorMessage.h"
#include <stdexcept>

ServiceControlManager::ServiceControlManager() {
	if ((this->SCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) {
		throw std::runtime_error(
			"Failed In OpenSCManager Function\n"
			+ GetErrorMessageA()
		);
	}
}

ServiceControlManager::~ServiceControlManager() { CloseServiceHandle(this->SCM); }

ServiceControlManager::operator const SC_HANDLE& () const noexcept { return this->SCM; }

