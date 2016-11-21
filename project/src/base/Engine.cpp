#include "base/Engine.h"
#include "TriangleTest.h"

void LightweightEngine::UpdateTime()
{
	//Get framerate and time
	thisFrame = (float)glfwGetTime();
	deltaTime = thisFrame - lastFrame;
	framerate = 1.f / deltaTime;
	lastFrame = thisFrame;
	totalTime += deltaTime;
	//Throw the framerate at the console
	//std::cout << framerate << std::endl;
}

void LightweightEngine::ProcessInputs()
{
	glfwPollEvents();
	glfwGetFramebufferSize(engineWindow->glfwContext, &engineWindow->width, &engineWindow->height);
	glViewport(0, 0, engineWindow->width, engineWindow->height);
}

void LightweightEngine::DrawFrame()
{
	//@foxtrot94: DEBUG CODE - Remove or Comment in Master
	TriangleTest triangle;
	mat4 view(1.f), projection(1.f);
	//@foxtrot94

	//Draw on buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Black Background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Update the camera and render once
	triangle.translate(0.05f * glm::sin(10.f*totalTime), 0.f, 0.f);
	renderer->UpdateCamera(view, projection);
	renderer->Render((WorldGenericObject*)&triangle);
	glBindVertexArray(NULL);

	//Show to screen
	glfwSwapBuffers(engineWindow->glfwContext);
}

void LightweightEngine::Cleanup()
{
	delete renderer;
	delete input;
}

LightweightEngine::LightweightEngine()
{
	renderer = Renderer::GetInstance();
	input = Input::GetInstance();

	thisFrame = 0.f;
	deltaTime = 0.1f;
	framerate = 0.f;
	lastFrame = 0.f;
}

LightweightEngine::~LightweightEngine()
{
	Cleanup();
}

void LightweightEngine::Init(std::string WindowTitle)
{
	//Initialize GLFW and the renderer
	std::cout << "Starting OpenGL 3.3 using GLFW" << std::endl;
	engineWindow = renderer->Initialize(WindowTitle);
	Shader* shaderBuilder = new Shader("glsl\\vertex.shader", "glsl\\fragment.shader");
	renderer->UseShader(shaderBuilder);

	//Also initialize the Input
	glfwSetKeyCallback(engineWindow->glfwContext, &KeyInputCallback);
	glfwSetCursorPosCallback(engineWindow->glfwContext, &CursorPositionCallback);
	glfwSetMouseButtonCallback(engineWindow->glfwContext, &MouseButtonCallback);
}

void LightweightEngine::Run()
{
	//Check init
	if (engineWindow == NULL) {
		return;
	}

	std::cout << "Initialization complete, starting game" << std::endl;

	//Unlock framerate
	glfwSwapInterval(0);
	//Game loop
	while (!glfwWindowShouldClose(engineWindow->glfwContext)) {
		this->UpdateTime();
		this->ProcessInputs();
		this->DrawFrame();
	}

	//Cleanup now
	//TODO: Check what's being leaked
	//TODO: cleanup meshes
	//TODO: Cleanup engine resources

	glfwTerminate();
}
