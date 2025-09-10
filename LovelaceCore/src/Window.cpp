#include "Window.hpp"
#include "stb_image.hpp"
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
    Logger::Log(INFO, "Initialized GLFW");
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidmode = glfwGetVideoMode(primaryMonitor);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    
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
    
    int width, height, nrChannels;

    unsigned char* icon = stbi_load("../LovelaceCore/resources/Ada_icon.png", &width, &height, &nrChannels, 0);

    if (!icon)
    {
        std::cout << stbi_failure_reason();
        exit(-1);
    }

    GLFWimage image{};
    image.height = height;
    image.width = width;
    image.pixels = icon;

    glfwSetWindowIcon(m_window, 1, &image);
    stbi_image_free(icon);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
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

void Window::Timer()
{
    float currentTime = (float)glfwGetTime();
    m_deltaTime = currentTime - m_lastTime;

    m_lastTime = currentTime;
}

bool Window::Run()
{
    if (glfwWindowShouldClose(m_window)) return false;
    Timer();
    
    glViewport(0, 0, m_width, m_height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwPollEvents();


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