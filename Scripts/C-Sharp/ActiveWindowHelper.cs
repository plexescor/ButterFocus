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

    static void Main()
    {
        string output = "";
        var task = Task.Run(() => GetActiveWindow());

        if (task.Wait(1000)) // wait max 1 sec
        {
            output = task.Result;
        }
        else
        {
            // Timed out
            output = "";
        }

        Console.WriteLine(output);
        Console.Out.Flush(); // immediate flush for C++ pipe
    }

    static string GetActiveWindow()
    {
        IntPtr hwnd = GetForegroundWindow();
        if (hwnd == IntPtr.Zero)
            return "";

        // Filter system/UWP windows by class name
        StringBuilder className = new StringBuilder(256);
        GetClassName(hwnd, className, className.Capacity);
        string cls = className.ToString();

        if (cls == "ApplicationFrameWindow" ||
            cls == "Windows.UI.Core.CoreWindow" ||
            cls == "ImmersiveShell")
            return "";

        // Window title safely
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
        catch { title = ""; }

        // Process name safely
        string procName = "";
        try
        {
            uint pid; // declare before
            GetWindowThreadProcessId(hwnd, out pid);
            var proc = Process.GetProcessById((int)pid);
            procName = proc.ProcessName;
        }
        catch { procName = ""; }

        return procName + "|" + title;
    }
}
