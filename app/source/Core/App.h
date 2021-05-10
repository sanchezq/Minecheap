
class GameManager;
struct GLFWwindow;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void window_iconify_callback(GLFWwindow* window, int iconified);
void window_maximize_callback(GLFWwindow* window, int maximized);

class App
{
public:
	// Constructor and destructor
	App() = delete;
	App(const App& other) = delete;
	App& operator=(const App& other) = delete;
	App(const int windowWidth, const int windowHeight, const char* windowName, const char* iconPath, const bool vsync = true);
	~App();

	// Instance
	static GameManager& GetGameManager();

	static void SetWindowSize(const int width, const int height);

	void Run();

private:
	// Init App
	void InitGLFW(const char* windowName);
	void ConfigGLFW();
	void SetWindowIcon(const char* path);
	void SetWindowCallbacks();
	void InitLibrary();
	void InitGlad();
	void CleanBeforeExit();

	void SetDeltaTime(const float time);
	void DisplayFPS();

	static GameManager ms_gameManager;

	GLFWwindow* m_window = nullptr;
	static int ms_windowWidth;
	static int ms_windowHeight;

	float m_lastTime = 0.f;
	float m_delta = 0.f;
	
	float m_fpsDisplayTimer = 0.0f;
	int m_nbFrame =0;
};