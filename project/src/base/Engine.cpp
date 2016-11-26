#include "base/Engine.h"
#include "TriangleTest.h"

LightweightEngine::LightweightEngine()
{
	renderer = Renderer::GetInstance();
	input = Input::GetInstance();


	thisFrame = 0.f;
	deltaTime = 0.1f;
	framerate = 0.f;
	lastFrame = 0.f;

	//Check for possible issues
}

LightweightEngine::~LightweightEngine()
{
	Cleanup();
}
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
	mat4 view(1.f), projection(1.f);
	//@foxtrot94

	//Camera taking deltaTime for its operations
	camera->SetCameraSpeed(deltaTime);

	// Camera/View transformation 
	//TODO: move these elsewhere
	view = glm::lookAt(camera->camPam.cameraPos, camera->camPam.cameraPos + camera->camPam.cameraFront,camera->camPam.cameraUp);
	projection = glm::perspective(camera->camPam.fov, (GLfloat)engineWindow->width/ (GLfloat)engineWindow->height, 0.1f, 100.0f);

	//Draw on buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Black Background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Update the camera, the objects and render once
	
	renderer->UpdateCamera(view, projection);
	for (auto* object : drawables) {
		object->Update(deltaTime);
	}
	renderer->Render(drawables);

	//Show to screen
	glfwSwapBuffers(engineWindow->glfwContext);
}

void LightweightEngine::Cleanup()
{
	delete renderer;
	delete input;
}

void LightweightEngine::Init(std::string WindowTitle)
{
	//Initialize GLFW and the renderer
	std::cout << "Starting OpenGL 3.3 using GLFW" << std::endl;
	engineWindow = renderer->Initialize(WindowTitle);
	Shader* shaderBuilder = new Shader("glsl\\vertex.shader", "glsl\\fragment.shader");
	renderer->UseShader(shaderBuilder);

	//Initialize Camera and pass width and height from engine window
	camera = Camera::GetInstance(engineWindow);
	//Pass camera to Input
	input->setCamera(camera);

	//Also initialize the Input
	glfwSetKeyCallback(engineWindow->glfwContext, &KeyInputCallback);
	glfwSetCursorPosCallback(engineWindow->glfwContext, &CursorPositionCallback);
	glfwSetMouseButtonCallback(engineWindow->glfwContext, &MouseButtonCallback);
}

void LightweightEngine::LoadWorld()
{
	//TODO: Place all the world loading here.
	//We can fire off a thread to keep the screen drawing while this method begins loading the world
}

void LightweightEngine::Run()
{
	//Check init
	if (engineWindow == NULL) {
		return;
	}

	//Unlock framerate
	glfwSwapInterval(0);
	//@foxtrot94: DEBUG CODE - Remove or Comment in Master
	WorldGenericObject* triangle = new TriangleTest();
	drawables.push_back(triangle);

	//Game loop
	std::cout << "Initialization complete, starting game" << std::endl;
	while (!glfwWindowShouldClose(engineWindow->glfwContext)) {
		this->UpdateTime();
		this->ProcessInputs();
		this->DrawFrame();
	}

	drawables.pop_back();
	delete triangle;

	glfwTerminate();
}
