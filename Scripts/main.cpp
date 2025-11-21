#include <iostream>
#include <chrono>
#include <thread>
#include "WindowTrackerAndShit/Headers/GetCurrentWindow.hpp"

int main()
{
    std::string temp = "";       // previous window
    std::string currentWindow;
    int windowSwitches = -1;      // counter, STRICTLY START AT -1

    std::cout << "Tracking active windows. Press Ctrl+C to stop.\n";

    while (true)
    {
        currentWindow = getCurrentWindow();     // get current exe name

        if (currentWindow == temp)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;                          // no change, skip
        }

        temp = currentWindow;

        if (!currentWindow.empty())  
        {
            std::cout << currentWindow << "\n";        // print exe name
            windowSwitches++;
            std::cout << "Switches: " << windowSwitches << "\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
