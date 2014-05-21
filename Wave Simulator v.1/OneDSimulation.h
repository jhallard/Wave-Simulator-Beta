#ifndef ONEDSIMULATION_H
#define ONEDSIMULATION_H


#include <engine.h>
#include <cmath>
#include "OneDWaveClass.h"


#pragma comment ( lib, "libmat.lib" ) 
#pragma comment ( lib, "libmx.lib" ) 
#pragma comment ( lib, "libmex.lib" ) 
#pragma comment ( lib, "libeng.lib" ) 


using namespace std;


void Copy1DMedium( OneDWaveMedium &CopyMedium,OneDWaveMedium &UserMedium);
void Copy1DSource(int,int Num, OneDWaveMedium &CopyMedium, OneDWaveMedium &UserMedium);

void OneDWaveSimulation(int Num, OneDWaveMedium &Medium)
{


	// opens the matlab engine

	Engine *m_pEngine;
	 m_pEngine = engOpen("null");


	OneDWaveMedium HoldMedium;	// we don't want to work with the user medium, we will copy it to ours


	// THIS NEXT PART FINDS WHICH 
	int CheckedWaveSources[4];
	int holdjjj = 0;				// holds the number of wave sources being used through the loop
	for(int iii = 0; iii < Num;iii ++)
	{

		if(Medium.WAVESOURCES[iii].IncludeInPlot != 0)
		{CheckedWaveSources[holdjjj] = iii;holdjjj++;}

	}// end for loop finding which wave sources are going to be used


	// this copies the medium to our medium
		Copy1DMedium(HoldMedium,Medium);

		for(int iii = 0;iii < holdjjj;iii++)
		{
			// this copies all the wave sources so our new medium
			Copy1DSource(iii,CheckedWaveSources[iii],HoldMedium,Medium);

		}






		//############
		//##############
		//################
		//####################

		// NOW WE STAR ACTUALLY PASSING DATA TO MATLAB!!!

		//####################
		//################
		//#############
		//##########



		// WE START BY PASSING THE PLOT PARAMETERS


		// this next if is incase the user defined the Y axis limits, then we don't have to find the limits



	


		mxArray* LowerYLimit = mxCreateDoubleMatrix(1,1,mxREAL);
		mxArray* UpperYLimit = mxCreateDoubleMatrix(1,1,mxREAL);
		double* pUpperYLimit = mxGetPr(UpperYLimit);
		double* pLowerYLimit = mxGetPr(LowerYLimit);
		

		if(HoldMedium.SetYAxis == 0)
		{
		// now we find the maximum amplitude
		double TotalAmplitude = 0;
		double CurrentAmplitude = 0;
		for(int iii = 0;iii < holdjjj; iii++)
		{

			CurrentAmplitude = HoldMedium.WAVESOURCES[iii].Amplitude;
			TotalAmplitude += CurrentAmplitude;

		}// end for loop

		*pUpperYLimit = TotalAmplitude;
		*pLowerYLimit = -1.0*TotalAmplitude;
		engPutVariable(m_pEngine,"UpperYLim",UpperYLimit);
		engPutVariable(m_pEngine,"LowerYLim",LowerYLimit);

		}// end if the user did not specify y axis limits
		else{  // THIS ELSE HANDLES IF THE USER DID SPECIFY THE Y LIMITS

			*pUpperYLimit = HoldMedium.UpperY;
			*pLowerYLimit = HoldMedium.LowerY;
		
		engPutVariable(m_pEngine,"UpperYLim",UpperYLimit);
		engPutVariable(m_pEngine,"LowerYLim",LowerYLimit);



		}

		// PASS THE X LIMITS ON THE GRAPH
		mxArray* LowerXLimit = mxCreateDoubleMatrix(1,1,mxREAL);
		mxArray* UpperXLimit = mxCreateDoubleMatrix(1,1,mxREAL);
		double* pUpperXLimit = mxGetPr(UpperXLimit);
		double* pLowerXLimit = mxGetPr(LowerXLimit);

		*pUpperXLimit = HoldMedium.UpperX;
		*pLowerXLimit = HoldMedium.LowerX;
		
		engPutVariable(m_pEngine,"UpperXLim",UpperXLimit);
		engPutVariable(m_pEngine,"LowerXLim",LowerXLimit);
		

		// PASS THE TIME LIMITS FOR THE SIMULATION
		mxArray* STime = mxCreateDoubleMatrix(1,1,mxREAL);
		mxArray* ETime = mxCreateDoubleMatrix(1,1,mxREAL);
		mxArray* SIMSPEED = mxCreateDoubleMatrix(1,1,mxREAL);
		
		double* pSTime = mxGetPr(STime);
		double* pETime = mxGetPr(ETime);
		double* pSIMSPEED = mxGetPr(SIMSPEED);


		*pSTime = HoldMedium.STime;
		*pETime = HoldMedium.ETime;
		*pSIMSPEED = HoldMedium.SimSpeed;
		
		engPutVariable(m_pEngine,"STime",STime);
		engPutVariable(m_pEngine,"ETime",ETime);
		engPutVariable(m_pEngine,"SimSpeed",SIMSPEED);


		// NOW WE PASS THE AMPLITUDE FOR EACH WAVE SOURCE
		mxArray* SourceAmplitude[4];  
		double *pSourceAmplitude[4];
		
		for(int iii = 0;iii < holdjjj;iii ++)
		{

			SourceAmplitude[iii] = mxCreateDoubleMatrix(1,1,mxREAL);
			pSourceAmplitude[iii] = mxGetPr(SourceAmplitude[iii]);

			*pSourceAmplitude[iii] = HoldMedium.WAVESOURCES[iii].Amplitude;
			
			switch(iii)
			{

			case(0):
				engPutVariable(m_pEngine,"Amplitude0",SourceAmplitude[iii]);
				break;

			case(1):
				engPutVariable(m_pEngine,"Amplitude1",SourceAmplitude[iii]);
				break;

			case(2):
				engPutVariable(m_pEngine,"Amplitude2",SourceAmplitude[iii]);
				break;

			case(3):
				engPutVariable(m_pEngine,"Amplitude3",SourceAmplitude[iii]);
				break;


			}// end switch on iii inside pass amplitude


		}// end for loop to get each amplitude to 





		// NOW WE PASS THE WaveNumber FOR EACH WAVE SOURCE
		mxArray* WaveNumber[4];  
		double *pWaveNumber[4];
		
		for(int iii = 0;iii < holdjjj;iii ++)
		{

			WaveNumber[iii] = mxCreateDoubleMatrix(1,1,mxREAL);
			pWaveNumber[iii] = mxGetPr(WaveNumber[iii]);

			*pWaveNumber[iii] = HoldMedium.WAVESOURCES[iii].WaveNumber;
			
			switch(iii)
			{

			case(0):
				engPutVariable(m_pEngine,"WaveNumber0",WaveNumber[iii]);
				break;

			case(1):
				engPutVariable(m_pEngine,"WaveNumber1",WaveNumber[iii]);
				break;

			case(2):
				engPutVariable(m_pEngine,"WaveNumber2",WaveNumber[iii]);
				break;

			case(3):
				engPutVariable(m_pEngine,"WaveNumber3",WaveNumber[iii]);
				break;


			}// end switch on iii inside pass wave number


		}// end for loop to get each wavenumber to matlab






		// NOW WE PASS THE OMEGA FOR EACH WAVE SOURCE
		mxArray* Omega[4];  
		double *pOmega[4];
		
		for(int iii = 0;iii < holdjjj;iii ++)
		{

			Omega[iii] = mxCreateDoubleMatrix(1,1,mxREAL);
			pOmega[iii] = mxGetPr(Omega[iii]);

			*pOmega[iii] = HoldMedium.WAVESOURCES[iii].Omega;
			
			switch(iii)
			{

			case(0):
				engPutVariable(m_pEngine,"Omega0",Omega[iii]);
				break;

			case(1):
				engPutVariable(m_pEngine,"Omega1",Omega[iii]);
				break;

			case(2):
				engPutVariable(m_pEngine,"Omega2",Omega[iii]);
				break;

			case(3):
				engPutVariable(m_pEngine,"Omega3",Omega[iii]);
				break;


			}// end switch on iii inside pass wave number


		}// end for loop to get each omega to matlab





		// NOW WE PASS THE PHASECONST FOR EACH WAVE SOURCE
		mxArray* Phase[4];  
		double *pPhase[4];
		
		for(int iii = 0;iii < holdjjj;iii ++)
		{

			Phase[iii] = mxCreateDoubleMatrix(1,1,mxREAL);
			pPhase[iii] = mxGetPr(Phase[iii]);

			*pPhase[iii] = HoldMedium.WAVESOURCES[iii].PhaseConst;
			
			switch(iii)
			{

			case(0):
				engPutVariable(m_pEngine,"Phase0",Phase[iii]);
				break;

			case(1):
				engPutVariable(m_pEngine,"Phase1",Phase[iii]);
				break;

			case(2):
				engPutVariable(m_pEngine,"Phase2",Phase[iii]);
				break;

			case(3):
				engPutVariable(m_pEngine,"Phase3",Phase[iii]);
				break;


			}// end switch on iii inside pass wave number


		}// end for loop to get each phase to matlab




		// NOW WE PASS THE STARTING POINTS TO MATLAB!
		mxArray* StartingPointX[4];
		double *pStartX[4];
		for(int iii = 0;iii < holdjjj;iii ++)
		{

			StartingPointX[iii] = mxCreateDoubleMatrix(1,1,mxREAL);
			pStartX[iii] = mxGetPr(StartingPointX[iii]);

			*pStartX[iii] = HoldMedium.WAVESOURCES[iii].StartingX;
			
			switch(iii)
			{

			case(0):
				engPutVariable(m_pEngine,"STARTX0",StartingPointX[iii]);
				break;

			case(1):
				engPutVariable(m_pEngine,"STARTX1",StartingPointX[iii]);
				break;

			case(2):
				engPutVariable(m_pEngine,"STARTX2",StartingPointX[iii]);
				break;

			case(3):
				engPutVariable(m_pEngine,"STARTX3",StartingPointX[iii]);
				break;


			}// end switch on iii inside pass wave number


		}// end for loop to get each phase to matlab








		//########################
		//#########
		//#############################
		//##############
		//##################################
		//#################

		// NOW BEGINS THE DIFFERENT SIMULATION CODES!!!



		//########################
		//#########
		//#############################
		//##############
		//##################################
		//#################


		// THIS SWITCH IS ON THE NUMBER OF WAVE SOURCES
		// NEEDING TO BE ANIMATED
		// THIS IS BECAUSE EACH DIFFERENT COMBINATION NEEDS ITS OWN SPECS
		switch(holdjjj)
		{


			// case only one wave is being plotted
		case (1):{

			if(HoldMedium.WAVESOURCES[0].NAME == 'A')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'B')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'C')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'D')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source D' ");}

						engEvalString(m_pEngine,"  figure('units','normalized','outerposition',[0 0 1 1]);");
						engEvalString(m_pEngine," subplot('Position',[.91 .85 .04 .04]), p = -2:.1:2; q = sin(p); plot(p,q,'r'),hleg = legend(NAME1 ),set(hleg,'position',[.89 .83 .1 .1],'FontWeight','bold'),");//
			engEvalString(m_pEngine," AMP = Amplitude0; K = WaveNumber0; W = Omega0; PHI = Phase0;  ");
			engEvalString(m_pEngine,"LX = LowerXLim;UX = UpperXLim; LY = LowerYLim;  UY = UpperYLim;X =  LX:.1:UX,Y = AMP*sin(K*(X - STARTX0) - W*STime + PHI),subplot('Position',[.05 .11 .82 .8]), PLOT = plot(X,Y,'r','LineWidth',3),grid minor,title(' 1 Wave Source - 1D ','FontWeight','bold'),xlim([LX UX]),ylim([1.1*LY 1.1*UY]),set(PLOT,'YDataSource','Y','XDataSource','X');");
			engEvalString(m_pEngine,"Interval = .03*SimSpeed/100; for t = STime:Interval:ETime Y = AMP*sin(K*(X - STARTX0) - W*t + PHI), refreshdata(PLOT), drawnow; end;");


			//engEvalString(m_pEngine,"for t = STime:0.1:ETime;  Y = AMP*sin(2.3*X - W*t + PHI); plot(X,Y,'r');ylim([LY UY]);xlim([LX UX]); drawnow; end;");
				 }break;





			// case only 2 wave sources are being plotted
			case (2):{

			if(HoldMedium.WAVESOURCES[0].NAME == 'A')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'B')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'C')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'D')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source D' ");}



			if(HoldMedium.WAVESOURCES[1].NAME == 'A')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES[1].NAME == 'B')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES[1].NAME == 'C')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES[1].NAME == 'D')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source D' ");}

			engEvalString(m_pEngine," NAME3 = ' Sum of Other Sources '; ");

						engEvalString(m_pEngine,"  figure('units','normalized','outerposition',[0 0 1 1]);");
						engEvalString(m_pEngine," subplot('Position',[.89 .85 .05 .04]), p = -2:.1:2; q = sin(p); qq = cos(p), qqq = 2*sin(p), plot(p,q,'k',p,qq,'b',p,qqq,'r'),hleg = legend(NAME1,NAME2,NAME3),set(hleg,'position',[.86 .83 .13 .15],'FontWeight','bold'),");//
			engEvalString(m_pEngine," AMP = Amplitude0;AMP1 = Amplitude1; K = WaveNumber0; K1 = WaveNumber1; W = Omega0; W1 = Omega1; PHI = Phase0; PHI1 = Phase1 ");
			engEvalString(m_pEngine,"LX = LowerXLim;UX = UpperXLim; LY = LowerYLim;  UY = UpperYLim;X =  LX:.1:UX, Y1 = AMP*sin(K*(X - STARTX0) - W*STime + PHI),Y2 = AMP1*sin(K1*(X - STARTX1) - W1*STime + PHI1), Y3 = Y1 + Y2,subplot('Position',[.05 .11 .8 .85]), plot(X,Y1,'k',X,Y2,'b',X,Y3,'r','LineWidth',3),grid minor,title(' Wave Source 1D ','FontWeight','bold'),xlim([LX UX]),ylim([1.1*LY 1.1*UY]);");
			engEvalString(m_pEngine,"Interval = .03*SimSpeed/100; for t = STime:Interval:ETime  Y1 = AMP*sin(K*(X - STARTX0) - W*t + PHI),Y2 = AMP1*sin(K1*(X - STARTX1) - W1*t + PHI1), Y3 = Y1 + Y2, plot(X,Y1,'k',X,Y2,'b',X,Y3,'r','LineWidth',3),grid minor,title(' 2 Wave Sources - 1D ','FontWeight','bold'),xlim([LX UX]),ylim([1.1*LY 1.1*UY]),  drawnow; end;");


			//engEvalString(m_pEngine,"for t = STime:0.1:ETime;  Y = AMP*sin(2.3*X - W*t + PHI); plot(X,Y,'r');ylim([LY UY]);xlim([LX UX]); drawnow; end;");
				 }break;








				// case only 3 wave sources are being plotted
			case (3):{

			if(HoldMedium.WAVESOURCES[0].NAME == 'A')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'B')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'C')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'D')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source D' ");}



			if(HoldMedium.WAVESOURCES[1].NAME == 'A')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES[1].NAME == 'B')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES[1].NAME == 'C')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES[1].NAME == 'D')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source D' ");}


			if(HoldMedium.WAVESOURCES[2].NAME == 'A')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES[2].NAME == 'B')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES[2].NAME == 'C')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES[2].NAME == 'D')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source D' ");}




			engEvalString(m_pEngine," NAME4 = ' Sum of Other Sources '; ");

						engEvalString(m_pEngine,"  figure('units','normalized','outerposition',[0 0 1 1]);");
						engEvalString(m_pEngine," subplot('Position',[.89 .85 .05 .04]), p = -2:.1:2; q1 = sin(p); q2 = cos(p), q3 = 2*sin(p), q4 = sin(p), plot(p,q1,'k',p,q2,'b',p,q3,'g',p,q4,'r'),hleg = legend(NAME1,NAME2,NAME3,NAME4),set(hleg,'position',[.86 .82 .13 .16],'FontWeight','bold'),");//
			engEvalString(m_pEngine," AMP = Amplitude0;AMP1 = Amplitude1;AMP2 = Amplitude2; K = WaveNumber0; K1 = WaveNumber1;K2 = WaveNumber2; W = Omega0; W1 = Omega1;W2 = Omega2; PHI = Phase0; PHI1 = Phase1,PHI2 = Phase2, ");
			engEvalString(m_pEngine,"LX = LowerXLim;UX = UpperXLim; LY = LowerYLim;  UY = UpperYLim;X =  LX:.1:UX, Y1 = AMP*sin(K*(X - STARTX0) - W*STime + PHI),Y2 = AMP1*sin(K1*(X - STARTX1) - W1*STime + PHI1),    Y3 = AMP2*sin(K2*(X - STARTX2) - W2*STime + PHI2),    Y4 = Y1 + Y2 + Y3,subplot('Position',[.05 .11 .8 .85]), plot(X,Y1,'k',X,Y2,'b',X,Y3,'g',X,Y4,'r',LineWidth',3),grid minor,title(' Wave Source 1D ','FontWeight','bold'),xlim([LX UX]),ylim([1.1*LY 1.1*UY]);");
			engEvalString(m_pEngine,"Interval = .03*SimSpeed/100; for t = STime:Interval:ETime   Y1 = AMP*sin(K*(X - STARTX0) - W*t + PHI),Y2 = AMP1*sin(K1*(X - STARTX1) - W1*t + PHI1),    Y3 = AMP2*sin(K2*(X - STARTX2) - W2*t + PHI2),    Y4 = Y1 + Y2 + Y3, plot(X,Y1,'k',X,Y2,'b',X,Y3,'g',X,Y4,'r','LineWidth',3),   grid minor,title(' 3 Wave Sources - 1D ','FontWeight','bold'),xlim([LX UX]),ylim([1.1*LY 1.1*UY]),  drawnow; end;");


			//engEvalString(m_pEngine,"for t = STime:0.1:ETime;  Y = AMP*sin(2.3*X - W*t + PHI); plot(X,Y,'r');ylim([LY UY]);xlim([LX UX]); drawnow; end;");
				 }break;







					// case only 2 wave sources are being plotted
			case (4):{

			if(HoldMedium.WAVESOURCES[0].NAME == 'A')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'B')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'C')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES[0].NAME == 'D')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source D' ");}



			if(HoldMedium.WAVESOURCES[1].NAME == 'A')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES[1].NAME == 'B')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES[1].NAME == 'C')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES[1].NAME == 'D')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source D' ");}


			if(HoldMedium.WAVESOURCES[2].NAME == 'A')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES[2].NAME == 'B')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES[2].NAME == 'C')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES[2].NAME == 'D')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source D' ");}


			if(HoldMedium.WAVESOURCES[3].NAME == 'A')
			{engEvalString(m_pEngine, "NAME4 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES[3].NAME == 'B')
			{engEvalString(m_pEngine, "NAME4 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES[3].NAME == 'C')
			{engEvalString(m_pEngine, "NAME4 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES[3].NAME == 'D')
			{engEvalString(m_pEngine, "NAME4 = 'Wave Source D' ");}




			engEvalString(m_pEngine," NAME5 = ' Sum of Other Sources '; ");

						engEvalString(m_pEngine,"  figure('units','normalized','outerposition',[0 0 1 1]);");
						engEvalString(m_pEngine," subplot('Position',[.89 .85 .05 .05]), p = -2:.1:2; q1 = sin(p); q2 = cos(p), q3 = 2*sin(p), q4 = sin(p),q5 = sin(p), plot(p,q1,'k',p,q2,'b',p,q3,'g',p,q4,'c',p,q5,'r'),hleg = legend(NAME1,NAME2,NAME3,NAME4,NAME5),set(hleg,'position',[.86 .82 .13 .16],'FontWeight','bold'),");//
			engEvalString(m_pEngine," AMP = Amplitude0;AMP1 = Amplitude1;AMP2 = Amplitude2;AMP3 = Amplitude3;          K = WaveNumber0; K1 = WaveNumber1;K2 = WaveNumber2;K3 = WaveNumber3;          W = Omega0; W1 = Omega1;W2 = Omega2;W3 = Omega3;       PHI = Phase0; PHI1 = Phase1,PHI2 = Phase2,PHI3 = Phase3, ");
			engEvalString(m_pEngine,"LX = LowerXLim;UX = UpperXLim; LY = LowerYLim;  UY = UpperYLim;X =  LX:.1:UX, Y1 = AMP*sin(K*(X - STARTX0) - W*STime + PHI),Y2 = AMP1*sin(K1*(X - STARTX1) - W1*STime + PHI1),    Y3 = AMP2*sin(K2*(X - STARTX2) - W2*STime + PHI2),     Y4 = AMP3*sin(K3*(X - STARTX3) - W3*STime + PHI3),    Y5 = Y1 + Y2 + Y3 + Y4,subplot('Position',[.05 .11 .8 .85]), plot(X,Y1,'k',X,Y2,'b',X,Y3,'g',X,Y4,'c',X,Y5,'r',LineWidth',3),grid minor,title(' 4 Wave Sources - 1D ','FontWeight','bold'),xlim([LX UX]),ylim([1.1*LY 1.1*UY]);");
			engEvalString(m_pEngine,"Interval = .03*SimSpeed/100; for t = STime:Interval:ETime   Y1 = AMP*sin(K*(X - STARTX0) - W*t + PHI),Y2 = AMP1*sin(K1*(X - STARTX1) - W1*t + PHI1),    Y3 = AMP2*sin(K2*(X - STARTX2) - W2*t + PHI2),   Y4 = AMP3*sin(K3*(X - STARTX3) - W3*t + PHI3),     Y5 = Y1 + Y2 + Y3 + Y4, plot(X,Y1,'k',X,Y2,'b',X,Y3,'g',X,Y4,'c',X,Y5,'r','LineWidth',3),   grid minor,title(' 4 Wave Sources - 1D ','FontWeight','bold'),xlim([LX UX]),ylim([1.1*LY 1.1*UY]),  drawnow; end;");


			//engEvalString(m_pEngine,"for t = STime:0.1:ETime;  Y = AMP*sin(2.3*X - W*t + PHI); plot(X,Y,'r');ylim([LY UY]);xlim([LX UX]); drawnow; end;");
				 }break;





		}






}// end simulation function 1d















void Copy1DMedium( OneDWaveMedium &CopyMedium,OneDWaveMedium &UserMedium)
{

	CopyMedium.WaveVelocity = UserMedium.WaveVelocity;
	CopyMedium.LowerX = UserMedium.LowerX;
	CopyMedium.UpperX = UserMedium.UpperX;
	CopyMedium.LowerY = UserMedium.LowerY;
	CopyMedium.UpperY = UserMedium.UpperY;
	CopyMedium.STime = UserMedium.STime;
	CopyMedium.ETime = UserMedium.ETime;
	CopyMedium.SimSpeed = UserMedium.SimSpeed;
	CopyMedium.Resolution = UserMedium.Resolution;
	CopyMedium.MESH = UserMedium.MESH;
	CopyMedium.BCKGRND = UserMedium.BCKGRND;
	CopyMedium.COLORSTREAM = UserMedium.COLORSTREAM;
	CopyMedium.SetYAxis = UserMedium.SetYAxis;



	




}




void Copy1DSource(int iii,int Num, OneDWaveMedium &CopyMedium, OneDWaveMedium &UserMedium)
{


	//CopyMedium.WAVESOURCES[Num]   = UserMedium.WAVESOURCES[Num] 


	CopyMedium.WAVESOURCES[iii].NAME   = UserMedium.WAVESOURCES[Num].NAME;

	CopyMedium.WAVESOURCES[iii].Amplitude   = UserMedium.WAVESOURCES[Num].Amplitude; 

	CopyMedium.WAVESOURCES[iii].Frequency   = UserMedium.WAVESOURCES[Num].Frequency; 

	CopyMedium.WAVESOURCES[iii].Wavelength   = UserMedium.WAVESOURCES[Num].Wavelength; 

	CopyMedium.WAVESOURCES[iii].WaveNumber   = UserMedium.WAVESOURCES[Num].WaveNumber; 

	CopyMedium.WAVESOURCES[iii].Omega   = UserMedium.WAVESOURCES[Num].Omega; 

	CopyMedium.WAVESOURCES[iii].PhaseConst   = UserMedium.WAVESOURCES[Num].PhaseConst; 

	CopyMedium.WAVESOURCES[iii].StartingX   = UserMedium.WAVESOURCES[Num].StartingX; 
	
	CopyMedium.WAVESOURCES[iii].WaveVelocity   = UserMedium.WAVESOURCES[Num].WaveVelocity;





}




#endif
