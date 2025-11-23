#include <string>
#include <future>
#include <cstdio>
#include <chrono>
#include <cctype> // for isalpha

// -------------------------------------------------------
// WINDOWS IMPLEMENTATION
// -------------------------------------------------------
std::string getCurrentWindow()
{
    // Launch ActiveWindowHelper.exe asynchronously
    auto futureResult = std::async(std::launch::async, []() -> std::string {
        FILE* pipe = _popen("ActiveWindowHelper.exe", "r"); // spawn the helper
        if (!pipe) return "";                               // if pipe failed, return empty

        char buffer[256];
        std::string output;

        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) //context nullptr = \0 (end of string)
        {
            output += buffer;                                // append every line
        }

        _pclose(pipe);                                      // close safely
        //I forgot to close the pipe, causing a ~500mb leak

        // Everything before the | character
        size_t pos = output.find('|');
        std::string windowName;
        if (pos == std::string::npos)
            windowName = output;                             // no |, return full string
        else
            windowName = output.substr(0, pos);             // return before |

        // ----------------- Only return if contains at least one alphabet -----------------
        bool hasAlpha = false;
        for (char c : windowName)
        {
            if (std::isalpha(static_cast<unsigned char>(c)))
            {
                hasAlpha = true;
                break;
            }
        }

        if (!hasAlpha)
            return ""; // skip window names with no letters

        return windowName;
    });

    // Wait max 3 seconds for result
    if (futureResult.wait_for(std::chrono::seconds(3)) == std::future_status::ready)
    {
        return futureResult.get();                          // got the value
    }
    else
    {
        return "";                                         // timed out, skip
    }
}
