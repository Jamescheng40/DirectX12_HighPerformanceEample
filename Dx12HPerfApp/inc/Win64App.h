
#include "CommonInc.h"


class Win64App 

{

public:

	//creating singleton object for Win64App class 
	static Win64App* instance(HINSTANCE hInstance);

	//running the applicaiton
	int Run();

	//initialize windows
	void initialize(WNDCLASSEXW* windowClass);

	//get single created object
	static Win64App* get_singleton();



protected:
	// Create an application instance.
	Win64App(HINSTANCE hInst);
	// Destroy the application instance and all windows associated with this application.
	virtual ~Win64App();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE m_hInstance;
	static HWND m_hwnd;
};

class Win64helper 
{
public:
	void ParseCommandLineArgs(_In_reads_(argc) WCHAR* argv[], int argc);
	bool m_useWarpDevice;

	// Window title.
	std::wstring m_title;




};