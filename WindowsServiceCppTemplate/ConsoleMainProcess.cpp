#include "ConsoleMainProcess.h"
#include "ServiceControl.h"
#include "Console.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

inline std::string GetServiceStatusString(const DWORD dwCurrentState) {
	switch (dwCurrentState) {
		case SERVICE_RUNNING:
			return "Service is running";
		case SERVICE_PAUSED:
			return "Service is paused";
		case SERVICE_STOPPED:
			return "Service is stopped";
		case SERVICE_START_PENDING:
			return "Service is preparing to start";
		case SERVICE_STOP_PENDING:
			return "Service is preparing to stop";
		case SERVICE_PAUSE_PENDING:
			return "Service is preparing to pause";
		case SERVICE_CONTINUE_PENDING:
			return "Service is preparing to continue";
		default:
			return "Current status code is " + std::to_string(dwCurrentState);
	}
}

void Console_MainProcess(HINSTANCE hInstance, const Console_CommandLineManager::CommandLineType& CommandLines, int nCmdShow) {
	const Console_CommandLineManager::CommandLineType ReservedArgs = { "install", "uninstall", "run", "stop", "pause", "continue", "show" };
	Console console{};
	try {
		if (std::find(ReservedArgs.begin(), ReservedArgs.end(), CommandLines.at(0)) != ReservedArgs.end()) {
			ServiceControl SvcCtrl{};
			if (CommandLines.at(0) == Console_CommandLineManager::AlignCmdLineStrType("install")) SvcCtrl.Install();
			else if (CommandLines.at(0) == Console_CommandLineManager::AlignCmdLineStrType("uninstall")) SvcCtrl.Uninstall();
			else if (CommandLines.at(0) == Console_CommandLineManager::AlignCmdLineStrType("run")) SvcCtrl.Run();
			else if (CommandLines.at(0) == Console_CommandLineManager::AlignCmdLineStrType("stop")) SvcCtrl.Stop();
			else if (CommandLines.at(0) == Console_CommandLineManager::AlignCmdLineStrType("pause")) SvcCtrl.Pause();
			else if (CommandLines.at(0) == Console_CommandLineManager::AlignCmdLineStrType("continue")) SvcCtrl.Pause();
			else {
				const DWORD dwServiceStatus = SvcCtrl.Show();
				console.WriteLine(GetServiceStatusString(dwServiceStatus), true);
			}
			if (CommandLines.at(0) != Console_CommandLineManager::AlignCmdLineStrType("show")) console.WriteLine("Succeed!", true);
		}
		else {
			// ここに他のコマンドライン引数が与えられた時の処理を書く

		}
	}
	catch (const std::exception& er) {
		console.WriteLine(er.what(), true);
	}
}
