#include "mem.h"
#include <psapi.h>

uintptr_t mem::resolvePointer(std::vector<uintptr_t> offsets, uintptr_t base) {
    uintptr_t ptr = base;
    for (uintptr_t offset : offsets) {
        ptr = *(uintptr_t*)ptr + offset;
    }
    return ptr;
}

uintptr_t mem::patternScan(const char* module, const char* signature) {
    MODULEINFO modInfo;
    GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(module), &modInfo, sizeof(MODULEINFO));
    uintptr_t start = (uintptr_t)modInfo.lpBaseOfDll;
    uintptr_t end = start + modInfo.SizeOfImage;
    const char* pat = signature;
    const char* pat_end = pat + strlen(signature);
    for (uintptr_t pCur = start; pCur < end; pCur++) {
        if (!*pat)
            return pCur;
        if (*(BYTE*)pCur == *(BYTE*)pat)
            pat = pat_end;
        else
            pat = signature;
    }
    return 0;
}