#include "Console.h"
#include <Windows.h>
#include <iostream>
#include <stdlib.h>

Console::Console() : fp(nullptr) {
	if (FALSE == AttachConsole(ATTACH_PARENT_PROCESS)) AllocConsole();
	freopen_s(&this->fp, "CONOUT$", "w", stdout);
	freopen_s(&this->fp, "CONOUT$", "w", stderr);
}

Console::~Console() {
	fclose(this->fp);
	FreeConsole();
}

void Console::WriteLine(const std::string& data, const bool Pause) const {
	std::cout << data << std::endl;
	if (Pause) system("pause");
};
