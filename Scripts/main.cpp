#include <iostream>
#include <chrono>
#include <thread>

// Assuming this header is available in your environment
#include "WindowTrackerAndShit/Headers/GetWindowRelatedInfoWin32.hpp" 

int main()
{
    std::string choice;
    std::cout << "Enter true or false: ";
    std::cin >> choice;

    if (choice == "true")
    {
        // Use an infinite loop (for (;;) is a common idiom)
        for (;;) 
        { 
            std::cout << getCurrentWindow() << "\n";
            
            // Wait for 1 second (1000 milliseconds)
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    // Note: The program will now require a hard termination (like closing the terminal or kill signal) 
    // since it no longer uses a specific handler to catch Ctrl+C gracefully.
    
    return 0; // This line is technically unreachable in the 'true' branch, but good practice.
}