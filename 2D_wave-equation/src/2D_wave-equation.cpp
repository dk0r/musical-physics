//============================================================================
// Name        : 2D_wave-equation.cpp
// Author      : dk0r
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include "nr3.h"
#include "rk4.h"
#include "gaussj.h"
#include <vector>

using namespace std;

//constants
double pi = atan(1)*4;

//Initial Conditions
double pastX = 0;
double pastY = 0;
double pastT = 0;

//Parameters
double dt = 0.01;  //time stepping
int kmax = 1000; //max iterations
double globeDT = 0; //global step tracking


double derivs()
{


	return 0;
}

void wave()
{
	VecDoub w(4);
	VecDoub dwdx(4);  //vector of x and y, positions and velocities

	int n = 129; // grid dimension is n-1
	int x = n;  // grid dimension is x-1
	int y = n;  // grid dimension is y-1

	double initialAmp = 0; //initial amplitude

	double amp[x][y];
	double originalAmp[x][y];
	bool dontCompute[x][y]; //ensures boundary conditions stay fixed



	//*****************************************************************************************************
	//*****************************************************************************************************

	//initializes entire grid
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			amp[i][j] = 0;
			originalAmp[i][j] = 0;
			dontCompute[i][j] = false;
		}
	}

	//defines: Horizontal upper&lower boundary conditions (amplitude = 0)
	for(int j=0; j<n; j++)
	{
		//upper horizontal boundary condition
		amp[0][j] = initialAmp;
		originalAmp[0][j] = initialAmp;
		dontCompute[0][j] = true;

		//lower horizontal boundary condition
		amp[n-1][j] = initialAmp;
		originalAmp[n-1][j] = initialAmp;
		dontCompute[n-1][j] = true;
	}

	//defines: Vertical left&right boundary conditions (amplitude = 0)
	for(int i=0; i<n; i++)
	{
		//left horizontal boundary condition
		amp[i][0] = initialAmp;
		originalAmp[i][0] = initialAmp;
		dontCompute[i][0] = true;

		//right horizontal boundary condition
		amp[i][n-1] = initialAmp;
		originalAmp[i][n-1] = initialAmp;
		dontCompute[i][n-1] = true;
	}

	//*****************************************************************************************************
	//*****************************************************************************************************

	//Start Calculations?????

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			amp[i][j] = 0;
			originalAmp[i][j] = 0;
			dontCompute[i][j] = false;
		}
	}















	//*****************************************************************************************************8
	//*****************************************************************************************************8
	//*****************************************************************************************************8
	//*****************************************************************************************************8
	//*****************************************************************************************************8
	//*****************************************************************************************************8
	//*****************************************************************************************************8
	//*****************************************************************************************************8

	double temp[x][y];
	double original[x][y];

	double outterTemp = 0;
	double innerTemp = 10;

	bool donotcompute[x][y];

	//initializes grid
	 for(int ix=0; ix<n; ix++)
	 {
		 for (int iy=0; iy<n; iy++)
		 {
			 donotcompute[ix][iy] = false;
			 temp[ix][iy] = 0.0;
			 original[ix][iy] = 0.0;
		 }
	 }


/*
	 //defines: An upper horizontal amplitude
	 for(int iy=1; iy<(n-1); iy++)
	 {
		 donotcompute[0][iy] = true;

		 temp[0][iy] = innerTemp;
		 original[0][iy] = innerTemp;
	 }
*/


	 //defines: A lower horizontal amplitude
	 for(int iy=1; iy<(n-1); iy++)
	 {
		 donotcompute[n-1][iy] = true;

		 temp[n-1][iy] = innerTemp;
		 original[n-1][iy] = innerTemp;
	 }


	 //defines left and right vertical boundary conditions
	 for(int ix=0; ix<n; ix++)
	 {
		 donotcompute[ix][0] = true;
		 donotcompute[ix][n-1] = true;

		 temp[ix][0] = outterTemp;
		 temp[ix][n-1] = outterTemp;

		 original[ix][0] = outterTemp;
		 original[ix][n-1] = outterTemp;





}

int main()
{

	wave();

	return 0;

}
