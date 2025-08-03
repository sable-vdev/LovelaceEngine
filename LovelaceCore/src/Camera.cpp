#include "Camera.hpp"

Camera::Camera()
{
    viewMatrix = glm::lookAt(m_position, m_position + m_cameraFront, m_up);
}
Camera::Camera(float degrees, float aspect, float near, float far)
{
}
void Camera::UpdateCamera(Window& window)
{
    m_cameraRight = glm::normalize(glm::cross(m_up, m_cameraFront));

    mousePos = window.GetMousePos();

    viewMatrix = glm::lookAt(m_position, m_position + m_cameraFront, m_up);
    if (window.GetKeyDown(1))
    {
        window.SetMouseVisibility(GLFW_CURSOR_DISABLED);

        if (m_firstMouse)
        {
            m_lastMouseX = mousePos.x;
            m_lastMouseY = mousePos.y;

            m_firstMouse = false;
        }
        float sensitivity = 0.1f;
        float xOffset = sensitivity * (mousePos.x - m_lastMouseX);
        float yOffset = sensitivity * (m_lastMouseY- mousePos.y);
        m_lastMouseX = mousePos.x;
        m_lastMouseY = mousePos.y;

        m_rotation.x += xOffset;
        m_rotation.y += yOffset;

        if (m_rotation.y > 89.0f)
            m_rotation.y = 89.0f;
        if (m_rotation.y < -89.0f)
            m_rotation.y = -89.0f;

        glm::vec3 dir;
        dir.x = cos(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
        dir.y = sin(glm::radians(m_rotation.y));
        dir.z = cos(glm::radians(m_rotation.y)) * sin(glm::radians(m_rotation.x));

        m_cameraFront = glm::normalize(dir);

        if (window.GetKeyDown(GLFW_KEY_A))
        {
            m_position += m_cameraSpeed * window.GetDeltaTime() * m_cameraRight;
        }
        if (window.GetKeyDown(GLFW_KEY_D))
        {
            m_position -= m_cameraSpeed * window.GetDeltaTime() * m_cameraRight;
        }
        if (window.GetKeyDown(GLFW_KEY_W))
        {
            m_position += m_cameraSpeed * window.GetDeltaTime() * m_cameraFront;
        }
        if (window.GetKeyDown(GLFW_KEY_S))
        {
            m_position -= m_cameraSpeed * window.GetDeltaTime() * m_cameraFront;
        }
        if (window.GetKeyDown(GLFW_KEY_SPACE))
        {
            m_position += m_cameraSpeed * window.GetDeltaTime() * m_up;
        }
        if (window.GetKeyDown(GLFW_KEY_LEFT_CONTROL))
        {
            m_position -= m_cameraSpeed * window.GetDeltaTime() * m_up;
        }
        if (window.GetKeyDown(GLFW_KEY_LEFT_SHIFT))
        {
            m_cameraSpeed = 60.0f;
        }
        else
        {
            m_cameraSpeed = 30.0f;
        }
    }
    else if (!window.GetKeyDown(1))
    {
        window.SetMouseVisibility(GLFW_CURSOR_NORMAL);
        m_firstMouse = true;
    }
}