#include "Input.hpp"

GLFWwindow* Input::m_window = nullptr;

Input::Input(GLFWwindow* window)
{
    m_window = window;}

bool Input::GetKeyDown(int keyCode)
{
    if (keyCode == GLFW_MOUSE_BUTTON_RIGHT || keyCode == GLFW_MOUSE_BUTTON_LEFT)
    {
        return glfwGetMouseButton(m_window, keyCode);
    }

    return glfwGetKey(m_window, keyCode) == GLFW_PRESS;
}

glm::vec2 Input::GetMousePos()
{
    glm::vec2 mousePos(0.0f);
    double x, y;
    glfwGetCursorPos(m_window, &x, &y);
    mousePos.x = static_cast<float>(x);
    mousePos.y = static_cast<float>(y);
    return mousePos;
}

void Input::SetMouseVisibility(int command)
{
    glfwSetInputMode(m_window, GLFW_CURSOR, command);
}