#pragma once
#include <cmath>
#include "FreeImagePlus.h"
#include <string>
#include <GL/glew.h>

#include "Debug.h"

struct Texture2D
{
	GLuint width, widthPow2;
	GLuint height, heightPow2;
	GLuint name;
	unsigned char* pixels;
	fipImage image;

	//virtual ~Texture2D()
	//{
	//	delete[] pixels;
	//}

	Texture2D(const std::string& path, const int& n = 0)
	{
		height = width = heightPow2 = widthPow2 = name = {};
		pixels = nullptr;

		glCreateTextures(GL_TEXTURE_2D, 1, &name);

		const bool dataLoaded = image.load(path.c_str());

		if (!dataLoaded)
		{
			Engine::Debug::LogError("Can't load this image.");
			return;
		}

		image.convertTo32Bits();

		width = image.getWidth();
		height = image.getHeight();

		pixels = image.accessPixels();

		//widthPow2 = 1 << static_cast<GLuint>(std::ceil(log2(static_cast<double>(width))));
		//heightPow2 = 1 << static_cast<GLuint>(std::ceil(log2(static_cast<double>(height))));

		//image.rescale(widthPow2, heightPow2, FILTER_BICUBIC);

		const int mipmapLevel = n <= 1 ? 1 : n;

		//glBindTextureUnit(n, name);

		glTextureStorage2D(name, mipmapLevel, GL_RGBA8, width, height);
		glTextureSubImage2D(name, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		Bind();

		if (mipmapLevel > 1) 
		{
			glGenerateTextureMipmap(name);
		}

		glTextureParameteri(name, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(name, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(name, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(name, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		Engine::Debug::Log("Texture loaded");
	}

	void Bind(const int& n = 0) const
	{
		glBindTextureUnit(n, name);
	}
};
