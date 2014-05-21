#ifndef ONEDWAVECLASS_H
#define ONEDWAVECLASS_H

#include <Windows.h>
#include "WaveDefines.h"
#include "OneDWaveProc.h"
#include "WaveSimHeader.h"




class OneDSourceClass;

// this is a class that holds all of the specific plot information for
// a one dimensional wave simualtion
// it holds all the axis limits, the wave velocity, and stores all the point sources
class OneDSourceClass
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

	double WaveVelocity;

	int IncludeInPlot;

	int Direction;



	OneDSourceClass()
	{

		Direction = 1;

		Amplitude = 0;

		Frequency = 5;

		StartingX = 0;

		PhaseConst = 0;

		PhaseConstPerc = 0;

		IncludeInPlot = 0;
		


	}


	void ZeroClass()
	{

		Direction = 1;

		Amplitude = 0;

		Frequency = 5;

		StartingX = 0;

		PhaseConst = 0;

		PhaseConstPerc = 0;

		IncludeInPlot = 0;

	}








};








class OneDWaveMedium
{

public:

	 double WaveVelocity;					// the velocity of the waves in the medium

	double LowerX,UpperX,LowerY,UpperY;		// the x and y axis limits

	double STime,ETime;						// start and end time of the simulation

	double SimSpeed;						// the playback speed of the simulation



	// ADVANCED PLOT OPTIONS

	double LowerZ,UpperZ;					// the x axis limits

	double Resolution;						// how finely we make the meshgrid

	char BCKGRND,MESH,COLORSTREAM;			// advanced color options for the plot

	LPWSTR VelString;


	OneDSourceClass WAVESOURCES[4];


	bool SetYAxis;
	



					// FUNCTIONS TO SET AND STORE THE ABOVE VARIABLES	


	OneDWaveMedium()
	{

		WAVESOURCES[0].NAME = 'A';
		WAVESOURCES[1].NAME = 'B';
		WAVESOURCES[2].NAME = 'C';
		WAVESOURCES[3].NAME = 'D';

		WaveVelocity = 10.0;
		LowerX = -10; UpperX = 10;
		

		VelString = L"10";
		COLORSTREAM = '0';
		BCKGRND = '0';
		MESH = '0';
		LowerY = 0;
		UpperY = 0;

		STime = 0;

		ETime = 15;

		SimSpeed = 100;

		SetYAxis = 0;
		

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

	double ReturnWaveVelocity()
	{

		return WaveVelocity;

	}





	void ZeroClass()
	{

		WAVESOURCES[0].NAME = 'A';
		WAVESOURCES[1].NAME = 'B';
		WAVESOURCES[2].NAME = 'C';
		WAVESOURCES[3].NAME = 'D';

		WaveVelocity = 10.0;
		LowerX = -10; UpperX = 10;
		

		VelString = L"10";
		COLORSTREAM = '0';
		BCKGRND = '0';
		MESH = '0';
		LowerY = 0;
		UpperY = 0;

		STime = 0;

		ETime = 15;

		SimSpeed = 100;


		SetYAxis = 0;
		

	}




};























#endif