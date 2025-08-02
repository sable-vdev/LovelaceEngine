#include "Camera.hpp"

Camera::Camera() 
    : m_position(glm::vec3(0.0f, 0.0f, 15.0f)), m_rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
    viewMatrix(glm::mat4(1.0f))
{
    viewMatrix = glm::lookAt(m_position, m_position + m_orientation, m_up);
}
Camera::Camera(float degrees, float aspect, float near, float far)
    : m_position(glm::vec3(0.0f, 0.0f, 15.0f)), m_rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
    viewMatrix(glm::mat4(1.0f))
{

}
void Camera::UpdateCamera(Window* window)
{
    viewMatrix = glm::lookAt(m_position, m_position + m_orientation, m_up);
    if (window->GetKeyDown(1))
    {
        window->SetMouseVisibility(GLFW_CURSOR_DISABLED);

        if (window->GetKeyDown(GLFW_KEY_A))
        {
            m_position += m_cameraSpeed * window->GetDeltaTime() * -glm::normalize(glm::cross(m_orientation, m_up));
        }
        if (window->GetKeyDown(GLFW_KEY_D))
        {
            m_position += m_cameraSpeed * window->GetDeltaTime() * glm::normalize(glm::cross(m_orientation, m_up));
        }
        if (window->GetKeyDown(GLFW_KEY_W))
        {
            m_position += m_cameraSpeed * window->GetDeltaTime() * m_orientation;
        }
        if (window->GetKeyDown(GLFW_KEY_S))
        {
            m_position -= m_cameraSpeed * window->GetDeltaTime() * m_orientation;
        }
        if (window->GetKeyDown(GLFW_KEY_SPACE))
        {
            m_position += m_cameraSpeed * window->GetDeltaTime() * m_up;
        }
        if (window->GetKeyDown(GLFW_KEY_LEFT_CONTROL))
        {
            m_position -= m_cameraSpeed * window->GetDeltaTime() * m_up;
        }
        if (window->GetKeyDown(GLFW_KEY_LEFT_SHIFT))
        {
            m_cameraSpeed = 60.0f;
        }
        else
        {
            m_cameraSpeed = 30.0f;
        }
    }
    else if (!window->GetKeyDown(1))
    {
        window->SetMouseVisibility(GLFW_CURSOR_NORMAL);
    }
}