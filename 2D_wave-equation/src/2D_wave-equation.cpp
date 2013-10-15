//============================================================================
// Name        : 2D_wave-equation.cpp
// Author      : dk0r
// Version     :
// Copyright   : 
// Description : 2D wave on a string
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "nr3.h"
#include "rk4.h"
#include "gaussj.h"
#include <vector>

using namespace std;

//constants
double pi = atan(1)*4;

//Initial Conditions
double pastX = 0.04;
double initX = 0.04;

//Parameters
double dx = 1; //position stepping
double dt = 0.01;  //time stepping
int Max = 1000; //max iterations

double rho = 0.009; // volumetric? surface or linear density?
double T =   42; //newtons

double C = sqrt(T/rho);
double cPrime = dx/dt;
double COURANT = pow( C/cPrime , 2 );

//IO.
ofstream of;
ofstream ofMidi;

int fileNamerCounter = 0;
string make_filename( const string& basename, const string& ext )
  {
	  ostringstream result;
	 result  << basename << setw(3) << setfill('0') << fileNamerCounter << ext;
	  fileNamerCounter++;
	  return result.str();
  }



void wave()
{
	int n = 257; // grid dimension is n-1
	int x = n;  // grid dimension is x-1
	int y = n;  // grid dimension is y-1

	//Psi matrices
	double psi[x][y];
	double prevPsi[x][y];
	double nextPsi[x][y];
	bool dontCompute[x][y]; //ensures boundary conditions stay fixed


	//initializes entire grid
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			psi[i][j] = 0;
			prevPsi[i][j] = 0;
			nextPsi[i][j] = 0;
			dontCompute[i][j] = false;
		}
	}

	//defines: Horizontal upper&lower boundary conditions (amplitude = 0)
	for(int j=0; j<n; j++)
	{
		//upper horizontal boundary condition
		psi[0][j] = 0;
		prevPsi[0][j] = 0;
		nextPsi[0][j] = 0;
		dontCompute[0][j] = true;

		//lower horizontal boundary condition
		psi[n-1][j] = 0;
		prevPsi[n-1][j] = 0;
		nextPsi[n-1][j] = 0;
		dontCompute[n-1][j] = true;
	}

	//defines: Vertical left&right boundary conditions (amplitude = 0)
	for(int i=0; i<n; i++)
	{
		//left vertical boundary condition
		psi[i][0] = 0;
		prevPsi[i][0] = 0;
		nextPsi[i][0] = 0;
		dontCompute[i][0] = true;

		//right vertical boundary condition
		psi[i][n-1] = 0;
		prevPsi[i][n-1] = 0;
		nextPsi[i][n-1] = 0;
		dontCompute[i][n-1] = true;
	}




		//defines INITIAL conditions
		prevPsi[63][63] = pastX; //second quadrant (top left)
		psi[63][63] = initX; //second quadrant (top left)



		//Start Calculations?????

		int counter=1;
		double psiStore=5;

	for(int k = 0; k<Max; k++)
	{
			//Calculates future psi (nextPsi[][])
			for(int i=0; i<n; i++)
			{
				for(int j=0; j<n; j++)
				{

						if(dontCompute[i][j] == false)
						{
							nextPsi[i][j] = COURANT * ( psi[i+1][j] + psi[i-1][j] +psi[i][j+1] + psi[i][j-1] - 4*psi[i][j])
													- prevPsi[i][j] + 2*psi[i][j] ;
						}
				}
			}


			//File Output
			of.open(make_filename( "/home/dk0r/git/musical-phys/2D_wave-equation/csv/psi", ".csv" ).c_str());

				for(int i=0; i<n ;i++)
				 {
					 for(int j=0; j<n ;j++)
					 {
						 {
							of << i << "," << j << "," << psi[i][j] << "\n";
						 }
					 }
					 of << "\n";
				 }


			double localAvg = (psi[1][62]+psi[1][63]+psi[1][64]) / 3;
			double prevLocalAvg = (prevPsi[1][62]+prevPsi[1][63]+prevPsi[1][64]) / 3;

			double current=0;
			double previous=0;

						for(int j=1; j<n; j++)
						{
							current += psi[1][j];
							previous += prevPsi[1][j];
						}

			double totalAvg = current/254;
			double prevTotalAvg = previous/254;


			            /*	(fabs(psi[1][63]) > 0.0001) &&  (fabs(  psi[1][63])<psiStore)

							&& ( (fabs(psi[1][62]) < localAvg) && (fabs(psi[1][64]) < localAvg) )

							&& ( fabs(prevPsi[1][63]) < fabs(psi[1][63]) )

							&& (fabs(prevPsi[1][62]) < prevLocalAvg) && (fabs(prevPsi[1][64]) < prevLocalAvg)
						*/


			if(  (counter>79 && counter <111) || (counter>640 && counter <691))
			{

				//psiStore = fabs(psi[1][63]);

				cout << "[[psi-" << setw(3) << counter <<"]]\n";
				cout << "above)    psi[1][64] = " << setprecision(8) << psi[1][64] <<"\n";
				cout << "::::::::::psi[1][63] = " << setprecision(8) << psi[1][63] <<"\n";
				cout << "below)    psi[1][62] = " << setprecision(8) << psi[1][62] <<"\n";


				cout << "\nLocal-avg      = " << localAvg << "\n";
				cout << "Prev-Local-avg = " << prevLocalAvg << "\n";
				cout << "del(Local) = " << fabs(localAvg-prevLocalAvg) << "\n\n";
				cout << "Total-avg    = " << totalAvg << "\n";
				cout << "Prev-Tot-avg = " << prevTotalAvg << "\n";
				cout << "del(Total) = " << fabs(totalAvg-prevTotalAvg) << "\n\n";
				cout << "del(Total-Local) = " << fabs(fabs(totalAvg-prevTotalAvg)-fabs(localAvg-prevLocalAvg)) << "\n\n";
				cout << "------------------------------------------------------------------" << "\n\n" ;
			}

	/*		//Horizontal
			if(  (fabs(psi[1][63]) > 0.0001) && (fabs(psi[1][63])<psiStore))
			{
				psiStore = fabs(psi[1][63]);

				cout << "psi-" << setw(3) << counter << "::  psi[1][63] = " << setprecision(8) << psi[1][63] << "\n";
			}
	*/

			counter++; //for debug output above
			of.close();

			//copies current psi to previous Psi for next time iteration
			//copies current psi into future psi
			for(int i=0; i<n; i++)
			{
				for(int j=0; j<n; j++)
				{
					if(dontCompute[i][j] == false)
					{
						prevPsi[i][j] = psi[i][j];
						psi[i][j] = nextPsi[i][j];
					}
				}
			}

	}

}

	 int main()
	 {
		cout << "............begin! \n";
		wave();
		return 0;
	 }
