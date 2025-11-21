// #include <iostream>
// #include "Headers/GetWindowRelatedInfoWin32.hpp"

// //-------------------------------------------------------
// //WINDOWS IMPLEMENTATION
// //-------------------------------------------------------

// #ifdef _WIN32 //If compiling on windows, execute this: 
// #include <Windows.h> //Include header in this so no include errors occur at the start of the shit

// std::string getCurrentWindow() 
// {
//     HWND currentWindowHWND = GetForegroundWindow();
//     if (currentWindowHWND == NULL) 
//     {
//         return "[Error: No Foreground Window]"; //Bro, nothing is in front, sad
//     }

//     int lengthOfTitle = GetWindowTextLengthW(currentWindowHWND);

//     if (lengthOfTitle <= 0) 
//     {
//         return "[No Title]"; //Bro, this window is sneaky, has no title
//     }

//     std::wstring buffer(lengthOfTitle + 1, L'\0'); 
//     //FOR ME AND OTHERs (i mean for noobs), buffer curr state: [??][??][??].....[\0]

//     int copiedWindowTextW = GetWindowTextW(currentWindowHWND, &buffer[0], lengthOfTitle + 1);
//     //the & thing is a pointer, the [0] tells us that

//     if (copiedWindowTextW <= 0)
//     {
//         // std::cout << "The window doesnt have a title or there is an error!";
//         buffer.clear(); //CLEAR THE BUFFER
//         return "[No Title]"; //Still nothing bro, move on
//     }
//     else
//     {
//         std::string actualTitle;
//         // buffer.resize(copiedWindowTextW);

//         //Calculate the size needed to convert UTF-16 to UTF-8, ugh, idk what am i doing, instead of learning for exams, i am doing this. nevertheless.
//         int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, buffer.c_str(), copiedWindowTextW, nullptr, 0, nullptr, nullptr);
//         //If needed size is 0 or -ve, wont proceed with bad size/values.
//         if (sizeNeeded <= 0)
//         {
//             return "[Conversion Failed]"; //Bro, conversion fucked up
//         }

//         //Resizing the actual title to the value we just obtained.
//         actualTitle.resize(sizeNeeded);

//         //Convert and flush the actual UTF-8 converted values
//         int converted = WideCharToMultiByte(CP_UTF8, 0, buffer.c_str(), copiedWindowTextW, &actualTitle[0], sizeNeeded, nullptr, nullptr);
//         if (converted <= 0) return "[Conversion Failed]"; //Return if conversion failed or there is an error

//         if (!actualTitle.empty() && actualTitle.back() == '\0') actualTitle.pop_back(); //Remove the null byte or whatever it it
//         return actualTitle;
//     }

//     // std::cout << currentWindowHWND;
// }
// #endif
