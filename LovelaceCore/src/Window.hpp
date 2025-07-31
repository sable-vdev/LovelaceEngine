#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
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
	std::string m_title;
	bool m_vsync;
	GLFWwindow* m_window;
	float m_deltaTime;
	float m_lastTime;
	float m_applicationRunTime;
public:
	Window();
	Window(int32_t widht, int32_t height, const char* title, bool vsync);
	bool Run();
	void Destroy();
	void SwapBuffers();
	bool Timer();
	bool GetKeyDown(int keyCode);
	inline float GetDeltaTime() const { return m_deltaTime; };
	inline float GetApplicationRunTime() const { return m_applicationRunTime; };
	inline float GetWidth() const { return (float)m_width; }
	inline float GetHeight() const { return (float)m_height; }
private:
	bool Initialize();

	static inline void FrameBufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (win)
		{
			win->m_height = height;
			win->m_width = width;
			Logger::Log(DEBUG, "Resized to width: " + std::to_string(width) + "height: " + std::to_string(height));
		}
	}
};