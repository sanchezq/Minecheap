#include "App.h"

// LibGFX
#include "Resources/Texture.h"
#include "ResourceGFX.h"

// IMGUI
#pragma warning(push)
#pragma warning(disable:26495)
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#pragma warning(pop)

// Glad and OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream> // std::cerr, std::endl, exit()

#include "SaveXML.h"
#include "GameManager.h"

// Static definition
GameManager App::ms_gameManager;
int App::ms_windowWidth = 1250;
int App::ms_windowHeight = 800;

App::App(const int windowWidth, const int windowHeight, const char* windowName, const char* iconPath, const bool /*vsync*/)
{
	// TODO Activate or deactivate vsync with the bool sent
	ms_windowWidth = windowWidth;
	ms_windowHeight = windowHeight;

	InitGLFW(windowName);
	ConfigGLFW();
	SetWindowIcon(iconPath);

	SetWindowCallbacks();
	InitLibrary();
	InitGlad();

	// TODO Need to use less memory or use the heap
	Resources::Scene* scene = new Resources::Scene();
	if (scene == nullptr)
	{
		return;
	}
	scene->InitScene();

	ms_gameManager.Initialize(m_window,*scene);
	framebuffer_size_callback(nullptr, ms_windowWidth, ms_windowHeight);
}

App::~App()
{
	delete &App::GetGameManager().MutateScene();
}

GameManager& App::GetGameManager()
{
	return ms_gameManager;
}

void App::SetWindowSize(const int width, const int height)
{
	ms_windowWidth = width;
	ms_windowHeight = height;
}

void App::Run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		SetDeltaTime((float)glfwGetTime());
#ifdef _DEBUG
		DisplayFPS();
#endif // _DEBUG		
		ms_gameManager.Update(m_window, ms_windowWidth, ms_windowHeight, m_delta);

		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);
	}
	CleanBeforeExit();
}

void App::InitGLFW(const char* windowName)
{
	/* Initialize the library */
	if (!glfwInit())
		return exit(-1);

	//-------------- glfw window creation / option generate fullscreen ---------------//
	m_window = glfwCreateWindow(ms_windowWidth, ms_windowHeight, windowName, nullptr, nullptr);
	if (!m_window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return exit(-1);
	}

	glfwMakeContextCurrent(m_window);
}

void App::ConfigGLFW()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//---> Set a version OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);//-/
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_DECORATED, true);
	glfwWindowHint(GLFW_ACCUM_RED_BITS, 8);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwSetGamma(glfwGetPrimaryMonitor(), 1.);

}

void App::SetWindowIcon(const char* path)
{
	GLFWimage icons;
	Resources::TemporaryTexture iconLoad = Resources::TemporaryTexture::TemporaryTexture(path, &icons.width, &icons.height, 0, 4);
	icons.pixels = iconLoad.m_pixels;
	if (icons.pixels)
	{
		glfwSetWindowIcon(m_window, 1, &icons);
	}
	else
	{
		std::cerr << "Failed to load Window Icon" << std::endl;
	}
}

void App::SetWindowCallbacks()
{
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwSetWindowIconifyCallback(m_window, window_iconify_callback);
	glfwSetWindowMaximizeCallback(m_window, window_maximize_callback);
}

void App::InitLibrary()
{
	// glad: load all OpenGL function pointers
	if (!InitLibGraph((GraphicsInitFunction)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return exit(-1);
	}
}

void App::InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return;
	}

	EnableBackFaceCulling();

	const char* glsl_version = "#version 450";
	/*INIT ImGUI*/
	//----------------------------------------------------------------------------------------------
	//Setup  Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ms_gameManager.MutateUI().InitFont();
	//Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//Setup Platform/Renderer bindigs
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	//------------------------------------------------------------------------------
}

void App::SetDeltaTime(const float time)
{
	m_delta = time - m_lastTime;
	m_lastTime = time;
}

void App::DisplayFPS()
{
	m_fpsDisplayTimer += m_delta;
	m_nbFrame++;

	if (m_fpsDisplayTimer >= 1.0f)
	{
		printf("%f ms/frame\n %d FPS\n", 1000.0 / double(m_nbFrame), m_nbFrame);
		m_fpsDisplayTimer = 0.0f;
		m_nbFrame = 0;
		return;
	}
}

void App::CleanBeforeExit()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	_CrtDumpMemoryLeaks();
}

void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
	App::SetWindowSize(width, height);
	App::GetGameManager().MutateScene().CalculateViewPort((float)height, (float)width);
}

void window_iconify_callback(GLFWwindow* window, int iconified)
{
	if (iconified)
	{
		glfwIconifyWindow(window);
	}
	else
	{
		glfwRestoreWindow(window);
	}
}

void window_maximize_callback(GLFWwindow* window, int maximized)
{
	if (maximized)
	{
		glfwMaximizeWindow(window);
	}
	else
	{
		glfwRestoreWindow(window);
	}
}