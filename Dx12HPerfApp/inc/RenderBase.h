#pragma once

#include "CommonInc.h"

#include <Events.h>

class RenderBase : public std::enable_shared_from_this<RenderBase> 
{
public:
	RenderBase();

	friend class Win64App;

	virtual ~RenderBase();

	// initialize/load app content
	virtual bool InitializeApp() = 0;

	virtual void UnInitializeApp() = 0;

	virtual void Destroy();

	virtual void testfunc() = 0;


protected:

	/**
  *  windows WM_PAINT update base.
  */
	virtual void OnUpdate(UpdateEventArgs& e);

	virtual void OnRender(RenderEventArgs& e);

	virtual void OnKeyPressed(KeyEventArgs& e);

	virtual void OnKeyReleased(KeyEventArgs& e);

	virtual void OnMouseMoved(MouseMotionEventArgs& e);

	virtual void OnMouseButtonPressed(MouseMotionEventArgs& e);

	virtual void OnMouseButtonReleased(MouseMotionEventArgs& e);

	virtual void OnMouseWheel(MouseWheelEventArgs& e);

	virtual void OnResize(ResizeEventArgs& e);

	virtual void OnWindowDestroy();

private:




};