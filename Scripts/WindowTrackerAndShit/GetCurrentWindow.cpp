#include <string>
#include <future>
#include <cstdio>
#include <chrono>

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

        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            output += buffer;                                // append every line
        }

        _pclose(pipe);                                      // close safely

        // Everything before the | character
        size_t pos = output.find('|');
        if (pos == std::string::npos)
            return output;                                  // no |, return full string
        return output.substr(0, pos);                       // return before |
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
