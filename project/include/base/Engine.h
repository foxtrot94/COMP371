#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "Objects.h"
#include "Renderer.h"
#include "Modulator.h"
#include "Shader.h"
#include "input.h"
#include "Camera.h"

//TODO: Rename class to something better
//Lightweight Engine abstraction layer for working with OpenGL
class WorldEngine {
public:
	//TODO:
	//struct Time {
	//};

private:
	//Main Rendering interface
	Renderer* renderer;
	//On-Screen window created by the renderer
	Renderer::Window* engineWindow;
	//List of all objects known to the Engine
	std::vector<EngineObject*> engineObjects;
	//List of all renderable, in-world objects
	std::vector<WorldGenericObject*> drawables;
	//Time related variables
	float lastFrame, thisFrame, framerate, deltaTime, totalTime;

	//Audio management interface
	Modulator* modulator;

	//Primary Input manager
	Input* input;

	//Main Camera
	Camera* camera;

	//
	bool hasLoaded;

	//Update everything related to time
	void UpdateTime();

	//Process inputs and events
	void ProcessInputs();

	//Draw a single frame using our renderer. Uses forward rendering mode.
	void DrawFrame();

	//
	void DrawLoadScreen();

	//Cleanup resources
	void Cleanup();

public:
	//Default ctor
	WorldEngine();

	//Default dtor
	~WorldEngine();

	//Initialize
	void Init(std::string WindowTitle);

	//Load the entire world
	void LoadWorld();

	//Run the engine
	void Run();
};