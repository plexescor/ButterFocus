#include <iostream>
#include "Headers/GetWindowRelatedInfoWin32.hpp"


//-------------------------------------------------------
//WINDOWS IMPLEMENTATION
//-------------------------------------------------------



#ifdef _WIN32 //If compiling on windows, execute this: 
#include <Windows.h>//Include header in this so no include errors occur at the start of the shit
std::string getCurrentWindow() 
{
    HWND currentWindowHWND = GetForegroundWindow();
    int lengthOfTitle = GetWindowTextLengthW(currentWindowHWND);


    if (lengthOfTitle < 0) lengthOfTitle = 0; //Code was breaking, this singular line was suggested by chatgpt, and no, the entire thing wasnt vibe coded, but i did tool help from gpt in some matters, like the functions provided by the Win32 Api
    std::wstring buffer; //Wstring -> used to store UTF-16 characters, damn
    buffer.resize(lengthOfTitle + 1); //We did +1 because we want to ensure we get the full name, last charcter of a wstring (or a string) is \0, ie it denotes the end of a string, why is it so complex?
    //FOR ME AND OTHERs (i mean for noobs), buffer curr state: [??][??][??].....[\0]

    //Lets copy the stupid window text into our buffer, but first, store it in a temp int
    int copiedWindowTextW = GetWindowTextW(currentWindowHWND, &buffer[0], buffer.size()); //the & thing is a pointer, the [0] tells us that: 
    //ERROR HANDLING
    if (copiedWindowTextW == 0)
    {
        // std::cout << "The window doesnt have a title or there is an error!";
        buffer.clear(); //CLEAR THE BUFFER
    }
    else
    {
        std::string actualTitle;
        buffer.resize(copiedWindowTextW);

        //Calculate the size needed to convert UTF-16 to UTF-8, ugh, idk what am i doing, instead of learning for exams, i am doing this. nevertheless.
        int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, buffer.c_str(), -1, nullptr, 0, nullptr, nullptr);
        //If needed sizze is 0 or -ve, wont proceed with bad size/values.
        if (sizeNeeded <= 0)
        {
            return {};
        }
        else
        {
            //Resizing the actual title to the value we just obtained.
            actualTitle.resize(sizeNeeded);

            //Convert and flush the actual UTF-8 converted values
            int converted = WideCharToMultiByte(CP_UTF8, 0, buffer.c_str(), -1, &actualTitle[0], sizeNeeded, nullptr, nullptr);
            if (converted <= 0) return {}; //Return {} if conversion failed or there is an error
            if (!actualTitle.empty() && actualTitle.back() == '\0') actualTitle.pop_back(); //Remove the null byte or whatever it it
            return actualTitle;
        }
    }
    // std::cout << currentWindowHWND;
}
#endif