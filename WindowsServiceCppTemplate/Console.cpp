#include "Console.h"
#include <Windows.h>
#include <iostream>
#include <stdlib.h>

Console::Console() : fp(nullptr) {
	if (FALSE == AttachConsole(ATTACH_PARENT_PROCESS)) {
		AllocConsole();
		freopen_s(&this->fp, "CONOUT$", "w", stdout); /* 標準出力(stdout)を新しいコンソールに向ける */
		freopen_s(&this->fp, "CONOUT$", "w", stderr); /* 標準エラー出力(stderr)を新しいコンソールに向ける */
	}
}

Console::~Console() {
	fclose(this->fp);
	FreeConsole();
}

void Console::WriteLine(const std::string& data, const bool Pause) const {
	std::cout << data << std::endl;
	if (Pause) system("pause");
};
