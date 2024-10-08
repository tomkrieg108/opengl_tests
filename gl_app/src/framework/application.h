#pragma once

#include "camera.h"
#include "events.h"
#include "test_app.h"

class Window;
class Layer;

class App
{
public:
	static App& instance() { return s_instance; }
	
	void Run();
	
	void OnMouseMove(EventMouseMove& e);
	void OnMouseScroll(EventMouseScroll& e);
	void OnMouseLDown(EventMouseLDown& e);
	void OnMouseLUp(EventMouseLUp& e);
	void OnMouseRDown(EventMouseRDown& e);
	void OnMouseRUp(EventMouseRUp& e);
	void OnMouseMDown(EventMouseMDown& e);
	void OnMouseMUp(EventMouseMUp& e);
	void OnKeyPressed(EventKeyPressed& e);
	void OnKeyReleased(EventKeyReleased& e);
	void OnWinResize(EventWinResize& e);
	void CheckKeys(double delta_time);


	PerspectiveCamera* GetCamera() { return m_camera; }
	Window* GetWindow() { return m_window; }

	
private:
	App();
	~App();

	
	void Startup();
	void Shutdown();
	void Render(double now, double time_step);

	void ImGuiInit();
	void ImGuiShutdown();
	void ImGuiUpdate();
	void ImGuiRender();
	void ImGuiNewFrame();

private:

	Window* m_window = nullptr;
	PerspectiveCamera* m_camera = nullptr;
	v2::Camera* m_camera2 = nullptr;
	Layer* m_layer = nullptr;
	Layer* m_coords = nullptr;

	static App s_instance;
};