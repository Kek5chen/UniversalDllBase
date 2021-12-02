#include "hack.h"

// hack dll template with basic features created using github copilot

// create a Dll entry point
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // create a new thread to execute the hack::run and pass the hModule
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)hack::run, (LPVOID)hModule, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}