#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>
#include <chrono>

#include "WindowTrackerAndShit/Headers/GetCurrentWindow.hpp"
#include "MainGUI/Headers/MainGUI.hpp"

// Conditional compilation for Windows-specific code
#ifdef _WIN32

    std::mutex mtx;
    std::string prevWindow;
    std::string sharedWindow;
    std::atomic<bool> quit(false);

    void WindowWorker()
    {
        while (!quit)
        {
            std::string window = getCurrentWindow();
            if (!window.empty() 
            && window.find_first_not_of(' ') != std::string::npos
            && window != "SearchApp" 
            && window != "explorer"
            && window != prevWindow)
            {
                std::lock_guard<std::mutex> lock(mtx);
                sharedWindow = window;
                prevWindow = window;
            }          
            std::this_thread::sleep_for(std::chrono::milliseconds(300)); 
        }
    }
    
    int main()
    {
        std::thread worker(WindowWorker);
        
        std::string lastPrintedWindow;

        while (true) 
        {
            std::string current;
            {
                std::lock_guard<std::mutex> lock(mtx);
                current = sharedWindow;
            }

            if (!current.empty() && current != lastPrintedWindow) {
                std::cout << "Current window: " << current << std::endl;
                lastPrintedWindow = current;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
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