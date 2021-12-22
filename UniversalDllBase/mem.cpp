#pragma warning(disable : 6387)

#include "mem.h"
#include "hack.h"

#include <psapi.h>

uintptr_t mem::resolvePointer(std::vector<uintptr_t> offsets, uintptr_t base) {
	uintptr_t ptr = base;
	for (uintptr_t offset : offsets) {
		ptr = *(uintptr_t*)ptr + offset;
	}
	return ptr;
}

#define InRange(x, a, b) (x >= a && x <= b) 
#define GetBits(x) (InRange((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xA): (InRange(x, '0', '9') ? x - '0': 0))
#define GetByte(x) (GetBits(x[0]) << 4 | GetBits(x[1]))

uintptr_t mem::FindPatternEx(const uintptr_t& pStartAddr, const uintptr_t& pEndAddr, const char* szTPattern) {
	const char* szPattern = szTPattern;
	uintptr_t pFirstMatch = NULL;

	for (uintptr_t pPosition = pStartAddr; pPosition < pEndAddr; pPosition++) {
		if (!*szPattern) return pFirstMatch;
		const uint8_t pCurrentPattern = *reinterpret_cast<const uint8_t*>(szPattern);
		const uint8_t pCurrentMemory = *reinterpret_cast<const uint8_t*>(pPosition);

		if (pCurrentPattern == '\?' || pCurrentMemory == GetByte(szPattern)) {
			if (!pFirstMatch) pFirstMatch = pPosition;
			if (!szPattern[2]) return pFirstMatch;
			szPattern += pCurrentPattern != '\?' ? 3 : 2;
		}
		else {
			szPattern = szTPattern;
			pFirstMatch = NULL;
		}
	}
	return NULL;
}

uintptr_t mem::FindPattern(const char* szModule, const char* szPattern) {
	MODULEINFO hModInfo = { nullptr };
	if (!K32GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &hModInfo, sizeof(hModInfo))) return NULL;
	const uintptr_t pStartAddr = (uintptr_t)hModInfo.lpBaseOfDll;
	const uintptr_t pEndAddr = pStartAddr + hModInfo.SizeOfImage;
	return FindPatternEx(pStartAddr, pEndAddr, szPattern);
}

HWND mem::GetWindowHandle(const char* windowName) {
	return FindWindowA(NULL, windowName);
}
