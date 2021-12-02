#pragma once

#include <Windows.h>
#include <stdio.h>

namespace hack {
    static const char* const HACK_NAME = "HackBase";
    static int HACK_VERSION = 1;
    static const char* const HACK_AUTHOR = "kek5chen";
    static uintptr_t module_base = 0;
    static uintptr_t module_size = 0;
    static uintptr_t module_end = 0;
    
    void attachConsole();
    void log(const char* format, ...);
    void error(const char* format, ...);
    void run(HMODULE dllModule);
}