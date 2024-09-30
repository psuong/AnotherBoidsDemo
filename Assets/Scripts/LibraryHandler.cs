using System;
using System.Runtime.InteropServices;
using UnityEngine;

public static class LibraryHandler
{
    private const string kernel32 = "kernel32";

    [DllImport(kernel32)]
    private static extern IntPtr LoadLibrary(string path);

    [DllImport(kernel32)]
    private static extern IntPtr GetProcAddress(IntPtr libraryHandle, string symbolName);

    [DllImport(kernel32)]
    private static extern bool FreeLibrary(IntPtr libraryHandle);


    public static T GetDelegate<T>(IntPtr libraryPtr, string functionName) where T : class
    {
        var symbol = GetFunctionPointer(libraryPtr, functionName);
        return Marshal.GetDelegateForFunctionPointer(symbol, typeof(T)) as T;
    }

    public static IntPtr GetFunctionPointer(IntPtr libraryPtr, string functionName)
    {
        var symbol = GetProcAddress(libraryPtr, functionName);

        if (symbol == IntPtr.Zero)
        {
            Debug.LogError($"Could not find function: {functionName}");
            throw new InvalidOperationException($"Cannot find function: {functionName}");
        }
        return symbol;
    }
}
