#include "main.h"
#include "input.h"
#include "utils.h"

#include "base\Engine.h"
#include "TriangleTest.h"

//Entry point
int main()
{
	glm::mat4 model(1.f), view(1.f), projection(1.f); //Test only matrices
	float lastFrame = 0.f, thisFrame = 0.f, framerate = 0.f, deltaTime=1.f;

	//Initialize
	std::cout << "Starting OpenGL 3.3 using GLFW" << std::endl;
	Renderer* render = new Renderer();
	Renderer::Window* engineWindow = render->Initialize("Shin Sekai - COMP371 OpenGL Project");
	Shader shaderBuilder("glsl\\vertex.shader", "glsl\\fragment.shader");
	render->UseShader(&shaderBuilder);

	std::cout << "Initialization complete, starting game" << std::endl;
	
	//Test Object
	TriangleTest triangle;
	//Game loop
	while (!glfwWindowShouldClose(engineWindow->glfwContext)){
		//Get framerate and time
		thisFrame = (float)glfwGetTime();
		deltaTime = thisFrame - lastFrame;
		framerate = 1.f / deltaTime;
		lastFrame = thisFrame;
		//std::cout << framerate << std::endl;

		//Process inputs
		glfwPollEvents();
		glfwGetFramebufferSize(engineWindow->glfwContext, &engineWindow->width, &engineWindow->height);
		glViewport(0, 0, engineWindow->width, engineWindow->height);

		//Draw on buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Black Background
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		//Update the camera and render once
		render->UpdateCamera(view, projection);
		render->Render((WorldGenericObject*)&triangle);
		glBindVertexArray(NULL);

		//Show to screen
		glfwSwapBuffers(engineWindow->glfwContext);
	}

	//Cleanup now
	//TODO: Check what's being leaked
	//TODO: cleanup meshes
	//TODO: Cleanup engine resources

	glfwTerminate();
	return 0;
}