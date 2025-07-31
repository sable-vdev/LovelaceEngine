#include "Window.hpp"

Window::Window()
    : m_window(nullptr), m_width(1280), m_height(720), m_title("Lovelace Render Engine"), m_vsync(false)
{
    if (!Initialize())
    {
        Logger::Log(ERROR, "Failed to initialize the glfw window");
        exit(-1);
        m_lastTime = (float)glfwGetTime();
    }
    Logger::Log(INFO, "Window created.");
}

Window::Window(int32_t width, int32_t height, const char* title, bool vsync)
    : m_window(nullptr), m_width(width), m_height(height), m_title(title), m_vsync(vsync)
{
    if (!Initialize())
    {
        Logger::Log(ERROR, "Failed to initialize the glfw window");
        exit(-1);
    }
    Logger::Log(INFO, "Window created.");
}

bool Window::Initialize()
{
    if (!glfwInit())
    {
        Logger::Log(ERROR, "Failed to initialize GLFW");
        return false;
    }
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidmode = glfwGetVideoMode(primaryMonitor);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    
    if (!m_window)
    {
        Logger::Log(ERROR, "Failed to initialize window");
        glfwTerminate();
        return false;
    }

    glfwMaximizeWindow(m_window);
    glfwGetWindowSize(m_window, &m_width, &m_height);

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);

    if (glewInit() != GLEW_OK)
    {
        Logger::Log(ERROR, "Failed to initialize GLEW");
        return false;
    }

    if (m_vsync) glfwSwapInterval(1);
    else glfwSwapInterval(0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    return true;
}

bool Window::Timer()
{
    float currentTime = (float)glfwGetTime();
    m_deltaTime = currentTime - m_lastTime;

    m_lastTime = currentTime;

    return false;
}

bool Window::GetKeyDown(int keyCode)
{
    if (keyCode == GLFW_MOUSE_BUTTON_RIGHT || keyCode == GLFW_MOUSE_BUTTON_LEFT)
    {
        return glfwGetMouseButton(m_window, keyCode);
    }
    //Logger::Log(DEBUG, std::to_string(glfwGetKey(m_window, keyCode) == GLFW_PRESS));
    return glfwGetKey(m_window, keyCode) == GLFW_PRESS;
}

bool Window::Run()
{
    
    if (glfwWindowShouldClose(m_window)) return false;
    
    glViewport(0, 0, m_width, m_height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwPollEvents();

    Timer();

    m_applicationRunTime += m_deltaTime;
    return true;
}

void Window::Destroy()
{
    glfwTerminate();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    Logger::Log(DEBUG, "Destroyed the window.");
}
void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}