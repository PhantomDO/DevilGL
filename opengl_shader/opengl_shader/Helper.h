#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#else
#define _T(x) (x)
#endif

#ifndef WIN32
#include <fstream>
#include <sstream>
#endif


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

namespace Engine
{

	class Helper
	{
	public:
		static void Terminate(const std::string& err);
		static void RendererInfo();
		static const char* GetGLError();

#ifdef WIN32
		static std::string GetShaderSourceFromRessource(const std::wstring& filename);
#else
		static std::string GetShaderSourceFromRessource(const std::string& filename);
#endif

		static glm::vec3 HSVtoRGB(const glm::vec3& hsv)
		{
			int i;
			float f, p, q, t;
			glm::vec3 color;

			if (hsv.g == 0)
			{
				// achromatic (grey)
				color.r = color.g = color.b = hsv.b;
				return color;
			}

			float fH = hsv.r / 60; // sector 0 to 5
			i = static_cast<int>(floor(fH));
			f = fH - i;			// factorial part of m_fH
			p = hsv.b * (1 - hsv.g);
			q = hsv.b * (1 - hsv.g * f);
			t = hsv.b * (1 - hsv.g * (1 - f));

			switch (i)
			{
			case 0:
				color.r = hsv.b;
				color.g = t;
				color.b = p;
				break;
			case 1:
				color.r = q;
				color.g = hsv.b;
				color.b = p;
				break;
			case 2:
				color.r = p;
				color.g = hsv.b;
				color.b = t;
				break;
			case 3:
				color.r = p;
				color.g = q;
				color.b = hsv.b;
				break;
			case 4:
				color.r = t;
				color.g = p;
				color.b = hsv.b;
				break;
			default:		// case 5:
				color.r = hsv.b;
				color.g = p;
				color.b = q;
				break;
			}

			return color;
		}
	};
}
