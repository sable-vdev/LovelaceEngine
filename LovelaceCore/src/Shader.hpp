#pragma once
#include <inttypes.h>
#include <string>
#include <map>
#include <unordered_map>
#include <GLAD/glad.h>
#include "stb_image/stb_image.h"
#include "glm/glm.hpp"
#include "lovelacetypes.hpp"

class Shader
{
public:
	Shader();
	void Initialize(uint32_t shaderType, const std::string& source, uint32_t shaderType2, const std::string& source2);
	void Bind() const;
	void Unbind() const;
	void AddTexture(const std::string& path, const int id = 0);
	void SetUniform1i(const std::string& name, int x);
	void SetUniform1f(const std::string& name, float x);
	void SetUniform4f(const std::string& name, float x, float y, float z, float w); 
	void SetUniform4f(const std::string& name, glm::vec4 vector); 
	void SetUniform3f(const std::string& name, float x, float y, float z);
	void SetUniform3f(const std::string& name, glm::vec3 vector);
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat);
	void SetUniformMat3f(const std::string& name, const glm::mat3& mat);
	void ActivateTexture(const unsigned int id);
	inline uint32_t GetShaderId() const { return m_rendererId; };
private:
	bool ReadFile(const std::string& source, std::string& out);
	int GetUniformLocation(const std::string& name);
private:
	uint32_t m_rendererId;
	uint32_t m_amountOfTextures = 0;
	std::unordered_map<std::string, I32> m_uniformCache;
};
