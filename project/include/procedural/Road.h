#pragma once

#include "base\Objects.h"

class Road : public ProceduralObject{
private:
	//TODO:
public:
	//ctor
	Road();
	//dtor
	virtual ~Road();

	virtual void Generate(Bounds perimeter) override;
};