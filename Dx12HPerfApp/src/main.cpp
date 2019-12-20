#define WIN32_LEAN_AND_MEAN

#include "CommonInc.h"

#include "Dx12HPerfApp.h"
#include "Win64App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    
    std::cerr << "hello this is my first application";

    Win64App* instance = Win64App::instance(hInstance);
    
    instance->get_singleton()->Run();
    


    return 0;
}

