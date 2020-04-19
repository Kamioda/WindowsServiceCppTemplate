#include "Console.h"
#include <iostream>
#include <stdlib.h>

Console::Console() : fp(nullptr) {
	AllocConsole();
	freopen_s(&this->fp, "CONOUT$", "w", stdout);
	freopen_s(&this->fp, "CONOUT$", "w", stderr);
	this->hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
}

Console::~Console() {
	fclose(this->fp);
	FreeConsole();
}

DWORD Console::Write(const std::string& str, const bool Pause) const {
	DWORD dwWriteByte{};
	WriteConsoleA(this->hStdOutput, str.c_str(), lstrlenA(str.c_str()), &dwWriteByte, NULL);
	if (Pause) system("pause");
	return dwWriteByte;
};

DWORD Console::WriteLine(const std::string& str, const bool Pause) const {
	return this->Write(str + "\n", Pause);
}
