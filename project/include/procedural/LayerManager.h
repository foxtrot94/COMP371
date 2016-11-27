#pragma once

#include <vector>

#include "Utils.h"

class Grid;
class Plane;
class Road;
class Building;
//class Plants;


class WorldLayerManager {
private:
	//Main grid used for world generation
	Grid* worldGrid;

	//Main Terrain on top of which the world is made
	Plane* terrain;

	//Colletion of roads in the city
	std::vector<Road*> roads;
	//All generated buildings
	std::vector<Building*> buildings;
	//Any vegetation items around the city
	//std::vector<Plants*> vegetation;

	void GenerateTerrain();

	void GenerateRoads();

	void GenerateBuildings();

	void GenerateVegetation();

	//void PlaceExtraProps();

public:
	//Generate a city. Step by step
	void CreateCity();
};