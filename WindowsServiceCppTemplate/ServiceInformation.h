#pragma once
#include <Windows.h>
#include <tchar.h>

namespace ServiceInfo {
	constexpr const TCHAR* Name = _T("");
	constexpr const TCHAR* DisplayName = _T("");
	constexpr const TCHAR* Description = _T("");
	constexpr DWORD StartType = SERVICE_AUTO_START;
	constexpr bool DelayedStart = true;
	// LocalSystem    : NULL
	// LocalService   : NT AUTHORITY\\LocalService
	// NetworkService : NT AUTHORITY\\NetworkService
	constexpr const TCHAR* ExecutionUser = NULL;
	constexpr bool RequireAdministrator = true;
}