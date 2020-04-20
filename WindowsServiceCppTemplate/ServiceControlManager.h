#pragma once
#include <Windows.h>

class ServiceControlManager {
private:
	SC_HANDLE SCM;
public:
	ServiceControlManager();
	~ServiceControlManager();
	operator const SC_HANDLE& () const noexcept;
};
