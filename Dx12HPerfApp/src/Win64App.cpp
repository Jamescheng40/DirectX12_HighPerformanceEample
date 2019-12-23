#include "..\inc\Win64App.h"



static Win64App* m_singleton = nullptr;
//windows handle
HWND Win64App::m_hwnd = nullptr;


Win64App* Win64App::instance(HINSTANCE hInstance,const  WCHAR * title, int height, int width)
{

    Win64App* instance = new Win64App(hInstance, title, height, width);
    m_singleton  = instance;
    return instance;
    
}

int Win64App::Run()
{
	//parse command line argument
	//int argv;
	//int argc;
	//LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    //Win64helper help;
    //help.ParseCommandLineArgs(argv, argc);
    //LocalFree(argv);

    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }



	return 0;
}

Win64App* Win64App::get_singleton()
{   
    return m_singleton;
}

void WinSettings(WNDCLASSEXW* wndClass)
{
    //wndClass->cbSize = sizeof(WNDCLASSEX);
    //wndClass->style = CS_HREDRAW | CS_VREDRAW;
    //wndClass->lpfnWndProc = &WindowProc;
    //wndClass->hInstance = m_hInstance;
    //wndClass->hCursor = LoadCursor(nullptr, IDC_ARROW);
    //wndClass->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    //wndClass->lpszMenuName = nullptr;
    //wndClass->lpszClassName = m_wintitle;


}

Win64App::Win64App(HINSTANCE hInst, const WCHAR * mWintitle, int height, int width)
    :m_hInstance(hInst),
    m_height(height),
    m_width(width)
{
    // Windows 10 Creators update adds Per Monitor V2 DPI awareness context.
// Using this awareness context allows the client area of the window 
// to achieve 100% scaling while still allowing non-client window content to 
// be rendered in a DPI sensitive fashion.
    m_wintitle = mWintitle;

    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);



    //Windows settings 
    WNDCLASSEXW wndClass = { 0 };
    //WinSettings(&wndClass);
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = &WindowProc;
    wndClass.hInstance = m_hInstance;
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndClass.lpszMenuName = nullptr;
    wndClass.lpszClassName = m_wintitle;


    //creating windows
    if (!RegisterClassExW(&wndClass))
    {
        MessageBoxA(NULL, "Unable to register the window class.", "Error", MB_OK | MB_ICONERROR);
    }

    RECT windowRect = { 0, 0, m_width, m_height };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hWnd = CreateWindowW(m_wintitle, m_wintitle,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr, nullptr, m_hInstance, nullptr);
    if (!hWnd)
    {
        MessageBoxA(NULL, "Could not create the render window.", "Error", MB_OK | MB_ICONERROR);
        
    }


    //ShowWindow(hWnd, SW_SHOW);


    


}

Win64App::~Win64App()
{
}

LRESULT Win64App::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT: {

    }
                 break;
    }
    return DefWindowProcW(hWnd, message, wParam, lParam);

}



void Win64helper::ParseCommandLineArgs(WCHAR* argv[], int argc)
{
    for (int i = 1; i < argc; ++i)
    {
        if (_wcsnicmp(argv[i], L"-warp", wcslen(argv[i])) == 0 ||
            _wcsnicmp(argv[i], L"/warp", wcslen(argv[i])) == 0)
        {
            m_useWarpDevice = true;
            m_title = m_title + L" (WARP)";
        }
    }


}
