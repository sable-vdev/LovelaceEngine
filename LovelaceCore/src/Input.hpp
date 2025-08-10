#pragma once
#include "Window.hpp"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

class Input
{
public:
	Input(GLFWwindow* window);
	static bool GetKeyDown(const int keyCode);
	static glm::vec2 GetMousePos();
	static void SetMouseVisibility(const int command);
private:
	static GLFWwindow* m_window;
};