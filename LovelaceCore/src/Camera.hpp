#pragma once
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "Input.hpp"

class Camera
{
public:
	Camera(const float width, const float height);
	void UpdateCamera(Input& input, const Window& window);
	//void UpdateCamera();
	inline glm::mat4 GetMatrix() const { return m_projectionMatrix * m_viewMatrix; }
	inline glm::vec3 GetPosition() const { return m_position; }
	void RenderImGui();
	bool ortho = false;
private:
	float m_cameraSpeed = 15.0f;
	float m_cameraNear = 0.01f;
	float m_cameraFar = 1000.0f;
	float m_cameraFOV = 45.0f;
	float m_aspect = 1.9f;
	float m_width;
	float m_height;
	float m_lastMouseX = 1920 / 2.0f;
	float m_lastMouseY = 1080 / 2.0f;
	bool m_firstMouse = true;
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 m_rotation = glm::vec3(-89.0f, 0.0f, 0.0f);
	glm::vec3 m_cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 m_viewMatrix = glm::mat4(1.0f);
	glm::mat4 m_projectionMatrix = glm::perspective(m_cameraFOV, m_aspect, m_cameraNear, m_cameraFar);
	glm::vec2 mousePos = glm::vec2(0.0f);
};