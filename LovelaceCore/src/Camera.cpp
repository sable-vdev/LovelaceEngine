#include "Camera.hpp"

Camera::Camera() : m_position(glm::vec3(0.0f, 0.0f, 15.0f)), m_rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
    viewMatrix(glm::mat4(1.0f))
{
    viewMatrix = glm::lookAt(m_position, m_position + m_orientation, m_up);
}
Camera::Camera(float degrees, float aspect, float near, float far)
{

}
void Camera::UpdateCamera(Window* window)
{
    viewMatrix = glm::lookAt(m_position, m_position + m_orientation, m_up);
    if (window->GetKeyDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
        window->SetMouseVisibility(GLFW_CURSOR_DISABLED);

        if (window->GetKeyDown(GLFW_KEY_A))
        {
            m_position.x -= 15.0f * window->GetDeltaTime();
        }
        if (window->GetKeyDown(GLFW_KEY_D))
        {
            m_position.x += 15.0f * window->GetDeltaTime();
        }
        if (window->GetKeyDown(GLFW_KEY_W))
        {
            m_position.z -= 15.0f * window->GetDeltaTime();
        }
        if (window->GetKeyDown(GLFW_KEY_S))
        {
            m_position.z += 15.0f * window->GetDeltaTime();
        }
    }
    else if (!window->GetKeyDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
        window->SetMouseVisibility(GLFW_CURSOR_NORMAL);
    }
}