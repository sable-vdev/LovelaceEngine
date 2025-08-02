#pragma once
#include <inttypes.h>
#include <string>
#include <GLEW/glew.h>
#include "glm/glm.hpp"

class Shader
{
public:
	Shader();
	void Initialize(uint32_t shaderType, const std::string& source, uint32_t shaderType2, const std::string& source2);
	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const std::string& name, float x, float y, float z, float w) const; 
	void SetUniform3f(const std::string& name, float x, float y, float z) const;
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat) const;
	int GetUniformLocation(const std::string& name) const;
	inline uint32_t GetShaderId() const { return m_rendererId; };
private:
	bool ReadFile(const std::string& source, std::string& out);
private:
	uint32_t m_rendererId;
};
