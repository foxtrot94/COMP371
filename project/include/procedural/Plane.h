#pragma once

#include "base/Objects.h"
#include "..\Utils.h"

class Plane : public ProceduralObject {
private:

public:
	virtual void Generate(Bounds perimeter) override;
};