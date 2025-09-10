#pragma once
#include "glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

enum LightMode
{
	DirectionalLight = 0,
	PointLight = 1,
	//Spotlight = 2
};

struct Light
{
	const float attenuationConstant = 1.0f;
	float attenuationLinear = 0.09f;
	float attenuationQuadratic = 0.032f;

	int lightMode = LightMode::DirectionalLight;

	glm::vec3 position = glm::vec3(1.2f, 1.0f, 2.0f);
	glm::vec3 rotation = glm::vec3(1.0, -1.0, -0.3);  //sun?
	glm::vec3 ambient = glm::vec3(0.5f);
	glm::vec3 diffuse  = glm::vec3(0.2f);
	glm::vec3 specular = glm::vec3(1.0f);

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	inline void ModelUpdate()
	{
		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, position);
	}

	inline void ChangeToSpotlight()
	{
		glm::vec3 ambient = glm::vec3(0.1f);
		glm::vec3 diffuse = glm::vec3(0.8f);
		glm::vec3 specular = glm::vec3(1.0f);
	}

	inline void ChangeToPointLight()
	{
		glm::vec3 ambient = glm::vec3(0.5f);
		glm::vec3 diffuse = glm::vec3(0.2f);
		glm::vec3 specular = glm::vec3(1.0f);
	}

	inline void ChangeToDirectionalLight()
	{
		glm::vec3 ambient = glm::vec3(0.5f);
		glm::vec3 diffuse = glm::vec3(0.2f);
		glm::vec3 specular = glm::vec3(1.0f);
	}
};