
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>

#include "search.h"

void DijkstraTest();

using namespace std;

int main(int argc, char** argv) {
	//init rand seed
	srand(time(0));

	DijkstraTest();

	cout << "TEST" << endl;
	return 0;	
}

void DijkstraTest(){

	int width = 15;
	int height = 15;


	int** grid = createGrid(width, height);
	//printState(grid, width, height);
	int startx = randomInt(width-1);
	int starty = randomInt(height-1); 
	int endx = randomInt(width-1);
	int endy = randomInt(height-1);

	
	int wallCount = randomInt(25);
	int walls = 0;
	for(int i = 0; i < wallCount; i++){
		int x = randomInt(width-1);
		int y = randomInt(height-1);
		if( (x != startx && y != starty) || (x != endx && y != endy)){
			addWallToGrid(grid, x, y);
			walls++;
		}
	}
	cout << "wallCount: " << wallCount << " , walls: " << walls << endl;

	grid[endx][endy] = 9999;
	
	/*
	addWallToGrid(grid, 1, 4);
	addWallToGrid(grid, 2, 4);
	addWallToGrid(grid, 2, 5);
	//addWallToGrid(grid, 1, 0);
	addWallToGrid(grid, 1, 1);

	addWallToGrid(grid, 2, 1);
	addWallToGrid(grid, 2, 2);
	//addWallToGrid(grid, 3, 2);
	//addWallToGrid(grid, 4, 2);
	addWallToGrid(grid, 4, 1);

	addWallToGrid(grid, 4, 3);
	addWallToGrid(grid, 4, 4);
	*/

	Node* test = new Node(grid, width, height);
	test->setStartPosition(startx,starty);


	//printNodeState(test);

	DijkstraSearch(test, endx, endy);
}
