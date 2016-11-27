#pragma once

#include <vector>
#include <random>

#include "procedural\Plane.h"
#include "procedural\Building.h"
#include "procedural\Road.h"

#include "Grid.h"
#include "Bounds.h"
#include "Utils.h"

//class Plants;

class WorldLayerManager {
private:
	//Private Constants
	const int MAX_RECURSIVE_DEPTH = 8;
	const int MIN_BLOCK_SIZE = 8;
	const int MAX_BLOCK_SIZE = 20;

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

	//Construct the terrain
	void GenerateTerrain();
	
	//Make roads recursively
	void GenerateRoads(Grid::Coordinate min, Grid::Coordinate max, int levels);
	//Returns a random number between 'a' and 'b'
	//TODO: move this to a random number generator class. This really shouldn't be here
	int GetRandomRange(int a, int b);

	void GenerateBuildings();

	void GenerateVegetation();

	//void PlaceExtraProps();

public:
	//ctor
	WorldLayerManager();

	//Generate a city. Step by step
	void CreateCity();
};