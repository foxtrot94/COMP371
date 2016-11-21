#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "Objects.h"
#include "Renderer.h"
#include "Modulator.h"
#include "Shader.h"
#include "input.h"

//TODO: Rename class to something better
class LightweightEngine {
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
	//Time related variables
	float lastFrame, thisFrame, framerate, deltaTime, totalTime;

	//Audio management interface
	Modulator* modulator;

	//Primary Input manager
	Input* input;

	//Update everything related to time
	void UpdateTime();

	//Process inputs and events
	void ProcessInputs();

	//Draw a single frame using our renderer
	void DrawFrame();

	//Cleanup resources
	void Cleanup();

public:
	//Default ctor
	LightweightEngine();

	//Default dtor
	~LightweightEngine();

	//Initialize
	void Init(std::string WindowTitle);

	//Run the engine
	void Run();
};