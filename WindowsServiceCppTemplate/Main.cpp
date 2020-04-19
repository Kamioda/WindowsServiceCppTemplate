#include "ServiceInformation.h"
#include "ServiceMainProcess.h"
#include "ConsoleMainProcess.h"
#include "GetErrorMessage.h"
#include <stdexcept>
SERVICE_STATUS SvcStatus;
SERVICE_STATUS_HANDLE SvcStatusHandle;
bool SetServiceStatusInfoImpl() noexcept { 
#if defined(_DEBUG) && defined(CONSOLE)
	return true;
#else
	return FALSE != SetServiceStatus(SvcStatusHandle, &SvcStatus);
#endif
}
void SetServiceStatusInfo() noexcept { SetServiceStatusInfoImpl(); }
void SetServiceStatusInfoE() noexcept(false) { if (!SetServiceStatusInfoImpl()) throw std::runtime_error("Failed to set service status\n" + GetErrorMessageA()); }
void Main_ServiceDispatcher();
std::vector<std::basic_string<TCHAR>> GetServiceCommandLineArgs(DWORD dwArgc, LPTSTR lpszArgv[]) {
	if (dwArgc == 1) return std::vector<std::basic_string<TCHAR>>{};
	std::vector<std::basic_string<TCHAR>> Args{};
	for (DWORD i = 1; i < dwArgc; i++) Args.emplace_back(std::basic_string<TCHAR>(lpszArgv[i]));
	return Args;
}

DWORD WINAPI HandlerEx(DWORD dwControl, DWORD, LPVOID, LPVOID) {
	switch (dwControl) {
		case SERVICE_CONTROL_SHUTDOWN:
		case SERVICE_CONTROL_STOP:
			SvcStatus.dwCurrentState = SERVICE_STOP_PENDING;
			break;
		case SERVICE_CONTROL_PAUSE:
			SvcStatus.dwCurrentState = SERVICE_PAUSE_PENDING;
			break;
		case SERVICE_CONTROL_CONTINUE:
			SvcStatus.dwCurrentState = SERVICE_CONTINUE_PENDING;
			break;
		default:
			break;
	}
	SetServiceStatusInfo();
	return NO_ERROR;
}

void WINAPI ServiceMain(DWORD dwArgc, LPTSTR lpszArgv[]) {
	try {
#if !defined(_DEBUG) || !defined(CONSOLE)
		SvcStatusHandle = RegisterServiceCtrlHandlerEx(lpszArgv[0], HandlerEx, NULL);
#endif
		memset(&SvcStatus, 0, sizeof(SvcStatus));
		ServiceProcess* SvcProcess = GetServiceProcessInstance(Service_CommandLineManager::GetCommandLineArg(GetServiceCommandLineArgs(dwArgc, lpszArgv)));
		SvcProcess->Service_MainProcess();
	}
	catch (...) {}
	if (SvcStatus.dwCurrentState != SERVICE_STOPPED) SvcStatus.dwCurrentState = SERVICE_STOPPED;
	SetServiceStatusInfo();
}
#if defined(_DEBUG) && defined(CONSOLE)
#ifdef UNICODE
int wmain(int argc, wchar_t* argv[]) {
	ServiceMain(static_cast<DWORD>(argc), argv);
	return 0;
}
#else
int main(int argc, char* argv[]) {
	ServiceMain(static_cast<DWORD>(argc), argv);
	return 0;
}
#endif
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int CmdShow) {
	std::strlen(lpCmdLine) == 0 ? Main_ServiceDispatcher() : Console_MainProcess(hInstance, Console_CommandLineManager::GetCommandLineArg(lpCmdLine), CmdShow);
	return 0;
}

void Main_ServiceDispatcher() {
	SERVICE_TABLE_ENTRY SvcTable[] = {
		{ ServiceInfo::Name, ServiceMain },
		{ NULL, NULL }
	};
	StartServiceCtrlDispatcher(SvcTable);
}
#endif