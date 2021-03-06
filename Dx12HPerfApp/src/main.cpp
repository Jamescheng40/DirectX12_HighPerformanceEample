#define WIN32_LEAN_AND_MEAN

#include "CommonInc.h"

#include "Dx12HPerfApp.h"
#include "Win64App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    LPWSTR* szArglist;
    int argCount;
    bool hide = false;

    //parsing command line here to get the show/hide parameter for the swapchain
    szArglist = CommandLineToArgvW(GetCommandLineW(), &argCount);
    for (int i = 0; i < argCount; i++)
    {

            if ( wcscmp(szArglist[i], L"-h") == 0)
            {
                hide = true;
            }

    }


    // Set the working directory to the path of the executable.
    WCHAR path[MAX_PATH];
    HMODULE hModule = GetModuleHandleW(NULL);
    if (GetModuleFileNameW(hModule, path, MAX_PATH) > 0)
    {
        PathRemoveFileSpecW(path);
        SetCurrentDirectoryW(path);
    }


    std::cerr << "hello this is my first application";
    std::wstring title(L"DX12 High Performance Application");
    
    Win64App* instance = Win64App::instance(hInstance,title.c_str(), 720, 1280, hide);
    
    //initialize dx12hperfapp class and set instance state for it
    std::shared_ptr<Dx12HPerfApp> myapp = std::make_shared<Dx12HPerfApp>();
    instance->SetWin64AppState(myapp);
    
    instance->get_singleton()->Run();
    


    return 0;
}

