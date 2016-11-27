#pragma once

#include "base\Objects.h"
#include "..\objloader.hpp"

class Road : public ProceduralObject{
private:
	//TODO:
public:
	//ctor
	Road();
	//dtor
	virtual ~Road();

	virtual void Generate(Bounds perimeter) override;

	void init();
};