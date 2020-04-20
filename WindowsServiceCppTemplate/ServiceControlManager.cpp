#include "ServiceControlManager.h"
#include "GetErrorMessage.h"
#include <stdexcept>

ServiceControlManager::ServiceControlManager() 
	: SCM(
		OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS),
		[](SC_HANDLE& handle) { CloseServiceHandle(handle); }
	) {
	if (this->SCM == nullptr) {
		throw std::runtime_error(
			"Failed In OpenSCManager Function\n"
			+ GetErrorMessageA()
		);
	}
}

ServiceControlManager::operator const SC_HANDLE& () const noexcept { return this->SCM; }

