#pragma once

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

	//Audio management interface
	Modulator* modulator;

	//Primary Input manager
	Input* input;

	//Time related variables
	float lastFrame, thisFrame, framerate, deltaTime, totalTime;

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
	void Init();

	//Run the engine
	void Run();
};