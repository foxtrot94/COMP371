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
}

void WorldLayerManager::GenerateRoads(Grid::Coordinate min, Grid::Coordinate max, int levels)
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
		GenerateRoads(Grid::Coordinate(min.x, min.y), Grid::Coordinate(max.x, splitPoint), levels - 1);
		//Up box
		GenerateRoads(Grid::Coordinate(min.x, splitPoint), Grid::Coordinate(max.x, max.y), levels - 1);
	}
	else if (Grid::Axis::X == axisToDivide) {
		//splitPoint = (min.x + max.x) / 2;
		splitPoint = GetRandomRange(min.x+ (MIN_BLOCK_SIZE / 2), max.x- (MIN_BLOCK_SIZE / 2));
		worldGrid->FillLine(min.y, max.y, splitPoint, axisToDivide, Grid::Road);

		//Left box
		GenerateRoads(Grid::Coordinate(min.x, min.y), Grid::Coordinate(splitPoint, max.y), levels - 1);
		//Right box
		GenerateRoads(Grid::Coordinate(splitPoint, min.y), Grid::Coordinate(max.x, max.y), levels - 1);
	}
}

int WorldLayerManager::GetRandomRange(int a, int b)
{
	std::random_device rando;
	std::mt19937 generator(rando());
	std::uniform_int_distribution<int> distribution(a, b);
	return distribution(generator);
}

void WorldLayerManager::GenerateBuildings()
{

}

void WorldLayerManager::GenerateVegetation()
{

}

WorldLayerManager::WorldLayerManager()
{

}

void WorldLayerManager::CreateCity()
{
	worldGrid = new Grid();

	GenerateTerrain();

	GenerateRoads(
		Grid::Coordinate(0,0),
		Grid::Coordinate(worldGrid->WIDTH-1,worldGrid->HEIGHT-1),
		WorldLayerManager::MAX_RECURSIVE_DEPTH
		);

	worldGrid->TerminalPrint();
	GenerateBuildings();
	
	GenerateVegetation();
}
