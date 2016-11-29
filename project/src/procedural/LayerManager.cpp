#include <iostream>

#include "procedural\LayerManager.h"
#include "procedural\Grid.h"

#include "Bounds.h"

void WorldLayerManager::GenerateTerrain()
{
	//Get the grid size and build it
	Bounds terrainBounds= worldGrid->GetRealBounds();
	terrain = new Plane();
	terrain->Generate(terrainBounds);
	
	GLTexture grass;
	grass.loadImageData("textures\\grass.jpg");
	terrain->assignTexture(&grass);
	terrain->getMesh()->adjustTexelMappingConstant(512.f);
}

void WorldLayerManager::GenerateRoads()
{
	//Recursively generate and draw all roads
	DrawRoadsRecursively(
		Grid::Coordinate(0, 0),
		Grid::Coordinate(Grid::WIDTH - 1, Grid::HEIGHT - 1),
		WorldLayerManager::MAX_RECURSIVE_DEPTH
	);

	std::vector<Bounds> RoadLengths = worldGrid->GetKnownRoads();
	vec3 black = vec3(0.01f);

	GLTexture streetVertical, streetHorizontal;
	streetVertical.loadImageData("textures\\streetVertical.jpg");
	streetHorizontal.loadImageData("textures\\streetHorizontal.jpg");

	for (int i = 0; i < RoadLengths.size(); ++i) {
		Bounds& bounds = RoadLengths[i];
		//Only for debugging purposes... hopefully
		ProceduralObject* newRoad = new Plane();
		newRoad->Generate(bounds);
		//newRoad->paintColor(black);

		newRoad->assignTexture(
			(bounds.getXlength() > bounds.getYlength())? &streetVertical : &streetHorizontal
		);

		//newRoad->getMesh()->adjustTexelMappingConstant(128.f);
		newRoad->translate(0.f, 0.01f+(0.01f*((float)i)), 0.f);
		roads.push_back(newRoad);
	}

	worldGrid->TerminalPrint();
}

void WorldLayerManager::DrawRoadsRecursively(Grid::Coordinate min, Grid::Coordinate max, int levels)
{
	//Run some checks before proceeding
	int xLength = max.x - min.x, yLength = max.y - min.y;
	bool hasSideToSplit = xLength > MIN_BLOCK_SIZE || yLength > MIN_BLOCK_SIZE;
	bool continueDivision = levels >= 0 && hasSideToSplit;
	bool hasMinimumRequirements = xLength <= MAX_BLOCK_SIZE && yLength <= MAX_BLOCK_SIZE;
	bool randomlyQuit = hasMinimumRequirements && ((static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100))) < 25.f);
	//Continue?
	if (!continueDivision || randomlyQuit) {
		std::cout << "Stopping division| Depth:" << MAX_RECURSIVE_DEPTH - levels << " Coords:" << min << "|" << max << std::endl;
		if (randomlyQuit)
			std::cout << "Choice was at random" << std::endl;
		return;
	}
	
	int axisChoice = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100))); //50/50
	Grid::Axis axisToDivide = axisChoice > 50 ? Grid::Axis::Y : Grid::Axis::X;
	//Grid::Axis axisToDivide = Grid::X;

	if (Grid::X==axisToDivide && xLength < (MIN_BLOCK_SIZE))
	{
		if (yLength > MIN_BLOCK_SIZE)
		{
			axisToDivide = Grid::Axis::Y; //Force a choice on the Y Axis
		}
		else
		{
			std::cout << "Early return" << std::endl;
			return;
		}
	}
	if (Grid::Y == axisToDivide && yLength < (MIN_BLOCK_SIZE))
	{
		if (xLength > MIN_BLOCK_SIZE)
		{
			axisToDivide = Grid::Axis::X; //Force a choice on the X axis
		}
		else
		{
			std::cout << "Early return" << std::endl;
			return;
		}
	}
	
	std::cout << "Axis choice was " << ((int)axisToDivide==0? 'X':'Y') << std::endl;
	//Make Exact splits for now
	int splitPoint = 0;
	if (Grid::Axis::Y == axisToDivide) {
		//Make exact splits for now
		//splitPoint = (min.y + max.y) / 2;
		splitPoint = GetRandomRange(min.y+(MIN_BLOCK_SIZE/2), max.y-(MIN_BLOCK_SIZE/2));
		worldGrid->FillLine(min.x, max.x, splitPoint, axisToDivide, Grid::Road);

		//Down box
		DrawRoadsRecursively(Grid::Coordinate(min.x, min.y), Grid::Coordinate(max.x, splitPoint), levels - 1);
		//Up box
		DrawRoadsRecursively(Grid::Coordinate(min.x, splitPoint), Grid::Coordinate(max.x, max.y), levels - 1);
	}
	else if (Grid::Axis::X == axisToDivide) {
		//splitPoint = (min.x + max.x) / 2;
		splitPoint = GetRandomRange(min.x+ (MIN_BLOCK_SIZE / 2), max.x- (MIN_BLOCK_SIZE / 2));
		worldGrid->FillLine(min.y, max.y, splitPoint, axisToDivide, Grid::Road);

		//Left box
		DrawRoadsRecursively(Grid::Coordinate(min.x, min.y), Grid::Coordinate(splitPoint, max.y), levels - 1);
		//Right box
		DrawRoadsRecursively(Grid::Coordinate(splitPoint, min.y), Grid::Coordinate(max.x, max.y), levels - 1);
	}
}

int WorldLayerManager::GetRandomRange(int a, int b)
{
	std::random_device rando;
	std::mt19937 generator(rando());
	std::uniform_int_distribution<int> distribution(a, b);
	return distribution(generator);
}

void WorldLayerManager::GenerateBuildings(std::vector<Bounds> blockBounds)
{
	for (int i = 0; i < blockBounds.size(); i++)
	{
		building = new Building();
		building->Generate(blockBounds[i]);
		buildings.push_back(building);

		GLTexture grass;
		grass.loadImageData("textures\\grass.jpg");
		building->assignTexture(&grass);
		building->getMesh()->adjustTexelMappingConstant(512.f);
		
		std::cout << "\n" << blockBounds[i].getXmin() << "\n" << blockBounds[i].getXmax() << std::endl;
	}
}

std::vector<ProceduralObject*> WorldLayerManager::GetGeneratedBuildings()
{
	std::vector<ProceduralObject*> retVal(buildings);
	//retVal.reserve(roads.size()+buildings.size());
	//retVal.insert(retVal.end(), roads.front(), roads.back());
	//retVal.insert(retVal.end(), buildings.front(), buildings.back());

	return retVal;
}

void WorldLayerManager::GenerateVegetation(std::vector<Bounds> parkBounds)
{

}

WorldLayerManager::WorldLayerManager()
{

}

void WorldLayerManager::CreateCity()
{
	worldGrid = new Grid();

	GenerateTerrain();
	GenerateRoads();

	//Get whatever is free and divide it between buildings and parks
	std::vector<Bounds> freeZones = worldGrid->GetFreeSpaces();
	std::vector<Bounds> buildingBlocks, parkBlocks;
	for (Bounds& freeBlock : freeZones) {
		int choice = GetRandomRange(0, 100);

		if (choice<25) { //0-25%
			parkBlocks.push_back(freeBlock);
		}
		else { //26-100%
			buildingBlocks.push_back(freeBlock);
		}
	}

	GenerateBuildings(buildingBlocks);
	GenerateVegetation(parkBlocks);
}

WorldGenericObject * WorldLayerManager::GetTerrain()
{
	return terrain;
}

std::vector<ProceduralObject*> WorldLayerManager::GetGeneratedRoads()
{
	std::vector<ProceduralObject*> retVal(roads);
	//retVal.reserve(roads.size()+buildings.size());
	//retVal.insert(retVal.end(), roads.front(), roads.back());
	//retVal.insert(retVal.end(), buildings.front(), buildings.back());

	return retVal;
}

vec3 WorldLayerManager::GetStartCameraPos()
{
	int low = 0, high = roads.size();
	int index = GetRandomRange(low, high);
	Bounds selectedRoads = worldGrid->GetKnownRoads()[index];
	vec3 pos;
	pos.x = (selectedRoads.getXmax() + selectedRoads.getXmin()) / 2.f;
	pos.z = (selectedRoads.getYmax() + selectedRoads.getYmin()) / 2.f;
	pos.y = 1.5f;

	return pos;
}
