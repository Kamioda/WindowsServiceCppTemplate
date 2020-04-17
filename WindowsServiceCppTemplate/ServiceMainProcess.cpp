#include "ServiceStatus.h"
#include "ServiceMainProcess.h"
#include <tchar.h>
#include <filesystem>

std::basic_string<TCHAR> GetModuleFileDirectory() {
	TCHAR Buffer[MAX_PATH];
	if (ERROR_SUCCESS != GetModuleFileName(NULL, Buffer, MAX_PATH)) return std::basic_string<TCHAR>{};
	const std::basic_string<TCHAR> path = std::basic_string<TCHAR>(Buffer);
	const std::filesystem::path modulepath(path);
#ifdef UNICODE
	return modulepath.parent_path().wstring() + L"\\";
#else
	return modulepath.parent_path().string() + "\\";
#endif
}

ServiceProcess::ServiceProcess(const Service_CommandLineManager::CommandLineType& args, const bool CurrentDirectoryIsModulePath)
	: Argv(args), ModuleFileDirectory(Service_CommandLineManager::AlignCmdLineStrType(GetModuleFileDirectory())) { 
	if (const auto ModuleDirectory = GetModuleFileDirectory(); 
		CurrentDirectoryIsModulePath && !ModuleDirectory.empty()) std::filesystem::current_path(ModuleDirectory);
	SvcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	SvcStatus.dwCurrentState = SERVICE_START_PENDING;
	SvcStatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_STOP;
	SvcStatus.dwWin32ExitCode = NO_ERROR;
	SvcStatus.dwServiceSpecificExitCode = 0;
	SvcStatus.dwCheckPoint = 0;
	SvcStatus.dwWaitHint = 2000;
	SetServiceStatusInfo();
}

Service_CommandLineManager::CommandLineStringType ServiceProcess::ChangeFullPath(const Service_CommandLineManager::CommandLineStringType& Path) {
	return Service_CommandLineManager::AlignCmdLineStrType(":") == Path.substr(1, 1) ? Path : this->ModuleFileDirectory + Path;
}