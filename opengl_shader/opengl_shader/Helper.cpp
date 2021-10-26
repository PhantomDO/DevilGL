#include "Helper.h"

void Helper::Terminate(const std::string& err)
{
	std::cerr << err << std::endl;
	glfwTerminate();
	std::exit(EXIT_FAILURE);
}

void Helper::RendererInfo()
{
	const char* glString;

	glString = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	if(!glString) glString = GetGLError();
	std::cout << "Company : " << glString << std::endl;
	
	glString = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	if(!glString) glString = GetGLError();
	std::cout << "Renderer : " << glString << std::endl;
	
	glString = reinterpret_cast<const char*>(glGetString(GL_VERSION));
	if(!glString) glString = GetGLError();
	std::cout << "Version : " << glString << std::endl;
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

void Helper::ShaderCompilationTest(GLint vertexShader)
{
	GLint isCompiled;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		for (auto& i : infoLog)
			std::cout << i;
	}
}

void Helper::ProgramShaderLinkedTest(GLint program, GLint vertexShader, GLint fragmentShader)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
	}
}

std::string Helper::ReadShaderFile(const char* shader)
{
	// lis le fichier 
	std::ifstream file(shader);
	if (!file) return std::string();

	size_t size = file.gcount();

	// remet les caract�re au d�part du fichier
	file.clear();
	file.seekg(0, std::ios_base::beg);

	// copie les caract�re dans le string stream
	std::stringstream sstr;
	sstr << file.rdbuf();
	file.close();

	// renvoie une string du string stream pass�
	return sstr.str();
}
