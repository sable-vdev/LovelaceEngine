#include "Camera.hpp"

Camera::Camera(const float width, const float height) : m_width(width), m_height(height)
{
    m_viewMatrix = glm::lookAt(m_position, m_position + m_cameraFront, m_up);
    m_aspect = width / height;

    m_lastMouseX = width / 2.0f;
    m_lastMouseY = height / 2.0f;

    m_projectionMatrix = glm::perspective(m_cameraFOV, m_aspect, m_cameraNear, m_cameraFar);
}

void Camera::RenderImGui()
{
    ImGui::Begin("Camera");
    ImGui::Checkbox("Orthographic Camera", &ortho);
    ImGui::DragFloat3("Position", &m_position.x, 0.1f);
    ImGui::DragFloat3("Rotation", &m_rotation.x, 0.1f);
    ImGui::DragFloat("FOV", &m_cameraFOV);
    ImGui::DragFloat("Near", &m_cameraNear);
    ImGui::DragFloat("Far", &m_cameraFar);
    ImGui::End();
}

void Camera::UpdateCamera(Input& input, const Window& window)
{
    m_cameraRight = glm::normalize(glm::cross(m_up, m_cameraFront));

    mousePos = Input::GetMousePos();

    m_viewMatrix = glm::lookAt(m_position, m_position + m_cameraFront, m_up);

    if (ortho)
    {
        m_projectionMatrix = glm::ortho(0.0f, m_width, 0.0f, m_height, m_cameraNear, m_cameraFar);
        m_rotation.x = 0.0f;
    }
    else
    {
        m_projectionMatrix = glm::perspective(m_cameraFOV, m_aspect, m_cameraNear, m_cameraFar);
    }

    if (Input::GetKeyDown(1))
    {
        Input::SetMouseVisibility(GLFW_CURSOR_DISABLED);

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

        m_rotation.y = std::clamp(m_rotation.y, -89.0f, 89.0f);
        
        glm::vec3 dir(0.0f);
        dir.x = cos(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
        dir.y = sin(glm::radians(m_rotation.y));
        dir.z = cos(glm::radians(m_rotation.y)) * sin(glm::radians(m_rotation.x));

        m_cameraFront = glm::normalize(dir);

        if (Input::GetKeyDown(GLFW_KEY_A))
        {
            m_position += m_cameraSpeed * window.GetDeltaTime() * m_cameraRight;
        }
        if (Input::GetKeyDown(GLFW_KEY_D))
        {
            m_position -= m_cameraSpeed * window.GetDeltaTime() * m_cameraRight;
        }
        if (Input::GetKeyDown(GLFW_KEY_W))
        {
            m_position += m_cameraSpeed * window.GetDeltaTime() * m_cameraFront;
        }
        if (Input::GetKeyDown(GLFW_KEY_S))
        {
            m_position -= m_cameraSpeed * window.GetDeltaTime() * m_cameraFront;
        }
        if (Input::GetKeyDown(GLFW_KEY_SPACE))
        {
            m_position += m_cameraSpeed * window.GetDeltaTime() * m_up;
        }
        if (Input::GetKeyDown(GLFW_KEY_LEFT_CONTROL))
        {
            m_position -= m_cameraSpeed * window.GetDeltaTime() * m_up;
        }
        if (Input::GetKeyDown(GLFW_KEY_LEFT_SHIFT))
        {
            m_cameraSpeed = 20.0f;
        }
        else
        {
            m_cameraSpeed = 10.0f;
        }
    }
    else if (!Input::GetKeyDown(1))
    {
        Input::SetMouseVisibility(GLFW_CURSOR_NORMAL);
        m_firstMouse = true;
    }
}
/*
void Camera::UpdateCamera()
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
        float yOffset = sensitivity * (m_lastMouseY - mousePos.y);
        m_lastMouseX = mousePos.x;
        m_lastMouseY = mousePos.y;

        m_rotation.x += xOffset;
        m_rotation.y += yOffset;

        if (m_rotation.y > 89.0f)
            m_rotation.y = 89.0f;
        if (m_rotation.y < -89.0f)
            m_rotation.y = -89.0f;

        glm::vec3 dir(0.0f);
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
*/