//============================================================================
// Name        : Parabolic-2D.cpp
// Author      : dk0r
// Version     :
// Copyright   : 
// Description : See Numerical Recipes Section 2.4 page 56.
//============================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include <nr3.h>
#include <tridag.h>
#include <math.h>
#include <vector>

using namespace std;


///Option Flags
	bool displayInfo = false; // Displays Coefficient Matrices/Vectors
	bool debug = false; //Displays Intermediary Calculations
	bool fileIO = true; //Outputs txt files in format: "position, temperature"

///File I/O
	ofstream of;
	ofstream ofMIDI;

	int fileNameCounter = 0;
	string make_filename( const string& basename, const string& ext )
	  {
		  ostringstream result;
		 result  << basename << setw(3) << setfill('0') << fileNameCounter << ext;
		  fileNameCounter++;
		  return result.str();
	  }

///Parameters
	int const t = 100;   //Max number of time steps
	int const m = 10;   //Dimension of [m x m] square matrix
	double lmbd = 4;   //Definition:  Lambda = (Δx^2) / (k*Δt)
					   //Lambda represents diffusion coefficient including all
					   //physical (heat, k) and discretization coefficients (Δx^2 and Δt)
	double temp = 100;  // Initial Condition (temperature)
	int x = (m/2);  // Position of Initial Condition (temp)


//Explicit Matrix and Vector
	double E[m][m]; //Explicit Coefficient Matrix
	VecDoub e(m); //Explicit Temperature Vector


///Implicit tridiagonal matrix represented as vector for "tridag.h"
	   // tridag.h uses the following three vectors to represent tridiagonal matrices.
       // See pg.56, eqn 2.4.1 in Numerical Recipes for details
	VecDoub a(m); // upper diagonal
	VecDoub b(m); // main diagonal
	VecDoub c(m); // lower diagonal

	VecDoub u(m); //Implicit Vector

	VecDoub r(m); //Known product of Explicit Matrix (E) * Explicit Vector (e)


///Initializes all matrices/vectors
void initialize()
{
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<m; j++)
		{
			E[i][j] = 0;
			e[i] = 0;

			//Implicit tridiagonals
			a[i]=0;
			b[i]=0;
			c[i]=0;

			//Implicit Vector
			u[i]=0;
			//Implicit Solution
			r[i]=0;
		}
	}
}

//Fills all matrices/vectors with proper boundary/initial conditions and discretization coefficients
void fill()
{
	//////////////IMPLICIT Matrix and Vector

	///Installs Implicit tridiagonal Coefficient Matrix in the form of three vectors (a,b,c) for tridag.h

		//Installs first row of Implicit tridiagonal Coefficient Matrix
		a[0] = 99999999999999999; //a[0] does not exist in tridiagonal matrix. Do not use it!
		b[0] = 2+lmbd;
		c[0] = -1;

		//Installs remaining body of Implicit tridiagonal Matrix
		for(int i=1; i<(m-1); i++)
		{
			a[i] = -1;
			b[i] = 2+lmbd;
			c[i] = -1;
		}

		//Installs last row of Implicit tridiagonal Coefficient Matrix
		a[(m-1)] = -1;
		b[(m-1)] = (2+lmbd);
		c[(m-1)] = 99999999999999999; //c[m-1] does not exist in tridiagonal matrix. Do not use it!

		///Installs Boundary Conditions in the:
		//explicit vectors
		e[0] = 0;
		e[(m-1)]=0;
		r[0] = 0;
		r[(m-1)]=0;
		//and implicit vector
		u[0]=0;
		u[(m-1)]=0;




	/////////////////EXPLICIT Matrix and Vector


	//Installs First line of Explicit Coefficient Matrix (E)
		E[0][0]=(lmbd-2);
		E[0][1]=1;

	//Installs remaining body of Explicit Coefficient Matrix (E) (E is never modified)
	for(int i=1; i<(m-1); i++)
	{
		E[i][i]=(lmbd-2);
		E[i][i+1] = 1;
		E[i][i-1]=1;
	}

	//Installs Last line of Explicit Coefficient Matrix (E)
		E[m-1][m-2]=1;
		E[m-1][m-1]=(lmbd-2);


	//Installs Initial Condition
		for (x=m/2-3; x< m/2+3; x++) e[x] = temp;


											///Displays contents of Implicit and Explicit Matrices and the Initial Explicit Vector
												if(displayInfo==true)
												{
													cout << endl << "Implicit Coefficient Matrix (represented using 3 Vectors per the tridag.h method)" << endl << "(Note: 1.vectors don't change over time  2.ignore a[0] and c[10]):" << endl;
															for(int i=0; i<m; i++)
															{
																cout << "a["<<i<<"],b["<<i<<"],c["<<i<<"] = " << a[i] << " , " << b[i] << " , " << c[i] << endl;
															}

													cout << endl << endl << "Explicit Coefficient Matrix E[i][j] (Note: doesn't change over time):" << endl;

													for(int i=0; i<m; i++)
													{
														for(int j=0; j<m; j++)
														{
															cout << E[i][j] << " ";
														}
														cout << endl;
													}

													cout << endl << "Initial Explicit Vector e[i]:" << endl << "(Note: Changes over time):" << endl;
													for(int i=0; i<m; i++)
														cout << "e["<<i<<"] = " << e[i] << endl;
												}

}

void crankNicolson()
{
		//Defines r[] vector by multiplying Explicit matrix by explicit vector (  E[][] * e[]  )
		for(int i=0; i<m; i++)
		{
		  r[i]=0.0;
		  for(int j=0; j<m; j++)
		    {
		      r[i] += E[i][j]*e[j];
		      ///Debug Info
		      if(debug==true){
			cout << "r[" << i << "] calculation:" << endl;
			cout << "E["<<i<<"]["<<j<<"] * e["<<j<<"] = r[" << i << "]" << endl;
			cout << E[i][j] << " * " << e[j] << " = " << r[i] << endl << endl;}
		    }
		}


		///Installs Boundary Conditions in the:
		//explicit vectors
		//e[0] = 0;
		//e[(m-1)]=0;
		//r[0] = 0;
		//r[(m-1)]=0;
		//and implicit vector
		//u[0]=0;
		//u[(m-1)]=0;



		//Solves matrix equation for implicit u[i] vector. [tridag does not modify a, b, c or r]
		tridag(a,b,c,r,u);




		///Installs Boundary Conditions in the:
		//explicit vectors
		//e[0] = 0;
		//e[(m-1)]=0;
		//r[0] = 0;
		//r[(m-1)]=0;
		//and implicit vector
		//u[0]=0;
		//u[(m-1)]=0;


		//Writes implicit (forward time) solution into explicit (current time) vector
		//for the next time iteration.
		for(int i=0; i<m; i++)
		{
		  e[i] = u[i];
		}
}

//A 3x3 test to confirm operation of tridag.h
void tridagTest()
{
	r[0]=0;
	r[1]=10;
	r[2]=0;

	tridag(a,b,c,r,u);

	for(int i=0; i<3; i++)
	{
		cout << "u["<<i<<"] = " << u[i] << endl;
	}
	cout << "Above you should see u(x,y,z) = <0.29, 1.76, 0.29> for lmbd=4" << endl;
}

int main()
{
	//Zero's out all vectors/matrices
	initialize();
	cout <<"initialized" <<endl << endl;

	//Fills all matrices and vectors with boundary/initial condition(s) and discretization coefficients
	fill();
	cout << "filled" <<endl << endl;



	//File I/O (Outputs initial condition: t=0)
	if(fileIO==true)
	of.open(make_filename( "rod-", ".txt" ).c_str());

	//	cout << "u[x,t] ≡ Temperatures @ position x and time t along a 1D rod:  " << endl << endl;

	for(int j=0; j<m; j++)
	{
		if(fileIO==true)
		of << j << " " << e[j] << endl;

		//		cout << "u["<<j<<",0]:  " << e[j] << endl;
	}
	//	cout << endl << endl;
		if(fileIO==true)
		of.close();



	//Iterates Solution
	for(int i=1; i<t; i++)
	{

		//Crank Nicolson Solution Method
		crankNicolson();

			///File I/O: Outputs time step evolutions
			if(fileIO==true)
			of.open(make_filename( "rod-", ".txt" ).c_str());

			//			cout << "u[x,t] ≡ Temperatures @ position x and time t along a 1D rod:  " << endl << endl;

			for(int j=0; j<m; j++)
			{
				if(fileIO==true)
				of << j << " " << u[j] << endl;

				//cout << "u[" <<j<< "," <<i<< "]:  " << u[j] << endl;
			}
			cout << endl << endl;

			if(fileIO==true)
			of.close();
	}

	cout << endl << "Crank-Nicolson complete" <<endl;

	return 0;
}
