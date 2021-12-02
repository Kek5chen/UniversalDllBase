#include "hack.h"

#include <psapi.h>
#include <string>
#include <sstream>

HMODULE _dllModule;

// create a console use freopen_s to add input and output to the console
void hack::attachConsole() {
    AllocConsole();
    // a string using hack::HACK_NAME and hack::HACK_VERSION in format "HACK_NAME vHACK_VERSION by HACK_AUTHOR" using stringstream
    std::stringstream ss;
    ss << HACK_NAME << " v" << HACK_VERSION << " by " << HACK_AUTHOR;
    // set the console title
    SetConsoleTitleA(ss.str().c_str());
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
}
void hack::log(const char* format, ...) {
    // print the format with the prefix "LOG: %text%\n"
    printf("LOG: ");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
}
void hack::error(const char* format, ...) {
    // print the format with the prefix "ERROR: "
    printf("ERROR: ");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void hack::run(HMODULE dllModule) {
    attachConsole();
    // print out that the dll is loaded
    log("DLL loaded");

    // resolve the programs main module base and put it in hack::module_base
    module_base = (uintptr_t)GetModuleHandle(NULL);
    // print out the module base
    log("Module base: %p", module_base);
    
    // resolve the programs main module size and put it in hack::module_size
    MODULEINFO moduleInfo;
    GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &moduleInfo, sizeof(moduleInfo));
    module_size = moduleInfo.SizeOfImage;
    // print out the module size
    log("Module size: %p", module_size);
    
    // resolve the programs main module size and put it in hack::module_end
    module_end = module_base + module_size;
    // print out the module end
    log("Module end: %p", module_end);

    // loop until the user presses VK_END
    while(!GetAsyncKeyState(VK_END));   

    // free console window
    FreeConsole();

    // unload the dll using dllModule
    FreeLibrary(dllModule);
}