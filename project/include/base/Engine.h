#pragma once

#include "Objects.h"
#include "Renderer.h"
#include "Modulator.h"
#include "Shader.h"
#include "input.h"

//TODO: Finish defining this class
//TODO: Rename class to something better
class LightweightEngine {
private:
	//Main Rendering interface
	Renderer* renderer;

	//Audio management interface
	Modulator* modulator;

	//TODO: Primary Input manager (Catalin)
	//Input* input;

public:
	//Default ctor
	LightweightEngine();

	//Default dtor
	~LightweightEngine();


};