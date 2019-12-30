#pragma once
#include "RenderBase.h"
#include "d3dx12.h"

#include <DirectXMath.h>
#include <Windows.h>

#include <wrl.h>
#include <dxgi1_5.h>
#include <dxgi1_6.h>
class Dx12HPerfApp : public RenderBase
{
public:
	using super = RenderBase;

	friend class Win64App;

	Dx12HPerfApp();
	~Dx12HPerfApp();

	virtual bool InitializeApp() override;

	virtual void UnInitializeApp() override;

	virtual void testfunc() override; 

	//below to another class
	static const UINT BufferCount = 3;
	UINT m_CurrentBackBufferIndex;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_d3d12RTVDescriptorHeap;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> m_dxgiSwapChain;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_d3d12BackBuffers[BufferCount];
	UINT m_RTVDescriptorSize;
	// Update the render target views for the swapchain back buffers.


	// Create the swapchian.

	void UpdateRenderTargetViews();


	Microsoft::WRL::ComPtr<IDXGISwapChain4> CreateSwapChain();


	/**
	 * Return the current back buffer index.
	 */
	UINT GetCurrentBackBufferIndex() const;

	/**
 * Get the back buffer resource for the current back buffer.
 */
	Microsoft::WRL::ComPtr<ID3D12Resource> GetCurrentBackBuffer() const;

	/**
	* Present the swapchain's back buffer to the screen.
	* Returns the current back buffer index after the present.
	*/
	UINT Present();
	
	/**
	* Get the render target view for the current back buffer.
	*/
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentRenderTargetView() const;


	int m_ClientWidth;
	int m_ClientHeight;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(UINT numDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE type);

protected:


	virtual void OnUpdate(UpdateEventArgs& e) override;

	virtual void OnRender(RenderEventArgs& e) override;

	virtual	void OnKeyPressed(KeyEventArgs& e) override;

	virtual void OnMouseWheel(MouseWheelEventArgs& e) override;

	virtual void OnResize(ResizeEventArgs& e) override;

private:
	//debug layer
	int counter = 0;

	void TransitionResource(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> commandList, Microsoft::WRL::ComPtr <ID3D12Resource> resource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);

	void ClearRTV(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> commandList,
		D3D12_CPU_DESCRIPTOR_HANDLE rtv, FLOAT* clearColor);

	void ClearDepth(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> commandList,
		D3D12_CPU_DESCRIPTOR_HANDLE dsv, FLOAT depth = 1.0f);

	// Create a GPU buffer.
	void UpdateBufferResource(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> commandList,
		ID3D12Resource** pDestinationResource, ID3D12Resource** pIntermediateResource,
		size_t numElements, size_t elementSize, const void* bufferData,
		D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE);

	// Resize the depth buffer to match the size of the client area.
	void ResizeDepthBuffer(int width, int height);


	uint64_t m_FenceValues[BufferCount] = {};

	//vertex buffer for the cube
	Microsoft::WRL::ComPtr<ID3D12Resource> m_VertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_VertexBufferView;

	//index buffer for the cube
	Microsoft::WRL::ComPtr<ID3D12Resource> m_IndexBuffer;
	D3D12_INDEX_BUFFER_VIEW m_IndexBufferView;

	// Depth buffer.
	Microsoft::WRL::ComPtr<ID3D12Resource> m_DepthBuffer;

	// Descriptor heap for depth buffer.
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_DSVHeap;

	// Root signature
	Microsoft::WRL::ComPtr<ID3D12RootSignature> m_RootSignature;


	// Pipeline state object.
	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_PipelineState;
	
	
	D3D12_VIEWPORT m_Viewport;
	D3D12_RECT m_ScissorRect;

	float m_FoV;


	DirectX::XMMATRIX m_ModelMatrix;
	DirectX::XMMATRIX m_ViewMatrix;
	DirectX::XMMATRIX m_ProjectionMatrix;	

	bool m_ContentLoaded;

};