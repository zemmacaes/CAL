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
    return goalFinder(1, 1);
}

bool Labirinth::goalFinder(int x, int y) {

    if (visited[x][y]) return false;
    visited[x][y] = true;
    if (labirinth[x][y] == 0) return false;
    if (labirinth[x][y] == 2) {
        sol[0] = x;
        sol[1] = y;
        return true;
    };

    bool right, left, top, down;
    right = goalFinder(x+1, y);
    left = goalFinder(x-1, y);
    top = goalFinder(x, y-1);
    down = goalFinder(x, y+1);

    if (right || left || top || down) return true;
    return false;
}


