#ifndef TWODWAVECLASS_H
#define TWODWAVECLASS_H

#include <Windows.h>
#include "WaveDefines.h"
#include "TwoDWaveProc.h"
#include "WaveSimHeader.h"


class TwoDSourceClass;

// this is a class that holds all of the specific plot information for
// a one dimensional wave simualtion
// it holds all the axis limits, the wave velocity, and stores all the point sources
class TwoDSourceClass
{


public:

	wchar_t NAME;

	double Amplitude;

	double Frequency;

	

	double Wavelength;

	double WaveNumber;

	double Omega;

	double PhaseConst;

	double PhaseConstPerc;

	double StartingX;

	double StartingY;

	double WaveVelocity;

	int IncludeInPlot;

	bool RadialDamping;

	bool TimeDamping;

	int TimeDampingRate;



	TwoDSourceClass()
	{
		Amplitude = 2;

		Frequency = 2 ;

		StartingX = 0;

		StartingY = 0;

		PhaseConst = 0;

		PhaseConstPerc = 0;

		IncludeInPlot = 0;
		
		RadialDamping = 1;

		TimeDamping = 0;

		TimeDampingRate = 1000;


		


	}








	void ZeroClass()
	{
		Amplitude = 2;

		Frequency = 2 ;

		StartingX = 0;

		StartingY = 0;

		PhaseConst = 0;

		PhaseConstPerc = 0;

		IncludeInPlot = 0;
		
		RadialDamping = 1;

		TimeDamping = 0;

		TimeDampingRate = 1000;

		

	}







};



class TwoDWaveMedium
{

public:

	 double WaveVelocity;					// the velocity of the waves in the medium

	 double LowerX;
	 double UpperX;
	 double LowerY;
	double UpperY;		// the x and y axis limits

	double STime,ETime;						// start and end time of the simulation

	double SimSpeed;						// the playback speed of the simulation



	// ADVANCED PLOT OPTIONS

	double LowerZ,UpperZ;					// the x axis limits

	double Resolution;						// how finely we make the meshgrid

	char BCKGRND,MESH,COLORSTREAM;			// advanced color options for the plot

	LPWSTR VelString;


	TwoDSourceClass WAVESOURCES2[4];


	bool SetZAxis;
					// FUNCTIONS TO SET AND STORE THE ABOVE VARIABLES	


	TwoDWaveMedium()
	{

		WaveVelocity = 10.0;
		//LowerX = -10; UpperX = 10;
		//LowerY = -10; UpperY = 10;
		LowerZ = 0; UpperZ = 0;

		VelString = L"10";

		LowerZ = 0;
		UpperZ = 0;

		WAVESOURCES2[0].NAME = 'A';
		WAVESOURCES2[1].NAME = 'B';
		WAVESOURCES2[2].NAME = 'C';
		WAVESOURCES2[3].NAME = 'D';

		STime = 0;

		ETime = 15;

		SimSpeed = 100;

		COLORSTREAM = '0';
		BCKGRND = '0';
		MESH = '0';
		
		SetZAxis = 0;

	}


	void SetVelString(wchar_t c,int num)
	{

		VelString[num] = c;


	}

	int SetWaveVelocity(double WaveSpeed)
	{

		if(WaveSpeed > 0 && WaveSpeed < 1000)
		{WaveVelocity = WaveSpeed;return 0;}
		else{return -1;}

	}


	int SetAxisLimits(double lx,double ux, double ly, double uy)
	{

		if(lx < ux && ly < uy)
		{LowerX = lx;UpperX = ux; LowerY = ly; UpperY = uy;return 0;}
		else{return -1;}

	}

	double ReturnWaveVelocity()
	{

		return WaveVelocity;

	}






	void ZeroClass()
	{

		WaveVelocity = 10.0;
		//LowerX = -10; UpperX = 10;
		//LowerY = -10; UpperY = 10;
		LowerZ = 0; UpperZ = 0;

		VelString = L"10";

		LowerZ = 0;
		UpperZ = 0;

		WAVESOURCES2[0].NAME = 'A';
		WAVESOURCES2[1].NAME = 'B';
		WAVESOURCES2[2].NAME = 'C';
		WAVESOURCES2[3].NAME = 'D';

		STime = 0;

		ETime = 15;

		SimSpeed = 100;

		COLORSTREAM = '0';
		BCKGRND = '0';
		MESH = '0';

		SetZAxis = 0;
		

	}


};






#endif