#pragma once 

#include "CommonInc.h"
#include "RenderBase.h"
#include "driver/DX12Resources.h"
#include <dxgi1_6.h>
#include <Windows.h>

#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_5.h>


#include <memory>
#include <string>
#include <map>

using AppPtr = std::shared_ptr<RenderBase>;
using WinMap = std::map< HWND, AppPtr >;
using WinNameMap = std::map< std::wstring, AppPtr >;

static WinMap gs_Windows;
static WinNameMap gs_WindowByName;

class Win64App 

{

public:

	static HWND m_hwnd;

	//creating singleton object for Win64App class 
	static Win64App* instance(HINSTANCE hInstance, const WCHAR * title, int height, int width, bool hide);

	//running the applicaiton
	int Run();

	//initialize windows
	void WinSettings(WNDCLASSEXW* windowClass);

	//get single created object
	static Win64App* get_singleton();

	//set and passed in pointer to indicate this application is graphics related
	bool SetWin64AppState(std::shared_ptr<RenderBase> Appbase);


	///**
	// * Get the Direct3D 12 device
	//*/
	//Microsoft::WRL::ComPtr<ID3D12Device2> GetDevice() const;

	int m_height;
	int m_width;

	UINT GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE type) const;

	/**
 * Get a command queue. Valid types are:
 * - D3D12_COMMAND_LIST_TYPE_DIRECT : Can be used for draw, dispatch, or copy commands.
 * - D3D12_COMMAND_LIST_TYPE_COMPUTE: Can be used for dispatch or copy commands.
 * - D3D12_COMMAND_LIST_TYPE_COPY   : Can be used for copy commands.
 */
	std::shared_ptr<CommandQueue> GetCommandQueue(D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT) const;

	// Flush all command queues.
	void Flush();

	Microsoft::WRL::ComPtr<ID3D12Device2> CreateDevice(Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter);
	/**
		* Get the Direct3D 12 device
		*/
	Microsoft::WRL::ComPtr<ID3D12Device2> GetDevice() const;

	Microsoft::WRL::ComPtr<IDXGIAdapter4> GetAdapter(bool bUseWarp);

	Microsoft::WRL::ComPtr<IDXGIAdapter4> m_dxgiAdapter;

	//stuff from commandqueueclass
	std::shared_ptr<CommandQueue> m_DirectCommandQueue;
	std::shared_ptr<CommandQueue> m_ComputeCommandQueue;
	std::shared_ptr<CommandQueue> m_CopyCommandQueue;


	std::shared_ptr<RenderBase> m_AppBase;
	

	//swapchain show/hide option
	bool m_hide;

protected:
	// Create an application instance.
	Win64App(HINSTANCE hInst, const WCHAR* mWintitle, int height, int width, bool hide);
	// Destroy the application instance and all windows associated with this application.
	virtual ~Win64App();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE m_hInstance;
	
	const WCHAR* m_wintitle;


	Microsoft::WRL::ComPtr<ID3D12Device2> m_d3d12Device;

	
};

class Win64helper 
{
public:
	void ParseCommandLineArgs(_In_reads_(argc) WCHAR* argv[], int argc);
	bool m_useWarpDevice;

	// Window title.
	std::wstring m_title;
	


};