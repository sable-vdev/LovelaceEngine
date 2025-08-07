#include "Window.hpp"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

class Input
{
public:
	Input(GLFWwindow* window);
	static bool GetKeyDown(int keyCode);
	glm::vec2 GetMousePos();
	void SetMouseVisibility(int command);
private:
	static GLFWwindow* m_window;
};