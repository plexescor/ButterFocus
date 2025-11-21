#include <iostream>
#include <Windows.h>
#include "Headers/GetCurrentWindow.hpp"

//-------------------------------------------------------
// WINDOWS IMPLEMENTATION
//-------------------------------------------------------

std::string getCurrentWindow()
{
    HWND currWindow = GetForegroundWindow(); // Get the currently focused window
    if (!currWindow) return "[No Foreground Window]"; // nothing is focused

    DWORD pid = 0;
    GetWindowThreadProcessId(currWindow, &pid); // get PID of focused window
    if (pid == 0) return "[No PID]";            // weird, should not happen, at least thats what i think

    // Open the process with minimal permission
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProcess) return "[Access Denied]";   // cannot open, maybe system/UWP app(idk how to monitor those)

    char fullPath[MAX_PATH] = {0};             // zero out buffer to avoid garbage
    DWORD size = MAX_PATH;

    // Query full executable path safely
    if (QueryFullProcessImageNameA(hProcess, 0, fullPath, &size) == 0)
    {
        CloseHandle(hProcess);
        return "[Query Failed]";               // UWP / sandboxed apps often fail here
    }

    CloseHandle(hProcess);                      // always close handle otherwise boom baby

    std::string pathStr(fullPath);              // convert C string to std::string, for conveinience
    size_t pos = pathStr.find_last_of("\\/");   // find last folder separator
    std::string exeName = (pos != std::string::npos) ? pathStr.substr(pos + 1) : pathStr;

    size_t dotPos = exeName.find_last_of("."); //Find last dot occurence
    std::string baseName = (dotPos != std::string::npos) ? exeName.substr(0, dotPos) : exeName; //Assign to baseName, everything before the dot
    return baseName;
}
