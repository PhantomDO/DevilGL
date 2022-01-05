#pragma once
#include <ostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Engine
{
	struct Bounds
	{
		glm::vec3 center;
		glm::vec3 extends;
		glm::vec3 size;
		glm::vec3 min;
		glm::vec3 max;

		Bounds()
		{
			center = glm::vec3{ 0, 0, 0 };
			size = glm::vec3{ 0, 0, 0 };
			extends = size / 2.f;
			min = center - extends;
			max = center + extends;
		}

		Bounds(const glm::vec3& center, const glm::vec3& size)
			: center(center), extends(size / 2.f), size(size),
			min(center - (size / 2.f)), max(center + (size / 2.f))
		{
		}

		bool Contains(const glm::vec3& v) const
		{
			//std::cout << v << ", " << min << ", " << max << std::endl;
			return	v.x >= min.x && v.x <= max.x &&
				v.y >= min.y && v.y <= max.y &&
				v.z >= min.z && v.z <= max.z;
		}

		bool Contains(glm::vec3& v)
		{
			//std::cout << v << ", " << min << ", " << max << std::endl;
			return	v.x >= min.x && v.x <= max.x &&
				v.y >= min.y && v.y <= max.y &&
				v.z >= min.z && v.z <= max.z;
		}

		friend bool operator<(const Bounds& l, const Bounds& r)
		{
			return	glm::length(l.size) * glm::length(l.size) < glm::length(r.size) * glm::length(r.size);
		}

		friend std::ostream& operator <<(std::ostream& os, const Bounds& b)
		{
			os << "Bounds (Center: (" << b.center.x << ", " << b.center.y << ", " << b.center.z
				<< "), Extends: (" << b.extends.x << ", " << b.extends.y << ", " << b.extends.z << "))";
			return os;
		}

	};
}
