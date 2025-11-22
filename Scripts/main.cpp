#include <iostream>
#include <thread>
#include <future>
#include <chrono>

#include "WindowTrackerAndShit/Headers/GetCurrentWindow.hpp"

// Conditional compilation for Windows-specific code
#ifdef _WIN32

    int main()
    {
        std::string currentWindow;
        std::string previousWindow;
        int switches = -1;

        while (true)
        {
            currentWindow = getCurrentWindow();
            if (previousWindow == currentWindow)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                continue;
            }
            if (currentWindow != "" 
                && currentWindow != "SearchApp"
                && currentWindow != "explorer"

               )
            {
                previousWindow = currentWindow;
                switches++;
                std::cout<<currentWindow << std::endl;
                std::cout.flush();
                std::cout<<"Swicthes: "<<switches<< std::endl;
                std::cout.flush();
                previousWindow = currentWindow;
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
            std::cout.flush();
        }
    }

    
#endif