#include "procedural\LayerManager.h"
#include "procedural\Grid.h"

void WorldLayerManager::GenerateTerrain()
{
	//Get the real size of the grid
}

void WorldLayerManager::GenerateRoads()
{

}

void WorldLayerManager::GenerateBuildings()
{

}

void WorldLayerManager::GenerateVegetation()
{

}

void WorldLayerManager::CreateCity()
{
	worldGrid = new Grid();

	GenerateTerrain();
	GenerateRoads();
	GenerateBuildings();
	GenerateVegetation();
}
