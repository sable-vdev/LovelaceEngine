#include "Camera.hpp"

Camera::Camera() : position(glm::vec3(0.0f, 0.0f, -5.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
    viewMatrix(glm::mat4(1.0f))
{
    viewMatrix = glm::translate(glm::mat4(1.0f), position);
}

void Camera::UpdateCamera(Window* window)
{
    viewMatrix = glm::translate(glm::mat4(1.0f), position);

    if (window->GetKeyDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
        if (window->GetKeyDown(GLFW_KEY_A))
        {
            position.x += 15.0f * window->GetDeltaTime();
        }
        if (window->GetKeyDown(GLFW_KEY_D))
        {
            position.x -= 15.0f * window->GetDeltaTime();
        }
        if (window->GetKeyDown(GLFW_KEY_W))
        {
            position.z += 15.0f * window->GetDeltaTime();
        }
        if (window->GetKeyDown(GLFW_KEY_S))
        {
            position.z -= 15.0f * window->GetDeltaTime();
        }
    }

}