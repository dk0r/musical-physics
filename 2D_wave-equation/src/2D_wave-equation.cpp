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
double pastX = 0;
double pastY = 0;
double pastT = 0;

//Parameters
int mod = 1; // Prints every mod^th iteration

double dx = 1; //position stepping
double dt = 0.01;  //time stepping
int Max = 500; //max iterations

double rho = 0.01; // volumetric? surface or linear density?
double T = 40; //newtons

double C = sqrt(T/rho);
double cPrime = dx/dt;
double COURANT = pow( C/cPrime , 2 );

//Misc.
ofstream of;

int fileNamerCounter = 0;
string make_filename( const string& basename, const string& ext )
  {
  ostringstream result;
  result << basename << fileNamerCounter << ext;
  fileNamerCounter++;
  return result.str();
  }

void wave()
{
	int n = 129; // grid dimension is n-1
	int x = n;  // grid dimension is x-1
	int y = n;  // grid dimension is y-1

	double psi[x][y];
	double prevPsi[x][y];
	double nextPsi[x][y];
	bool dontCompute[x][y]; //ensures boundary conditions stay fixed



	//*****************************************************************************************************
	//*****************************************************************************************************

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
		//left horizontal boundary condition
		psi[i][0] = 0;
		prevPsi[i][0] = 0;
		nextPsi[i][0] = 0;
		dontCompute[i][0] = true;

		//right horizontal boundary condition
		psi[i][n-1] = 0;
		prevPsi[i][n-1] = 0;
		nextPsi[i][n-1] = 0;
		dontCompute[i][n-1] = true;
	}

	//defines INITIAL conditions
		prevPsi[32][32] = 1; //second quadrant (top left)
		psi[32][32] = 1; //second quadrant (top left)

//****************Maybe you should have an initial difference between prev and psi?!?!?!?!?!?!??!?!?!?!??@?%$??$?@#$@#$
//$%#@$%^@%&#$%U$%^&#$%&%^#$U$@%^U@#&%^@#%YUH#%&$@#&$@#&$U@#^YH



//*****************************************************************************************************
//*****************************************************************************************************

	//Start Calculations?????


	for(int k = 0; k<Max; k++)
	{
						//calculates future psi
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

					//	if(k%mod==0)
					//	{

								of.open(make_filename( "/home/dk0r/git/musical-phys/2D_wave-equation/csv/psi", ".csv" ).c_str());

									for(int i=0; i<n ;i++)
									 {
										 for(int j=0; j<n ;j++)
										 {
											 {
												of << i << "," << j << "," << psi[i][j] << "\n";
											 }
										 }
									 }

									of.close();
					//	}

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
		 cout << "some shit\n";
		wave();
		 return 0;
	 }
