#include <fstream>
#include <iostream>
#include "Shader.hpp"
#include "Logger.hpp"


Shader::Shader() : m_rendererId(glCreateProgram())
{
}

void Shader::Initialize(const uint32_t shaderType, const std::string& source, const uint32_t shaderType2, const std::string& source2)
{
	const uint32_t shader1 = glCreateShader(shaderType);
	const uint32_t shader2 = glCreateShader(shaderType2);

	std::string out;
	ReadFile(source, out);

	const char* p = out.c_str();

	int length = static_cast<int>(strlen(out.c_str()));

	glShaderSource(shader1, 1, &p, &length);
	glCompileShader(shader1);

	int result = 0;
	glGetShaderiv(shader1, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(shader1, GL_INFO_LOG_LENGTH, &length);
		char* message = static_cast<char*>(malloc(length * sizeof(char)));
		glGetShaderInfoLog(shader1, length, &length, message);
		Logger::Log(ERROR, message != nullptr ? message : "0");
		glDeleteShader(shader1);
		free(message);
	}

	out = "";
	ReadFile(source2, out);

	const char* p2 = out.c_str();

	length = static_cast<int>(strlen(out.c_str()));

	glShaderSource(shader2, 1, &p2, &length);
	glCompileShader(shader2);

	result = 0;
	glGetShaderiv(shader2, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(shader2, GL_INFO_LOG_LENGTH, &length);
		char* message = static_cast<char*>(malloc(length * sizeof(char)));
		glGetShaderInfoLog(shader2, length, &length, message);
		Logger::Log(ERROR, message != nullptr ? message : "0");
		glDeleteShader(shader2);
		free(message);
	}

	glAttachShader(m_rendererId, shader1);
	glAttachShader(m_rendererId, shader2);
	glLinkProgram(m_rendererId);

	//delete p2;
	glDeleteShader(shader1);
	glDeleteShader(shader2);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::Bind() const
{
	glUseProgram(m_rendererId);
}

void Shader::AddTexture(const std::string& path, const int id)
{
	uint32_t texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	uint32_t colorFormat = 0;
	if (nrChannels == 4) colorFormat = GL_RGBA;
	else if (nrChannels == 3) colorFormat = GL_RGB;
	else Logger::Log(ERROR, "Did not provide a supported texture format");

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		Logger::Log(ERROR, "Failed to load texture");
	}

	stbi_image_free(data);
	m_amountOfTextures++;
}

void Shader::SetUniform1i(const std::string& name, int x)
{
	if (GetUniformLocation(name) != -1)
	{
		glUniform1i(m_uniformCache[name], x);
	}
}

void Shader::SetUniform1f(const std::string& name, float x)
{
	if (int i = GetUniformLocation(name) != -1)
	{
		glUniform1f(i, x);
	}
}

void Shader::SetUniform4f(const std::string& name, float x, float y, float z, float w)
{
	if (int i = GetUniformLocation(name) != -1)
	{
		glUniform4f(i, x, y, z, w);
	}
}

void Shader::SetUniform4f(const std::string& name, glm::vec4 vector)
{
	if (int i = GetUniformLocation(name) != -1)
	{
		glUniform4f(i, vector.x, vector.y, vector.z, vector.w);
	}
}

void Shader::SetUniform3f(const std::string& name, float x, float y, float z)
{
	glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetUniform3f(const std::string& name, glm::vec3 vector) 
{
	glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat) 
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetUniformMat3f(const std::string& name, const glm::mat3& mat)
{
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_uniformCache.find(name) != m_uniformCache.end()) return m_uniformCache[name];
	int location = glGetUniformLocation(m_rendererId, name.c_str());

	if (location != -1)
	{
		m_uniformCache[name] = location;
	}
	//else Logger::Log(WARNING, "Couldn't find uniform location of uniform: " + name);
	
	return location;
}

void Shader::ActivateTexture(const unsigned int id)
{
	glActiveTexture(GL_TEXTURE0 + id);
}

bool Shader::ReadFile(const std::string& source, std::string& out)
{
	std::ifstream shaderSource(source);
	if (shaderSource.is_open())
	{
		std::string line;
		while (getline(shaderSource, line))
		{
			out.append(line);
			out.append("\n");
		}

		shaderSource.close();
	}
	else return false;

	return true;
}