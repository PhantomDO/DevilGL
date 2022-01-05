#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Helper.h"
#include "Window.h"

namespace Engine
{

	class Input
	{
	public:
		static void CursorPosCallback(GLFWwindow* pWindow, double x, double y);

		static void GetKeyDown(GLFWwindow* pWindow, int key, int scanCode, int action, int mods);

		static void GetScrolling(GLFWwindow* pWindow, double x, double y);

		static void GetSize(GLFWwindow* pWindow, int width, int height);
	};
}
