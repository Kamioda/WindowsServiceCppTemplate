#include "ConsoleMainProcess.h"
#include "Install.h"
#include "Uninstall.h"
#include <Windows.h>
#include <string>
#include <vector>

void Console_MainProcess(HINSTANCE hInstance, const Console_CommandLineManager::CommandLineType& CommandLines, int nCmdShow) {
	if (CommandLines.at(0) == Console_CommandLineManager::AlignCmdLineStrType("install")) Install();
	else if (CommandLines.at(0) == Console_CommandLineManager::AlignCmdLineStrType("uninstall")) Uninstall();
	else {
		// ここに他のコマンドライン引数が与えられた時の処理を書く

	}
}
