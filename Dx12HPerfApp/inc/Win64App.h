
#include "CommonInc.h"
#include "RenderBase.h"

class Win64App 

{

public:

	//creating singleton object for Win64App class 
	static Win64App* instance(HINSTANCE hInstance, const WCHAR * title, int height, int width);

	//running the applicaiton
	int Run();

	//initialize windows
	void WinSettings(WNDCLASSEXW* windowClass);

	//get single created object
	static Win64App* get_singleton();

	//set and passed in pointer to indicate this application is graphics related
	bool SetWin64AppState(std::shared_ptr<RenderBase> Appbase);

protected:
	// Create an application instance.
	Win64App(HINSTANCE hInst, const WCHAR* mWintitle, int height, int width);
	// Destroy the application instance and all windows associated with this application.
	virtual ~Win64App();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE m_hInstance;
	static HWND m_hwnd;
	const WCHAR* m_wintitle;
	int m_height;
	int m_width;
	std::shared_ptr<RenderBase> m_AppBase;
};

class Win64helper 
{
public:
	void ParseCommandLineArgs(_In_reads_(argc) WCHAR* argv[], int argc);
	bool m_useWarpDevice;

	// Window title.
	std::wstring m_title;
	


};