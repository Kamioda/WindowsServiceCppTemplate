#pragma once
#include <Windows.h>
#include <string>
#include <stdexcept>

inline std::string GetErrorMessageA() {
	char* lpMessageBuffer = nullptr;
	const DWORD code = GetLastError();
	const DWORD length = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, code, LANG_USER_DEFAULT, (LPSTR)&lpMessageBuffer, 0, NULL);
	if (length == 0) throw std::runtime_error("エラーメッセージ取得時にエラーが発生しました。\nエラーコード : " + std::to_string(GetLastError()));
	DWORD i = length - 3;
	for (; '\r' != lpMessageBuffer[i] && '\n' != lpMessageBuffer[i] && '\0' != lpMessageBuffer[i]; i++);//改行文字削除
	lpMessageBuffer[i] = '\0';
	std::string s = "エラーコード : " + std::to_string(code) + "　" + lpMessageBuffer;
	LocalFree(lpMessageBuffer);
	return s;
}
