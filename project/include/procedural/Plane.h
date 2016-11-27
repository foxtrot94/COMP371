#pragma once

#include "base/Objects.h"

class Plane : public ProceduralObject {
private:

public:
	virtual void Generate(Bounds perimeter) override;
};