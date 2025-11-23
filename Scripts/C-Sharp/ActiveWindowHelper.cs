using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

class Program
{
    // ----------------- Win32 imports -----------------
    [DllImport("user32.dll")]
    static extern IntPtr GetForegroundWindow();

    [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
    static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

    [DllImport("user32.dll", CharSet = CharSet.Auto)]
    static extern int GetWindowTextLength(IntPtr hWnd);

    [DllImport("user32.dll")]
    static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint pid);

    [DllImport("user32.dll")]
    static extern int GetClassName(IntPtr hWnd, StringBuilder lpClassName, int nMaxCount);

    // ----------------- Last valid window storage -----------------
    static string lastValid = "";

    static void Main()
    {
        string output = "";

        // Create a get active window task asynchronously
        var task = Task.Run(() => GetActiveWindow()); 

        // Wait max 1 sec for safety
        if (task.Wait(1000)) 
        {
            output = task.Result;
        }
        else
        {
            // Timed out
            output = lastValid; // return last known window
        }

        // Output to console for C++ pipe
        Console.WriteLine(output);
        Console.Out.Flush(); // immediate flush prevents console freezes
    }

    static string GetActiveWindow()
    {
        IntPtr hwnd = GetForegroundWindow();
        if (hwnd == IntPtr.Zero)
            return lastValid; // return previous if no active window

        // Get class name
        StringBuilder className = new StringBuilder(256);
        GetClassName(hwnd, className, className.Capacity);
        string cls = className.ToString();

        // ----------------- Skip system / UWP / hidden / minimized windows -----------------
        // This is a hardcoded list of known system window classes
        string[] skipClasses = new string[]
        {
            "ApplicationFrameWindow",   // UWP windows
            "Windows.UI.Core.CoreWindow",
            "ImmersiveShell",
            "DV2ControlHost",           // modern overlay
            "Button",                   // Start menu / search buttons
            "Shell_TrayWnd",            // Taskbar
            "Progman",                  // desktop shell
            "WorkerW",                  // desktop wallpaper hosts
            "SysShadow",                // visual shadows
            "Windows.UI.Composition.DesktopWindow", // some overlays
            "MsgrIMEWindowClass",       // hidden IME windows
            "Internet Explorer_Server", // IE hidden windows
            "ApplicationFrameWindow",
            "Tooltips_Class32"          // tooltips
        };

        foreach (var s in skipClasses)
        {
            if (cls == s)
                return lastValid; // keep previous if this is system/overlay
        }

        // ----------------- Window title safely -----------------
        string title = "";
        try
        {
            int length = GetWindowTextLength(hwnd);
            if (length > 0)
            {
                StringBuilder sb = new StringBuilder(length + 1);
                GetWindowText(hwnd, sb, sb.Capacity);
                title = sb.ToString();
            }
        }
        catch 
        { 
            title = ""; 
        }

        // ----------------- Process name safely -----------------
        string procName = "";
        try
        {
            uint pid;
            GetWindowThreadProcessId(hwnd, out pid);
            var proc = Process.GetProcessById((int)pid);
            procName = proc.ProcessName;
        }
        catch 
        { 
            procName = ""; 
        }

        // ----------------- Compose output -----------------
        // "|" important to separate process name and title in C++ code
        string result = procName + "|" + title;

        // Update last valid window
        if (!string.IsNullOrWhiteSpace(result))
            lastValid = result;

        return lastValid; // always return last valid to C++
    }
}
