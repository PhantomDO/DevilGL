#pragma once
#include <GL/glew.h>

namespace Engine
{

	class Time
	{
	public:
		static float deltaTime;
		static float lastFrame;

		Time() = default;
	};
}