#pragma once
#include <Windows.h>

inline void CloseServiceHandles(SC_HANDLE& Service, SC_HANDLE& scm) {
	CloseServiceHandle(Service);
	CloseServiceHandle(scm);
}
