#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "Window.hpp"

class Camera
{
public:
	Camera();
	void UpdateCamera(Window* window);
private:
public:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, -5.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
private:
};