#include "Helper.h"

#include "Debug.h"

void Helper::Terminate(const std::string& err)
{
	Debug::LogError(err);
	glfwTerminate();
	std::exit(EXIT_FAILURE);
}

void Helper::RendererInfo()
{
	const char* glString;
	std::stringstream ss;

	glString = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	if(!glString) glString = GetGLError();
	ss << "Company : " << glString << std::endl;
	
	glString = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	if(!glString) glString = GetGLError();
	ss << "Renderer : " << glString << std::endl;
	
	glString = reinterpret_cast<const char*>(glGetString(GL_VERSION));
	if(!glString) glString = GetGLError();
	ss << "Version : " << glString << std::endl;

	Debug::Log(ss.str());
}

const char* Helper::GetGLError()
{
	switch(glGetError())
	{
	case GL_NO_ERROR:
	  return "GL_NO_ERROR";
	case GL_INVALID_ENUM:
	  return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE:
	  return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION:
	  return "GL_INVALID_OPERATION";
	case GL_STACK_OVERFLOW:
	  return "GL_STACK_OVERFLOW";
	case GL_STACK_UNDERFLOW:
	  return "GL_STACK_UNDERFLOW";
	case GL_OUT_OF_MEMORY:
	  return "GL_OUT_OF_MEMORY";
	default: ;
	  //case GL_INVALID_FRAMEBUFFER_OPERATION?:
	  //	return "GL_INVALID_FRAMEBUFFER_OPERATION???";
	  //case GL_TABLE_TOO_LARGE?:
	  //	return "GL_TABLE_TOO_LARGE???";
	}

	return "UNKNOWN ERROR";
}

#ifdef WIN32
std::string Helper::GetShaderSourceFromRessource(const std::wstring& filename)
{
	const HRSRC hrSrc = FindResource(nullptr, filename.c_str(), _T("SHADERS"));
	const HGLOBAL hRes = LoadResource(nullptr, hrSrc);
	DWORD szRes = SizeofResource(nullptr, hrSrc);
	return std::string{ reinterpret_cast<const char*>(LockResource(hRes)), szRes };
}
#else
std::string Helper::GetShaderSourceFromRessource(const std::string& filename)
{
	const std::ifstream shaderFile{ filename };
	if(!shaderFile.is_open()) return std::string{};

	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
	return shaderStream.str();
}
#endif

