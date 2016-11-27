#pragma once

#include <iostream>

#include "Bounds.h"
#include "Utils.h"

class Grid {
public:
	// Amount of cells in the grids x-axis
	static const int WIDTH = 50;
	// Amount of cells in the grids y-axis
	static const int HEIGHT = 50;
	static const int NUM_CELLS = WIDTH*HEIGHT;
	// The x and y length, in meters, of each cell
	const float CELL = 10.f; //10 meters is the average street width
	
	// What element occupies a cell currently
	enum Type {
		Empty = 0,
		Road = 1,
		Free = 2
	};
	// Axis along the grid
	enum Axis {
		X = 0,
		Y = 1
	};

	// Simple struct for addressing coordinates
	struct Coordinate {
		int x, y;
		Coordinate(int X, int Y) {
			x = X;
			y = Y;
		}
		bool isValid() {
			return x > 0 && x < WIDTH && y>0 && y < HEIGHT;
		}
		friend std::ostream& operator<<(std::ostream& os, const Grid::Coordinate& coord);
	};

private:
	//The underlying grid implementations
	Grid::Type Cells[Grid::WIDTH][Grid::HEIGHT];
	//Actual dimensions defined by the grid
	float realWidth, realHeight;
	
public:
	//ctor
	Grid();
	//dtor
	~Grid();

	//Makes a line along the axis from start to end with fill value
	void FillLine(int start, int end, int axisPoint, Grid::Axis axis, Grid::Type fillValue);

	//Recursively fills the grid starting at x,y with the fill value
	void FillRecursive(int x, int y, Grid::Type fillValue);

	void TerminalPrint();

	Bounds GetRealBounds();
};