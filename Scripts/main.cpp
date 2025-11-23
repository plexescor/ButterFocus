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

    std::mutex mtx;//LOCKING SHIT
    std::string prevWindow;

    std::string sharedWindow;
    int swicthesG = -1; //G -> global
    std::atomic<bool> quit(false); //The exit conditon for app

    void WindowWorker() //Worker running on worker thread
    {
        while (!quit)
        {
            std::string window = getCurrentWindow(); //get currrent window
            if (!window.empty()  //Some checks
            && window.find_first_not_of(' ') != std::string::npos //idk, chatgpt suggested
            && window != "SearchApp" 
            && window != "explorer"
            && window != prevWindow)
            {
                std::lock_guard<std::mutex> lock(mtx);//Lock before modifyig
                sharedWindow = window;
                prevWindow = window;//I dont need to explain
                swicthesG++;
            }          
            std::this_thread::sleep_for(std::chrono::milliseconds(300)); //sleep to not hammer the cpu
        }
    }
    
    int main()
    {
        createWindow(); //Call the create window function
        std::thread worker(WindowWorker); //Create a new thread 
        
        std::string lastPrintedWindow;

        while (true) 
        {
            std::string current;
            int switchesS; //S -> Scoped
            { //Keep these brackets
                std::lock_guard<std::mutex> lock(mtx);
                current = sharedWindow; //Lock before reading
                switchesS = swicthesG;
            }

            if (!current.empty() && current != lastPrintedWindow) 
            {
                lastPrintedWindow = current;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(300));//zzzzzzzzzzzzzzzzzzz
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