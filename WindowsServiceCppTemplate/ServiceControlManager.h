#pragma once
#include "HandleManager.h"
#include <Windows.h>

class ServiceControlManager {
private:
	windows::ServiceHandle SCM;
public:
	ServiceControlManager();
	operator const SC_HANDLE& () const noexcept;
};
