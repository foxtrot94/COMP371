#pragma once
#include "base/Objects.h"

class Light : public ProceduralObject
{

public:
	Light();
	~Light();

	//void UpdateLightShader();
	//void GenerateLightSource();
private:

	virtual void Generate(Bounds perimeter) override;
};


