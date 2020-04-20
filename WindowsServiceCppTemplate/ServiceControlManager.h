#pragma once
#include "HandleManager.h"
#include <Windows.h>

class ServiceControlManager {
private:
	HandleManager<SC_HANDLE> SCM;
public:
	ServiceControlManager();
	operator const SC_HANDLE& () const noexcept;
};
