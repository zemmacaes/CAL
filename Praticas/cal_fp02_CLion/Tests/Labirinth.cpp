/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{
	initializeVisited();
	return (goalFinder(x, y));
}

bool Labirinth::goalFinder(int x, int y) {
    if (visited[x][y]) return false;
    if (x < 0 || x > 10 || y < 0 || y > 10) return false;
    visited[x][y] = true;
    if (labirinth[x][y] == 0) return false;
    if (labirinth[x][y] == 2) return true;

    bool right, left, up, down;
    right = goalFinder(x + 1, y);
    if (right) return true;
    left = goalFinder(x - 1, y);
    if (left) return true;
    up = goalFinder(x, y - 1);
    if (up) return true;
    down = goalFinder(x, y + 1);
    if (down) return true;
    return false;
}

