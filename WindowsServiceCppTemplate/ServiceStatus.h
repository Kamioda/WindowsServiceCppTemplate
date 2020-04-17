#pragma once
#include <Windows.h>
extern SERVICE_STATUS SvcStatus;
extern SERVICE_STATUS_HANDLE SvcStatusHandle;
void SetServiceStatusInfo() noexcept;
void SetServiceStatusInfoE() noexcept(false);
