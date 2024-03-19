#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace ngl
{
	void InitContext(int major = 4, int minor = 5);
	void ResizeWindow(GLFWwindow* window, int width, int height);

	inline bool CheckError();
	inline void ClearErrors();

	void BreakOnError();

	class Window
	{
	public:

		Window() = delete;
		Window(int width = 800, int height = 600, const char* title = "Hello OpenGL");

		bool ShouldClose() const;

		operator bool() const;

		void Clear();
		void Clear(float r, float g, float b);

		GLFWwindow* m_ptr = nullptr;
	};
}