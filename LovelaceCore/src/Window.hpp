#pragma once
#define GLAD_GL_IMPLEMENTATION
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <iostream>
#include "Logger.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class Window
{
private:
	int32_t m_width;
	int32_t m_height;
	float m_deltaTime;
	float m_lastTime;
	const char* m_title;
	GLFWwindow* m_window;
	float m_applicationRunTime;
	bool m_vsync;
public:
	Window();
	Window(int32_t width, int32_t height, const char* title, bool vsync);
	bool Run();
	void Destroy();
	void SwapBuffers();
	void Timer();
	inline float GetDeltaTime() const { return m_deltaTime; };
	inline float GetApplicationRunTime() const { return m_applicationRunTime; };
	inline float GetWidth() const { return (float)m_width; }
	inline float GetHeight() const { return (float)m_height; }
	inline GLFWwindow* GetWindow() const { return m_window; }
private:
	bool Initialize();
	static inline void FrameBufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (win)
		{
			win->m_height = height;
			win->m_width = width;
		}
	}
};