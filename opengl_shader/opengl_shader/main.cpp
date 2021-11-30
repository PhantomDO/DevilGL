#include <iostream>
#include <string>

#include "Entity.h"
#include "GameEntity.h"
#include "Helper.h"
#include "Input.h"
#include "Light.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Window.h"

//#ifdef WIN32
//This magic line is to force notebook computer that share NVidia and Intel graphics to use high performance GPU (NVidia).
//Intel graphics doesn't support OpenGL > 1.2
extern "C" _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
//#endif

const GLfloat PI = 3.1415926535897932384626433832795f;

int main( int argc, char * argv[])
{
#ifdef WIN32
  //Passe la console en UTF-8, permettant d'afficher les accents.
  //Tous les fichiers de cette solution sont encodés en UTF-8.
	SetConsoleOutputCP(65001);
#endif
	const int window_width = 800;
	const int window_height = 600;
	Window* window = new Window(window_width, window_height, false);

	// pointeur sur les touche du claver
	glfwSetKeyCallback(window->GetWindowPtr(), Input::GetKeyDown);
	//glfwSetScrollCallback(window->GetWindowPtr(), Input::GetScrolling);
	glfwSetWindowSizeCallback(window->GetWindowPtr(), Input::GetSize);

	// COLOR
	glm::vec3* background = new glm::vec3(0.33f, 1.0f, 1.0f);
	auto orange = glm::vec3(0.39f, 1.0f, 1.0f);
	auto blue = glm::vec3(1.0f, 1.0f, 1.0f);	
	glClearColor(background->r,	background->g,	background->b,	1.0f);

	// mesh
	std::vector<std::string> meshPaths;
	auto meshList = Tools::ChoiceListFromDirectory("./models", meshPaths);
	std::vector<std::string> texturePaths;
	auto textureList = Tools::ChoiceListFromDirectory("./textures", texturePaths);

	int count;
	std::vector<std::shared_ptr<GameEntity>> entities;
	std::cout << "How many entities do you want ?";
	std::cin >> count;
	entities.reserve(count);
	for (int i = 0; i < count; ++i)
	{
		auto entity = std::make_shared<GameEntity>();

		if (!meshPaths.empty()) 
		{
			int meshChoice = -1;
			while (meshChoice <= -1)
			{
				Debug::Log(meshList);
				std::cin >> meshChoice;
			}

			Debug::Log(meshPaths[meshChoice]);
			auto mr = std::make_shared<MeshRenderer>();			
			mr->SetMesh(Mesh(meshPaths[meshChoice]));
			
			if (!texturePaths.empty())
			{
				int texChoice = -1;
				while (texChoice <= -1)
				{
					Debug::Log(textureList);
					std::cin >> texChoice;
				}

				Debug::Log(texturePaths[texChoice]);
				mr->AddTexture(Texture2D(texturePaths[texChoice]));
			}

			entity->AddComponent(mr);
		}

		entities.emplace_back(entity);
	}

	window->SetMeshProgram(ShaderProgram(
		Shader{ GL_VERTEX_SHADER, "MeshVertexShader.glsl" },
		Shader{ GL_FRAGMENT_SHADER, "MeshFragmentShader.glsl" }));

	// light
	count = 0;
	std::vector<Light> lights;
	std::cout << "How many light do you want 0, 1, 2 ?";
	std::cin >> count;
	if (count > 2) count = 2;

	window->SetLightProgram(ShaderProgram(
		Shader{ GL_VERTEX_SHADER, "LightVertexShader.glsl" },
		Shader{ GL_FRAGMENT_SHADER, "LightFragmentShader.glsl" }));
	
	if (count > 0) 
	{		
		lights.reserve(count);
		for (int i = 0; i < count; ++i)
		{
			Light l = Light(glm::vec3(0), glm::vec3(1.0f), 
				glm::vec3(1.0f, 1.0f, 0.8f), glm::vec3(1.0f, 1.0f, 0.8f));
			l.parameters = LightParameters(window->GetMeshProgram().GetID(), i);
			l.meshParameters = LightParameters(window->GetLightProgram().GetID());
			
			auto mr = std::make_shared<MeshRenderer>();
			mr->SetMesh(Mesh("./models/cube.obj"));
			l.AddComponent(mr);
			
			lights.emplace_back(l);
		}		
	}

	auto id = window->GetLightProgram().GetID();
	
	//GLint usedLightCount = glGetUniformLocation(window->GetLightProgram().GetID(), "usedLightCount");
	GLint usedLightMeshCount = glGetUniformLocation(window->GetMeshProgram().GetID(), "usedLightCount");

	window->GetLightProgram().Use();
	GLuint lightProjMatrix = glGetUniformLocation(window->GetLightProgram().GetID(), "proj");
	glUniformMatrix4fv(lightProjMatrix, 1, GL_FALSE, glm::value_ptr(window->camera.GetProjectionMatrix()));
	GLuint lightModelMatrix = glGetUniformLocation(window->GetLightProgram().GetID(), "model");
	
	if (std::shared_ptr<MeshRenderer> mr; entities[0] != nullptr && entities[0]->TryGetComponent(mr))
	{
		glUniformMatrix4fv(lightModelMatrix, 1, GL_FALSE, 
			glm::value_ptr(glm::scale(glm::mat4(1), mr->GetMesh()->bounds.size / 40.0f)));
	}
			
	// pointeur sur la couleur de la fenetre
	glfwSetWindowUserPointer(window->GetWindowPtr(), background);
	/// pointeur sur la m_Position de la souris
	glfwSetCursorPosCallback(window->GetWindowPtr(), Input::CursorPosCallback);

	//// utilise le programe creer precedement
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glfwSetTime(0);	
	//// change la couleur de la fenetre
	glClearColor(1.f, 0.08f, 0.58f, 1.f);

	const GLint mvpID = glGetUniformLocation(window->GetMeshProgram().GetID(), "mvp");
	const GLint mvID = glGetUniformLocation(window->GetMeshProgram().GetID(), "mv");

	// pointeur sur la camera de la fenetre
	glfwSetWindowUserPointer(window->GetWindowPtr(), window);
	// pointeur sur la mouse wheel
	glfwSetScrollCallback(window->GetWindowPtr(), Input::GetScrolling);
	// pointeur sur les touche du claver
	glfwSetKeyCallback(window->GetWindowPtr(), Input::GetKeyDown);


	auto meshSize = glm::distance(entities[0]->GetComponent<MeshRenderer>()->GetMesh()->bounds.min, 
		entities[0]->GetComponent<MeshRenderer>()->GetMesh()->bounds.max);

	while (!glfwWindowShouldClose(window->GetWindowPtr()))
	{
		glfwPollEvents();
		// remet la couleur par default
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat time = static_cast<GLfloat>(glfwGetTime());

		// Mesh
		if (!entities.empty()) 
		{
			window->GetMeshProgram().Use();
			for (auto& entity : entities)
			{
				if (std::shared_ptr<MeshRenderer> mr; entity->TryGetComponent(mr))
				{
					std::shared_ptr<Transform> tr;
					bool hasTransform = entity->TryGetComponent(tr);

					glUniformMatrix4fv(mvpID, 1, GL_FALSE, glm::value_ptr(mr->GetMVPMatrix(
						window->camera.GetProjectionMatrix(),
						window->camera.GetViewMatrix(),
						hasTransform ? tr->GetModelMatrix() : glm::mat4(1.0f)
					)));

					glUniformMatrix4fv(mvID, 1, GL_FALSE, glm::value_ptr(mr->GetMVMatrix(
						window->camera.GetViewMatrix(),
						hasTransform ? tr->GetModelMatrix() : glm::mat4(1.0f)
					)));

					glUniform1ui(glGetUniformLocation(window->GetMeshProgram().GetID(), "texSample"), static_cast<GLuint>(mr->GetTextures().size()));
					glUniform1i(glGetUniformLocation(window->GetMeshProgram().GetID(), "tex"), 0);

					mr->Draw(window->GetMeshProgram());
				}
			}
		}
		
		//glUniform1ui(usedLightCount, static_cast<GLuint>(lights.size()));
		glUniform1ui(usedLightMeshCount, static_cast<GLuint>(lights.size()));

		// Lights
		if (!lights.empty())
		{
			window->GetLightProgram().Use();
			
			// Calcul m_Position des lights;
			for (size_t i = 0; i < lights.size(); ++i)
			{
				float xorz = cos(time * 2.0f) * 0.5f * meshSize;
				float yorx = cos(time / 2.0f) * 0.5f * meshSize;
				float zory = sin(time * 2.0f) * 0.5f * meshSize;

				if (i % 2 == 0) 
				{
					lights[i].position.x = xorz;
					lights[i].position.y = yorx;
					lights[i].position.z = zory;
				}
				else
				{
					lights[i].position.z = xorz;
					lights[i].position.x = yorx;
					lights[i].position.y = zory;
				}
				
				glm::vec4 lightPosition = window->camera.GetViewMatrix() * glm::vec4(lights[i].position, 1.0f);
				lights[i].position = glm::vec3(lightPosition) / lightPosition.w;
				
				glUniform3fv(lights[i].parameters.position, 1, glm::value_ptr(lights[i].position));
				glUniform3fv(lights[i].parameters.ambiant, 1, glm::value_ptr(lights[i].ambiant));
				glUniform3fv(lights[i].parameters.diffuse, 1, glm::value_ptr(lights[i].diffuse));
				glUniform3fv(lights[i].parameters.specular, 1, glm::value_ptr(lights[i].specular));

				glUniform3fv(lights[i].meshParameters.position, 1, glm::value_ptr(lights[i].position));
				glUniform3fv(lights[i].meshParameters.diffuse, 1, glm::value_ptr(lights[i].diffuse));
				
				if (std::shared_ptr<MeshRenderer> mr; lights[i].TryGetComponent(mr))
				{
					//std::shared_ptr<Transform> tr;
					/*glUniformMatrix4fv(mvpID, 1, GL_FALSE, glm::value_ptr(mr->GetMVPMatrix(
						window->camera.GetProjectionMatrix(), 
						window->camera.GetViewMatrix(), 
						lights[i].TryGetComponent(tr) ? tr->GetModelMatrix() : glm::mat4(1.0f)
						)));*/

					mr->Draw(window->GetLightProgram());
				}
			}

		}

		glfwSwapBuffers(window->GetWindowPtr());
	}

	glfwDestroyWindow(window->GetWindowPtr());
	glfwTerminate();
	std::exit(EXIT_SUCCESS);
}