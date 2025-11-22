#include <iostream>
#include <thread>
#include <future>
#include <chrono>

#include "WindowTrackerAndShit/Headers/GetCurrentWindow.hpp"

// int main()
// {
//     std::string prevWindow = "";
//     std::string currentWindow;
//     int windowSwitches = -1; //KEEP IT AT -1, 0 CAUSES INCORRECT READING

//     std::cout << "Tracking active windows. Press Ctrl+C to stop.\n";

//     while (true)
//     {
//         currentWindow = getCurrentWindow();

//         // skip if no change or empty
        // if (currentWindow.empty() || currentWindow == prevWindow)
        // {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(200));
        //     continue;
        // }

        // prevWindow = currentWindow;

        // // filter common system/UWP apps
        // if (currentWindow != "StartMenuExperienceHost" &&
        //     currentWindow != "SearchApp" &&
        //     currentWindow != "ApplicationFrameHost" &&
        //     currentWindow != "explorer")
        // {
        //     windowSwitches++;
        //     std::cout << currentWindow << "\n";
        //     std::cout << "Switches: " << windowSwitches << "\n";
        // }

        // std::this_thread::sleep_for(std::chrono::milliseconds(200));
//     }

//     return 0;
// }

// Conditional compilation for Windows-specific code
#ifdef _WIN32
    int main()
    {
        std::string prevWindow = "";
        std::string procName;
        int windowSwitches = -1; //KEEP IT AT -1, 0 CAUSES INCORRECT READING

        std::cout << "Tracking active windows. Press Ctrl+C to stop.\n";


        while (true)
        {
            //So declaring an ASYNC function to get the result of current active window on THE NEW THREAD, to avoid
            //API permission issues.
            auto futureWindow = std::async(std::launch::async, []() //Launch the task on new thread immediately
            {
                return getCurrentWindow();
            }); //Get the current window

            //Checking for max 3 seconds until the async func finishes
            if (futureWindow.wait_for(std::chrono::seconds(3)) == std::future_status::ready)
            {   //IF the status of futre is ready, get the name
                procName = futureWindow.get();
            }
            else
            { //Else skip
                continue;
            }

            //Checking various things
            if (procName.empty() || procName == prevWindow)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                continue;
            }

            prevWindow = procName;

            // filter common system/UWP apps
            if (procName != "StartMenuExperienceHost" &&
                procName != "SearchApp" &&
                procName != "ApplicationFrameHost" &&
                procName != "explorer")
            {
                windowSwitches++;
                std::cout << procName << "\n";
                std::cout << "Switches: " << windowSwitches << "\n";
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
#endif