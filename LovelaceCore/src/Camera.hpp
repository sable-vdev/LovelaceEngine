#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "Window.hpp"

class Camera
{
public:
	Camera();
	Camera(float degrees, float aspect, float near, float far);
	void UpdateCamera(Window* window);
	inline glm::mat4 GetMatrix() const { return m_projectionMatrix * viewMatrix; };
private:
public:
private:
	float m_cameraMoveSpeed = 15.0f;
	float m_cameraNear = 0.01f;
	float m_cameraFar = 1000.0f;
	float m_cameraFOV = 45.0f;
	float m_aspect = 1.9;
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 15.0f);
	glm::vec3 m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 m_projectionMatrix = glm::perspective(m_cameraFOV, m_aspect, m_cameraNear, m_cameraFar);
};