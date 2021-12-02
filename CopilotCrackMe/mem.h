#pragma once
#include <Windows.h>
#include <vector>

namespace mem {
    uintptr_t resolvePointer(std::vector<uintptr_t> offsets, uintptr_t base);
    uintptr_t patternScan(const char* module, const char* signature);
}