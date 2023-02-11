#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>

extern "C"
{
#include "../platform.h"
#include "../UIWindow.h"
#include "../UIApplication.h"

    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    HINSTANCE __instance;

    void _UIPlatformMain(UIApplication *application)
    {
        __instance = GetModuleHandle(NULL);
    }

    void _UIPlatformEventLoop(UIApplication *application)
    {
        MSG msg = {};
        int msgCount = GetMessage(&msg, NULL, 0, 0);
        if (msgCount > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void _UIPlatformWindowCreate(UIWindow *window)
    {
        // Register the window class.
        const wchar_t CLASS_NAME[] = L"Sample Window Class";

        RECT wr = {0, 0, window->frame.width, window->frame.height};
        AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

        WNDCLASS wc = {};

        wc.lpfnWndProc = WindowProc;
        wc.hInstance = __instance;
        wc.lpszClassName = CLASS_NAME;

        RegisterClass(&wc);

        // Create the window.

        HWND hwnd = CreateWindowEx(
            0,                           // Optional window styles.
            CLASS_NAME,                  // Window class
            L"Learn to Program Windows", // Window text
            WS_OVERLAPPEDWINDOW,         // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,

            NULL,       // Parent window
            NULL,       // Menu
            __instance, // Instance handle
            NULL        // Additional application data
        );

        window->platformWindow = hwnd;

        ShowWindow(hwnd, 1);
    }

    void _UIPlatformWindowDestroy(UIWindow *window)
    {
        DestroyWindow((HWND)window->platformWindow);
    }

    void _UIPlatformWindowSetTitle(UIWindow *window, const char *title)
    {
        int size = MultiByteToWideChar(CP_UTF8, 0, title, -1, NULL, 0);
        wchar_t *wide_title = new wchar_t[size];
        MultiByteToWideChar(CP_UTF8, 0, title, -1, wide_title, size);
        LPCWSTR lpcwstr_title = wide_title;
        SetWindowText((HWND)window->platformWindow, lpcwstr_title);
    }

    void _UIPlatformWindowRender(UIWindow *window)
    {
    }

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
        }
            return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}