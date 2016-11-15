#include "main.h"
#include "input.h"
#include "utils.h"

#include "base\Engine.h"
#include "TriangleTest.h"

using namespace std;

//TODO: Remove globals, upgrade to C++ (check main.h)
glm::vec3 cameraTranslation = glm::vec3(0.0f,0.f,260.f);
glm::vec3 cameraDirectionPoint = glm::vec3(0.f, 0.f, -1.f);

glm::vec3 objectRotation = glm::vec3(0.f);

float framerate = 0.f;
float deltaTime = 99.f;

//Entry point
int main()
{
	glm::mat4 model(1.f), view(1.f), projection(1.f); //matrix projections

	std::cout << "Starting OpenGL 3.3 using GLFW" << std::endl;
	Renderer* render = new Renderer();
	Renderer::Window* engineWindow = render->Initialize("Shin Sekai - COMP371 OpenGL Project", HEIGHT, WIDTH);
	Shader shaderBuilder("glsl\\vertex.shader", "glsl\\fragment.shader");
	render->UseShader(&shaderBuilder);

	//Test Object
	TriangleTest triangle;

	//Game loop
	std::cout << "Initialization complete, starting game" << std::endl;
	float lastFrame = 0.f, thisFrame=0.f;
	while (!glfwWindowShouldClose(engineWindow->glfwContext)){
		thisFrame = (float)glfwGetTime();
		deltaTime = thisFrame - lastFrame;
		framerate = 1.f / deltaTime;
		lastFrame = thisFrame;
		std::cout << framerate << std::endl;

		glfwPollEvents();
		glfwGetFramebufferSize(engineWindow->glfwContext, &engineWindow->width, &engineWindow->height);
		glViewport(0, 0, engineWindow->width, engineWindow->height);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Black Background
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		//Update the camera and render once
		render->UpdateCamera(view, projection);
		render->Render((WorldGenericObject*)&triangle);

		glBindVertexArray(NULL);

		glfwSwapBuffers(engineWindow->glfwContext);
	}

	//Cleanup now
	//TODO: Check what's being leaked
	//TODO: cleanup meshes
	//TODO: Cleanup engine resources

	glfwTerminate();
	return 0;
}