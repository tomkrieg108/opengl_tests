#include "pch.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "base.h"
#include "layer.h"
#include "window.h"
#include "shader.h"
#include "camera.h"
#include "gl_utils.h"
#include "application.h"

App App::s_instance;

App::App()
{
	//m_window = std::make_unique<Window>();
	m_window = new Window();

	float aspect_ratio = (float)m_window->BufferWidth() / (float)m_window->BufferHeight();
	m_camera = new PerspectiveCamera(aspect_ratio);
	//m_camera = new OrthographicCamera();

	TestAppMgr test_app_mgr(*m_window, *m_camera);
	m_coords = test_app_mgr.GetLayer(TestAppMgr::COORD_SYS);

	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_TEXTURE_TEST);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_TEXTURES_COMBINED_TEST);

	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_BASIC_LIGHTING_COLOURS);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_BASIC_LIGHTING_DIFFUSE);
	m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_BASIC_LIGHTING_SPECULAR);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_MATERIALS_TEST);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_LIGHT_MAP_DIFFUSE);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_LIGHT_MAP_SPECULAR);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_LIGHT_MAP_EMISSION);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_LIGHT_CASTER_DIRECTIONAL);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_LIGHT_CASTER_POINT);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_LIGHT_CASTER_SPOT);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_LIGHT_CASTER_SPOT_SOFT);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_MULTIPLE_LIGHTS);

	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_MODEL_LOADING_TEST);


	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_DEPTH_TESTING);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_DEPTH_TESTING_VIEW);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_STENCIL_TESTING);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_BLEND_DISCARD_TESTING);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_BLEND_SORT_TESTING);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_FACE_CULLING); 
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_FRAME_BUFFER_TEST);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_SKYBOX);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_ENV_MAPPING);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_ADVANCED_GLSL_UBO);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_GEOMETRY_SHADER_HOUSES);
  //m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_GEOMETRY_SHADER_EXPLODING);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_NORMAL_VISUALISATION);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_INSTANCING_QUADS);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_ASTEROIDS);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_ASTEROIDS_INSTANCED);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_ANTI_ALIASING_MSAA);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_ANTI_ALIASING_OFFSCREEN);

	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_ADVANCED_LIGHTING);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_GAMMA_CORRECTION);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_SHADOW_MAPPING_DEPTH);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_SHADOW_MAPPING_BASE);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_SHADOW_MAPPING);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_POINT_SHADOW);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_POINT_SHADOW_SOFT);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_NORMAL_MAPPING);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_PARALLAX_MAPPING);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_HDR);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_BLOOM);
	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_DEFERRED_SHADING);

	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_TEXT_RENDERING);

	//m_layer = test_app_mgr.GetLayer(TestAppMgr::LGL_HEIGHT_MAP_CPU);

	//m_layer = test_app_mgr.GetLayer(TestAppMgr::BIB_2);

		
	EventManager::SetCallback(this, &App::OnMouseMove);
	EventManager::SetCallback(this, &App::OnMouseLDown);
	EventManager::SetCallback(this, &App::OnMouseLUp);
	EventManager::SetCallback(this, &App::OnMouseRDown);
	EventManager::SetCallback(this, &App::OnMouseRUp);
	EventManager::SetCallback(this, &App::OnMouseMDown);
	EventManager::SetCallback(this, &App::OnMouseMUp);
	EventManager::SetCallback(this, &App::OnMouseScroll);
	EventManager::SetCallback(this, &App::OnKeyPressed);
	EventManager::SetCallback(this, &App::OnKeyReleased);
	EventManager::SetCallback(this, &App::OnWinResize);
	//DisplayGLVersion();
	//DisplayGLParams();
	//DisplayVideoModes();
}


App::~App()
{
	delete m_layer;
	if (m_coords)
		delete m_coords;
}

void App::Startup()
{
	if(m_coords)
		m_coords->Startup();
	m_layer->Startup();
	App::ImGuiInit();
}

void App::Shutdown()
{
	if (m_coords)
		m_coords->Shutdown();
	m_layer->Shutdown();
	App::ImGuiShutdown();
}

void App::Render(double now, double time_step)
{
	//const GLfloat clear_color[] = { glm::sin(now) * 0.5f + 0.5f, glm::cos(now) * 0.5f + 0.5f,
	//						  0.0f, 1.0f };
	//GLfloat clear_color[] = { 0.0f, 0.0f, 0.1f, 1.0f };
	//glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // don't forget to clear the stencil buffer!
	if (m_coords)
		m_coords->OnUpdate(now, time_step);
	m_layer->OnUpdate(now, time_step);
}

void App::Run()
{
	App::Startup();

	auto delta_time = 0.0;
	auto last_time = glfwGetTime();
	while (!m_window->ShouldClose())
	{
		auto now = glfwGetTime(); //in seconds
		delta_time = now - last_time;
		last_time = now;

		CheckKeys(delta_time);

		App::Render(now, delta_time);
		App::ImGuiRender();
		
		m_window->SwapBuffers();
		m_window->PollEvents();
	}

	App::Shutdown();
}

void App::ImGuiInit()
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_window->GlfwWindow(), true);
	const char* glsl_version = "#version 430";
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

	float fontSize = 22.0f;
	//TODO - can't find these files in debug build - craches (ok in realease) WTF?
	//io.Fonts->AddFontFromFileTTF("asset/fonts/opensans/OpenSans-Bold.ttf", fontSize);
	//io.FontDefault = io.Fonts->AddFontFromFileTTF("asset/fonts/opensans/OpenSans-Regular.ttf", fontSize);
	//ImGui::StyleColorsDark();
}

void App::ImGuiUpdate()
{
	auto win_width = m_window->Width();
	auto buf_width = m_window->BufferWidth();
	//ImGuiWindowFlags window_flags = 0;
	ImGui::Begin("App");

	if (ImGui::CollapsingHeader("Window"))
	{
		//if (ImGui::TreeNode("Frame Rate"))
		{
			
			ImGui::Text("Width,Height %d %d : ", m_window->Width(), m_window->Height());
			ImGui::Text(" Buf Width, Buf Height %d %d : ", m_window->BufferWidth(), m_window->BufferHeight());
			ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//ImGui::TreePop();
		}
	}

	if (ImGui::CollapsingHeader("Camera"))
	{
		//ImGui::Text("Info re Camera");

		ImGui::SliderFloat3("Position ", &(m_camera->Position()[0]), -100.0f, 100.0f);
		ImGui::SliderFloat3("Front ", &(m_camera->Front()[0]), -1.01f, 1.01f);
		ImGui::SliderFloat3("Up    ", &(m_camera->Up()[0]), -1.01f, 1.01f);
		ImGui::SliderFloat3("Right ", &(m_camera->Right()[0]), -1.01f, 1.01f);
		
		auto yaw = m_camera->Yaw();
		auto pitch = m_camera->Pitch();
		auto near = m_camera->ZNear();
		auto far = m_camera->ZFar();

		ImGui::SliderFloat("Yaw", &yaw, -180.0f, 180.0f);
		ImGui::SliderFloat("Pitch", &pitch, -180.0f, 180.0f);
		//ImGui::SliderFloat("FOV", &(m_camera->F), 15.0f, 75.0f);

		ImGui::SliderFloat("Z Near", &near, 0.01f, 2.0f);
		ImGui::SliderFloat("Z Far", &far, 80.0f, 200.0f);
	}

	ImGui::End();

	//ImGui::ShowDemoWindow();
}

void App::ImGuiShutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void App::ImGuiRender()
{
	App::ImGuiNewFrame();

	App::ImGuiUpdate();
	m_layer->ImGuiUpdate();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void App::ImGuiNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void App::OnMouseMove(EventMouseMove& e)
{
	// don't pass mouse and keyboard presses further if an ImGui widget is active
	auto& io = ImGui::GetIO();
	if (io.WantCaptureMouse)
	{
		return;
	}

	bool* keys = m_window->GetKeys().m_key_code;
	if (keys[GLFW_KEY_LEFT_ALT])
		return;

	const float sensitivity = 0.1f;
 	m_camera->Turn(e.delta_x * sensitivity, e.delta_y * sensitivity);
	std::cout << "Mouse move x y:" << e.delta_x << "," << e.delta_y << "\n";
}

void App::OnMouseLDown(EventMouseLDown& e)
{
	std::cout << "Left Mouse Button Pressed\n";
}
void App::OnMouseLUp(EventMouseLUp& e)
{
	std::cout << "Left Mouse Button Released\n";
}
void App::OnMouseRDown(EventMouseRDown& e)
{
	std::cout << "Right Mouse Button Pressed\n";
}
void App::OnMouseRUp(EventMouseRUp& e)
{
	std::cout << "Right Mouse Button Released\n";
}
void App::OnMouseMDown(EventMouseMDown& e)
{
	std::cout << "Middle Mouse Button Pressed\n";
}
void App::OnMouseMUp(EventMouseMUp& e)
{
	std::cout << "Middle Mouse Button Released\n";
}

void App::OnMouseScroll(EventMouseScroll& e)
{
	m_camera->Zoom(e.y_offset);
	std::cout << "Mouse scroll \n";
}

void App::OnKeyPressed(EventKeyPressed& e)
{
	auto& io = ImGui::GetIO();
	if (io.WantCaptureKeyboard)
	{
		return;
	}
	std::cout << "Key code pressed " << e.key << "\n";
}

void App::OnKeyReleased(EventKeyReleased& e)
{
	auto& io = ImGui::GetIO();
	if (io.WantCaptureKeyboard)
	{
		return;
	}
	std::cout << "Key code Released " << e.key << "\n";
}


void App::OnWinResize(EventWinResize& e)
{
	m_camera->SetAspectRatio((float)e.buffer_width, (float)e.buffer_height);
	std::cout << "Win Resize\n";
}

void App::CheckKeys(double delta_time)
{
	const float move_speed = 5.0f;
	const float t = (float)(delta_time);
	bool* keys = m_window->GetKeys().m_key_code;

	//if (!m_imgui_layer->IsDisplayed())
	//if (!m_input_disabled)
	{
		if (keys[GLFW_KEY_W])
		{
			m_camera->MoveForward(move_speed * t);
		}

		if (keys[GLFW_KEY_S])
		{
			m_camera->MoveForward(-move_speed * t);
		}

		if (keys[GLFW_KEY_A])
		{
			m_camera->MoveRight(-move_speed * t);
		}

		if (keys[GLFW_KEY_D])
		{
			m_camera->MoveRight(move_speed * t);
		}

	}
	if (keys[GLFW_KEY_ESCAPE])
		m_window->ShutDown();
}

