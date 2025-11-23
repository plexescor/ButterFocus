#include <iostream>
#include <thread>
#include <future>
#include <chrono>

#include "WindowTrackerAndShit/Headers/GetCurrentWindow.hpp"
#include "MainGUI/Headers/MainGUI.hpp"

// Conditional compilation for Windows-specific code
#ifdef _WIN32
    int main()
    {
        createWindow(getCurrentWindow());
        return 0;
    }




    //*******************************************************************//
    //              THE CODE BELOW IS FOR TESTING PURPOSES               //
    //*******************************************************************//


    // int main()
    // {   
    //     //Vars
    //     std::string currentWindow;
    //     std::string previousWindow;
    //     int switches = -1;//KEEP THIS AT -1, otherwise issues are caused

    //     while (true)
    //     {
    //         //call the function and store it in currentWindow;
    //         currentWindow = getCurrentWindow();
    //         //Skip this iteration if previous window is same as current
    //         if (previousWindow == currentWindow)
    //         {
    //             std::this_thread::sleep_for(std::chrono::milliseconds(300));
    //             continue;
    //         }
    //         //Filter shit
    //         if (!currentWindow.empty()                 // not empty
    //             && currentWindow.find_first_not_of(' ') != std::string::npos  // has at least 1 non-space
    //             && currentWindow != "SearchApp"
    //             && currentWindow != "explorer"
    //            )
    //            {
    //                 previousWindow = currentWindow;
    //                 switches++;
    //                 std::cout<<currentWindow << std::endl;
    //                 std::cout.flush();
    //                 std::cout<<"Swicthes: "<<switches<< std::endl;
    //                 std::cout.flush();
    //                 previousWindow = currentWindow;
    //                 std::this_thread::sleep_for(std::chrono::milliseconds(300));
    //            }
    //         std::cout.flush();
    //     }
    // }

    
#endif