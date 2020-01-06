#include "..\inc\Win64App.h"



static Win64App* m_singleton = nullptr;
//windows handle
HWND Win64App::m_hwnd = nullptr;


Win64App* Win64App::instance(HINSTANCE hInstance,const  WCHAR * title, int height, int width, bool hide)
{

    Win64App* instance = new Win64App(hInstance, title, height, width, hide);
    m_singleton  = instance;
    return instance;
    
}

UINT Win64App::GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE type) const
{
    return m_d3d12Device->GetDescriptorHandleIncrementSize(type);
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

    m_AppBase->InitializeApp();


    ShowWindow(m_hwnd, SW_SHOW);

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

Microsoft::WRL::ComPtr<ID3D12Device2> Win64App::CreateDevice(Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter)
{
    Microsoft::WRL::ComPtr<ID3D12Device2> d3d12Device2;
    ThrowIfFailed(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&d3d12Device2)));
    //    NAME_D3D12_OBJECT(d3d12Device2);

        // Enable debug messages in debug mode.
#if defined(_DEBUG)
    Microsoft::WRL::ComPtr<ID3D12InfoQueue> pInfoQueue;
    if (SUCCEEDED(d3d12Device2.As(&pInfoQueue)))
    {
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);

        // Suppress whole categories of messages
        //D3D12_MESSAGE_CATEGORY Categories[] = {};

        // Suppress messages based on their severity level
        D3D12_MESSAGE_SEVERITY Severities[] =
        {
            D3D12_MESSAGE_SEVERITY_INFO
        };

        // Suppress individual messages by their ID
        D3D12_MESSAGE_ID DenyIds[] = {
            D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,   // I'm really not sure how to avoid this message.
            D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,                         // This warning occurs when using capture frame while graphics debugging.
            D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,                       // This warning occurs when using capture frame while graphics debugging.
        };

        D3D12_INFO_QUEUE_FILTER NewFilter = {};
        //NewFilter.DenyList.NumCategories = _countof(Categories);
        //NewFilter.DenyList.pCategoryList = Categories;
        NewFilter.DenyList.NumSeverities = _countof(Severities);
        NewFilter.DenyList.pSeverityList = Severities;
        NewFilter.DenyList.NumIDs = _countof(DenyIds);
        NewFilter.DenyList.pIDList = DenyIds;

        ThrowIfFailed(pInfoQueue->PushStorageFilter(&NewFilter));
    }
#endif

    return d3d12Device2;
}


Win64App* Win64App::get_singleton()
{   
    return m_singleton;
}

bool Win64App::SetWin64AppState(std::shared_ptr<RenderBase> Appbase)
{
    bool result = true;
    m_AppBase = Appbase;
    //load content and ready to run
   /* Appbase->testfunc();

*/

//making static appbase pointer
    AppPtr AppBasePtr = m_AppBase;
    gs_Windows.insert(WinMap::value_type(m_hwnd, AppBasePtr));
    gs_WindowByName.insert(WinNameMap::value_type(m_wintitle, AppBasePtr));

    return result;
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

Microsoft::WRL::ComPtr<ID3D12Device2> Win64App::GetDevice() const
{
    return m_d3d12Device;
}

Microsoft::WRL::ComPtr<IDXGIAdapter4> Win64App::GetAdapter(bool bUseWarp)
{
    Microsoft::WRL::ComPtr<IDXGIFactory4> dxgiFactory;
    UINT createFactoryFlags = 0;
#if defined(_DEBUG)
    createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

    ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory)));

    Microsoft::WRL::ComPtr<IDXGIAdapter1> dxgiAdapter1;
    Microsoft::WRL::ComPtr<IDXGIAdapter4> dxgiAdapter4;

    if (bUseWarp)
    {
        ThrowIfFailed(dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&dxgiAdapter1)));
        ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));
    }
    else
    {
        SIZE_T maxDedicatedVideoMemory = 0;
        for (UINT i = 0; dxgiFactory->EnumAdapters1(i, &dxgiAdapter1) != DXGI_ERROR_NOT_FOUND; ++i)
        {
            DXGI_ADAPTER_DESC1 dxgiAdapterDesc1;
            dxgiAdapter1->GetDesc1(&dxgiAdapterDesc1);

            // Check to see if the adapter can create a D3D12 device without actually 
            // creating it. The adapter with the largest dedicated video memory
            // is favored.
            if ((dxgiAdapterDesc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0 &&
                SUCCEEDED(D3D12CreateDevice(dxgiAdapter1.Get(),
                    D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)) &&
                dxgiAdapterDesc1.DedicatedVideoMemory > maxDedicatedVideoMemory)
            {
                maxDedicatedVideoMemory = dxgiAdapterDesc1.DedicatedVideoMemory;
                ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));
            }
        }
    }

    return dxgiAdapter4;
}

std::shared_ptr<CommandQueue> Win64App::GetCommandQueue(D3D12_COMMAND_LIST_TYPE type) const
{

    std::shared_ptr<CommandQueue> commandQueue;
    switch (type)
    {
    case D3D12_COMMAND_LIST_TYPE_DIRECT:
        commandQueue = m_DirectCommandQueue;
        break;
    case D3D12_COMMAND_LIST_TYPE_COMPUTE:
        commandQueue = m_ComputeCommandQueue;
        break;
    case D3D12_COMMAND_LIST_TYPE_COPY:
        commandQueue = m_CopyCommandQueue;
        break;
    default:
        assert(false && "Invalid command queue type.");
    }

    return commandQueue;
    
}

void Win64App::Flush()
{
    m_DirectCommandQueue->Flush();
    m_ComputeCommandQueue->Flush();
    m_CopyCommandQueue->Flush();

}

Win64App::Win64App(HINSTANCE hInst, const WCHAR * mWintitle, int height, int width, bool hide)
    :m_hInstance(hInst),
    m_height(height),
    m_width(width),
    m_hide(hide)
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

    m_hwnd = hWnd;

    m_dxgiAdapter = GetAdapter(false);
    if (m_dxgiAdapter)
    {
        m_d3d12Device = CreateDevice(m_dxgiAdapter);
    }
    if (m_d3d12Device)
    {
        m_DirectCommandQueue = std::make_shared<CommandQueue>(m_d3d12Device, D3D12_COMMAND_LIST_TYPE_DIRECT);
        m_ComputeCommandQueue = std::make_shared<CommandQueue>(m_d3d12Device, D3D12_COMMAND_LIST_TYPE_COMPUTE);
        m_CopyCommandQueue = std::make_shared<CommandQueue>(m_d3d12Device, D3D12_COMMAND_LIST_TYPE_COPY);
    }

    


    


}

Win64App::~Win64App()
{
}

LRESULT Win64App::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    AppPtr m_AppPtr;
    WinMap::iterator iter = gs_Windows.find(m_hwnd);
    if (iter != gs_Windows.end())
    {
        m_AppPtr = iter->second;
    }
    if(m_AppPtr){
    switch (message) {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT: 
    {
        UpdateEventArgs updateEventArgs(0.0f, 0.0f);
        m_AppPtr->OnUpdate(updateEventArgs);

        RenderEventArgs renderEventArgs(0.0f, 0.0f);
        m_AppPtr->OnRender(renderEventArgs);

         
    }
    break;
    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    }
    else 
    {
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;

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
