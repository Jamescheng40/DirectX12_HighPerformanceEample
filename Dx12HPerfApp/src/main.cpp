#define WIN32_LEAN_AND_MEAN

#include "CommonInc.h"

#include "Dx12HPerfApp.h"
#include "Win64App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    
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
    
    Win64App* instance = Win64App::instance(hInstance,title.c_str(), 720, 1280);
    
    //initialize dx12hperfapp class and set instance state for it
    std::shared_ptr<Dx12HPerfApp> myapp = std::make_shared<Dx12HPerfApp>();
    instance->SetWin64AppState(myapp);
    
    instance->get_singleton()->Run();
    


    return 0;
}

