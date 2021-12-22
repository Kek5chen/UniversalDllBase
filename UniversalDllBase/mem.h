#pragma once
#include <Windows.h>
#include <vector>

namespace mem {
    uintptr_t resolvePointer(std::vector<uintptr_t> offsets, uintptr_t base);
    uintptr_t FindPatternEx(const uintptr_t& pStartAddr, const uintptr_t& pEndAddr, const char* szTPattern);
    uintptr_t FindPattern(const char* szModule, const char* szPattern);
    HWND GetWindowHandle(const char* windowName);
}
