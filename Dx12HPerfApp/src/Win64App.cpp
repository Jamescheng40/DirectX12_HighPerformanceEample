#include "..\inc\Win64App.h"



static Win64App* m_singleton = nullptr;
//windows handle
HWND Win64App::m_hwnd = nullptr;

Win64App* Win64App::instance(HINSTANCE hInstance)
{

    Win64App* instance = new Win64App(hInstance);
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
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }



	return 0;
}

void Win64App::initialize(WNDCLASSEXW* windowClass)
{

    
}

Win64App* Win64App::get_singleton()
{   
    return m_singleton;
}

Win64App::Win64App(HINSTANCE hInst)
    :m_hInstance(hInst)
{
    // Windows 10 Creators update adds Per Monitor V2 DPI awareness context.
// Using this awareness context allows the client area of the window 
// to achieve 100% scaling while still allowing non-client window content to 
// be rendered in a DPI sensitive fashion.


    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    WNDCLASSEXW  windowClass = { 0 };
    
    //initialize( windowClass);
    //windowClass->cbSize = sizeof(WNDCLASSEX);
    //windowClass->style = CS_HREDRAW | CS_VREDRAW;
    //windowClass->lpfnWndProc = WindowProc;
    //windowClass->hInstance = m_hInstance;
    //windowClass->hCursor = LoadCursor(NULL, IDC_ARROW);
    //windowClass->lpszClassName = L"Dx12HighPerfEx";
    //windowClass->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = m_hInstance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = L"Dx12HighPerfEx";
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);


    if (!RegisterClassExW(&windowClass))
    {
        MessageBoxA(NULL, "Unable to register the window class.", "Error", MB_OK | MB_ICONERROR);
    }


    RECT windowRect = { 0, 0, 1280, 720 };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
    std::wstring name(L"caoniba");
    HWND hWnd = CreateWindowW(L"1", name.c_str(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr, nullptr, m_hInstance, nullptr);
    
    if (!hWnd) {
        MessageBoxA(NULL, "Window handle = NULL", "Error", MB_OK | MB_ICONERROR);
    }


    ShowWindow(hWnd, SW_SHOW);


    


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
        PAINTSTRUCT ps;
        HDC hDC = BeginPaint(hWnd, &ps);
        char* cpaText[] = {
            "Hello World!",
            "This is a hello world application made in the Win32 API",
            "This example was made by some random dude, aka -LeetGamer-"
        };
        int iY = 5;
        for (int iLoopCounter = 0; cpaText[iLoopCounter] != '\0'; iLoopCounter++, iY += 20) {
            TextOut(hDC, 5, iY, cpaText[iLoopCounter], strlen(cpaText[iLoopCounter]));
        }
        EndPaint(hWnd, &ps);
    }
                 break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);

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
