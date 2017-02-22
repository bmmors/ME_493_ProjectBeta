//Britny Mors
//ME 493 - Autonomy
//Homework 2 - Grid World Domain
//Worked with Sierra Gonzales

#include <iostream>
#include <assert.h>
#include <vector>
#include <random>
#include <time.h>

using namespace std;

void create_grid() {

}

int main() {
	int Ax = 0; //initialize agent location at (0,0)
	int Ay = 0;
	int Gx = 0; //initialize goal location at (0,0)
	int Gy = 0;
	
	int xGS = 5; //set x value for grid size
	int yGS = 5; //set y calue for grid size

	//char grid[xGS][yGS]; //create array to store x and y grid information

	//Set the agent and the goal in random locations
	Ax = rand() % xGS;
	Ay = rand() % yGS;

	Gx = rand() % xGS;
	Gy = rand() % yGS;

	cout << "Agent x:\t" << Ax << "\ty:\t" << Ay << endl;
	cout << "Goal x:\t" << Gx << "\ty:\t" << Gy << endl;



	return 0;
}