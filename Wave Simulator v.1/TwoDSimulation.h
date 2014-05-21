#ifndef TWODSIMULATION_H
#define TWODSIMULATION_H


#include <engine.h>
#include <cmath>
#include "TwoDWaveClass.h"


#pragma comment ( lib, "libmat.lib" ) 
#pragma comment ( lib, "libmx.lib" ) 
#pragma comment ( lib, "libmex.lib" ) 
#pragma comment ( lib, "libeng.lib" ) 


using namespace std;


void Copy2DMedium( TwoDWaveMedium &CopyMedium, TwoDWaveMedium &UserMedium);
void Copy2DSource(int,int Num, TwoDWaveMedium &CopyMedium, TwoDWaveMedium &UserMedium);
double IsDamped(int Num,TwoDWaveMedium &HoldMedium);

void TwoDWaveSimulation(int Num, TwoDWaveMedium &Medium)
{


	// opens the matlab engine

	Engine *m_pEngine;
	 m_pEngine = engOpen("null");


	TwoDWaveMedium HoldMedium;	// we don't want to work with the user medium, we will copy it to ours


	// THIS NEXT PART FINDS WHICH 
	int CheckedWAVESOURCES2[4];
	int holdjjj = 0;				// holds the number of wave sources being used through the loop
	for(int iii = 0; iii < Num;iii ++)
	{

		if(Medium.WAVESOURCES2[iii].IncludeInPlot != 0)
		{CheckedWAVESOURCES2[holdjjj] = iii;holdjjj++;}

	}// end for loop finding which wave sources are going to be used


	// this copies the medium to our medium
		Copy2DMedium(HoldMedium,Medium);

		for(int iii = 0;iii < holdjjj;iii++)
		{
			// this copies all the wave sources so our new medium
			Copy2DSource(iii,CheckedWAVESOURCES2[iii],HoldMedium,Medium);

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



	


		mxArray* LowerZLimit = mxCreateDoubleMatrix(1,1,mxREAL);
		mxArray* UpperZLimit = mxCreateDoubleMatrix(1,1,mxREAL);
		double* pUpperZLimit = mxGetPr(UpperZLimit);
		double* pLowerZLimit = mxGetPr(LowerZLimit);
		

		if(HoldMedium.SetZAxis == 0)
		{
		// now we find the maximum amplitude
		double TotalAmplitude = 0;
		double CurrentAmplitude = 0;
		for(int iii = 0;iii < holdjjj; iii++)
		{

			CurrentAmplitude = HoldMedium.WAVESOURCES2[iii].Amplitude;
			TotalAmplitude += CurrentAmplitude;

		}// end for loop

		*pUpperZLimit = TotalAmplitude;
		*pLowerZLimit = -1.0*TotalAmplitude;
		engPutVariable(m_pEngine,"UpperZLim2",UpperZLimit);
		engPutVariable(m_pEngine,"LowerZLim2",LowerZLimit);

		}// end if the user did not specify y axis limits
		else{  // THIS ELSE HANDLES IF THE USER DID SPECIFY THE Y LIMITS

			*pUpperZLimit = HoldMedium.UpperZ;
			*pLowerZLimit = HoldMedium.LowerZ;
		
		engPutVariable(m_pEngine,"UpperZLim2",UpperZLimit);
		engPutVariable(m_pEngine,"LowerZLim2",LowerZLimit);



		}

		// PASS THE X and Y LIMITS ON THE GRAPH
		mxArray* LowerXLimit = mxCreateDoubleMatrix(1,1,mxREAL);
		mxArray* UpperXLimit = mxCreateDoubleMatrix(1,1,mxREAL);
		mxArray* LowerYLimit = mxCreateDoubleMatrix(1,1,mxREAL);
		mxArray* UpperYLimit = mxCreateDoubleMatrix(1,1,mxREAL);
		
		double* pUpperXLimit = mxGetPr(UpperXLimit);
		double* pLowerXLimit = mxGetPr(LowerXLimit);
		double* pUpperYLimit = mxGetPr(UpperYLimit);
		double* pLowerYLimit = mxGetPr(LowerYLimit);

		*pUpperXLimit = Medium.UpperX;
		*pLowerXLimit = Medium.LowerX;

		*pUpperYLimit = Medium.UpperY;
		*pLowerYLimit = Medium.LowerY;
		
		engPutVariable(m_pEngine,"UpperXLim2",UpperXLimit);
		engPutVariable(m_pEngine,"LowerXLim2",LowerXLimit);

		engPutVariable(m_pEngine,"UpperYLim2",UpperYLimit);
		engPutVariable(m_pEngine,"LowerYLim2",LowerYLimit);
		



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

			*pSourceAmplitude[iii] = HoldMedium.WAVESOURCES2[iii].Amplitude;
			
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

			*pWaveNumber[iii] = HoldMedium.WAVESOURCES2[iii].WaveNumber;
			
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

			*pOmega[iii] = HoldMedium.WAVESOURCES2[iii].Omega;
			
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

			*pPhase[iii] = HoldMedium.WAVESOURCES2[iii].PhaseConst;
			
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

			*pStartX[iii] = HoldMedium.WAVESOURCES2[iii].StartingX;
			
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


		}// end for loop to get each starting x to matlab



		// NOW WE PASS THE STARTING POINTS TO MATLAB!
		mxArray* StartingPointY[4];
		double *pStartY[4];
		for(int iii = 0;iii < holdjjj;iii ++)
		{

			StartingPointY[iii] = mxCreateDoubleMatrix(1,1,mxREAL);
			pStartY[iii] = mxGetPr(StartingPointY[iii]);

			*pStartY[iii] = HoldMedium.WAVESOURCES2[iii].StartingY;
			
			switch(iii)
			{

			case(0):
				engPutVariable(m_pEngine,"STARTY0",StartingPointY[iii]);
				break;

			case(1):
				engPutVariable(m_pEngine,"STARTY1",StartingPointY[iii]);
				break;

			case(2):
				engPutVariable(m_pEngine,"STARTY2",StartingPointY[iii]);
				break;

			case(3):
				engPutVariable(m_pEngine,"STARTY3",StartingPointY[iii]);
				break;


			}// end switch on iii inside pass wave number


		}// end for loop to get each starting y to matlab







		// DAMPING COEFFECIENTS

		mxArray* RadialDamp1[4];
		double *pRadialDamp1[4];
		for(int iii = 0;iii < holdjjj; iii++)
		{

			RadialDamp1[iii] = mxCreateDoubleMatrix(1,1,mxREAL);
			pRadialDamp1[iii] = mxGetPr(RadialDamp1[iii]);

			
			
				*pRadialDamp1[iii] = HoldMedium.WAVESOURCES2[iii].RadialDamping;
			
		
			switch(iii)
			{

			case(0):
				engPutVariable(m_pEngine,"RDAMP0",RadialDamp1[iii]);
				break;

			case(1):
				engPutVariable(m_pEngine,"RDAMP1",RadialDamp1[iii]);
				break;

			case(2):
				engPutVariable(m_pEngine,"RDAMP2",RadialDamp1[iii]);
				break;

			case(3):
				engPutVariable(m_pEngine,"RDAMP3",RadialDamp1[iii]);
				break;


			}// end switch on iii inside pass wave number


		}// end for loop to get radial damping coeff to matlab








		
		mxArray* TimeDamp[4];
		double *pTimeDamp[4];
		for(int iii = 0;iii < holdjjj;iii ++)
		{

			TimeDamp[iii] = mxCreateDoubleMatrix(1,1,mxREAL);
			pTimeDamp[iii] = mxGetPr(TimeDamp[iii]);

			
				*pTimeDamp[iii] = HoldMedium.WAVESOURCES2[iii].TimeDamping;
			
			
			
			
			switch(iii)
			{
				
			case(0):
				engPutVariable(m_pEngine,"TDAMP0",TimeDamp[iii]);
				break;

			case(1):
				engPutVariable(m_pEngine,"TDAMP1",TimeDamp[iii]);
				break;

			case(2):
				engPutVariable(m_pEngine,"TDAMP2",TimeDamp[iii]);
				break;

			case(3):
				engPutVariable(m_pEngine,"TDAMP3",TimeDamp[iii]);
				break;


			}// end switch on iii inside pass wave number


		}// end for loop to get time damping coeff to matlab












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

		
		engEvalString(m_pEngine," XVIEW = 10, YVIEW = 0, ZVIEW = 0,");


		int CAX = IsDamped(holdjjj, HoldMedium);

mxArray* ColorAxis = mxCreateDoubleMatrix(1,1,mxREAL);
double* pColorAxis = mxGetPr(ColorAxis);

*pColorAxis = CAX;

engPutVariable(m_pEngine,"CAX",ColorAxis);
engEvalString(m_pEngine,"LCAX = -CAX, UCAX = CAX");


		// THIS SWITCH IS ON THE NUMBER OF WAVE SOURCES
		// NEEDING TO BE ANIMATED
		// THIS IS BECAUSE EACH DIFFERENT COMBINATION NEEDS ITS OWN SPECS
		switch(holdjjj)
		{


			



			// case only one wave is being plotted
		case (1):{

			if(HoldMedium.WAVESOURCES2[0].NAME == 'A')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'B')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'C')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'D')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source D' ");}

			


						engEvalString(m_pEngine,"  figure('units','normalized','outerposition',[0 0 1 1]),");
						engEvalString(m_pEngine," subplot('Position',[.91 .85 .04 .04]), p = -2:.1:2; q = sin(p); plot(p,q,'k'),hleg = legend(NAME1 ),set(hleg,'position',[.89 .83 .1 .1],'FontWeight','bold'),");//
			engEvalString(m_pEngine," AMP = Amplitude0; K = WaveNumber0; W = Omega0; PHI = Phase0,  ");
			engEvalString(m_pEngine,"LX = LowerXLim2;UX = UpperXLim2; LY = LowerYLim2; UY = UpperYLim2;UZ = UpperZLim2; LZ = LowerZLim2,");
			engEvalString(m_pEngine,"RES = .8*(UX/80 - LX/80 + UY/80 - LY/80),x = LX:RES:UX, y = LY:RES:UY, [X,Y] = meshgrid(x,y), R = sqrt((X - STARTX0).^2 + (Y-STARTY0).^2), ARROWX0 = [STARTX0 STARTX0], ARROWY0 = [STARTY0 STARTY0], ARROWZ0 = [1.8*LCAX 1.8*UCAX],");
			

		

			//*(1./(1+RDAMP0.*R))*(1/(1+TDAMP0*t))*
			engEvalString(m_pEngine," Z = (1./(1+RDAMP0*R)).*(AMP*(1/(1+TDAMP0*t))*sin(K*R - W*STime + PHI)),subplot('Position',[.05 .11 .82 .8]),surf(X,Y,Z),grid minor,title(' 1 Wave Source - 2D ','FontWeight','bold'),xlim([LX UX]),ylim([LY UY]),zlim([1.9*LCAX 1.9*UCAX]),caxis([LCAX UCAX]),hold on, plot3(ARROWX0,ARROWY0,ARROWZ0,'b','LineWidth',6),hold off,");
			engEvalString(m_pEngine,"Interval = .04*SimSpeed/100; for t = STime:Interval:ETime Z = (1./(1+(RDAMP0*R))).*(AMP*(1/(1+(TDAMP0*t)))*sin(K*R - W*t + PHI)), surf(X,Y,Z),xlim([LX UX]),ylim([LY UY]),zlim([1.9*LCAX 1.9*UCAX]),caxis([LCAX UCAX]),grid minor, view([10-XVIEW*t 50-YVIEW*t 25-40*abs(sin(ZVIEW*3.14*t/ETime))]),title(' 1 Wave Source - 2D ','FontWeight','bold'), hold on, plot3(ARROWX0,ARROWY0,ARROWZ0,'k','LineWidth',7),hold off, drawnow, end,");

			
				 }break;





			// case only 2 wave sources are being plotted
			case (2):{

			if(HoldMedium.WAVESOURCES2[0].NAME == 'A')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'B')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'C')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'D')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source D' ");}



			if(HoldMedium.WAVESOURCES2[1].NAME == 'A')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES2[1].NAME == 'B')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES2[1].NAME == 'C')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES2[1].NAME == 'D')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source D' ");}




				engEvalString(m_pEngine,"  figure('units','normalized','outerposition',[0 0 1 1]),;");
						engEvalString(m_pEngine," subplot('Position',[.91 .84 .04 .02]), p = -2:.1:2; q = sin(p); q1 = sin(p), plot(p,q,'k',p,q1,'c'),hleg = legend(NAME1,NAME2 ),set(hleg,'position',[.89 .8 .1 .1],'FontWeight','bold'),");//
			engEvalString(m_pEngine," AMP0 = Amplitude0;AMP1 = Amplitude1;     K0 = WaveNumber0;K1 = WaveNumber1;     W0 = Omega0; W1 = Omega1;    PHI0 = Phase0; PHI1 = Phase1;  ");
			engEvalString(m_pEngine,"LX = LowerXLim2;UX = UpperXLim2; LY = LowerYLim2; UY = UpperYLim2;UZ = UpperZLim2; LZ = LowerZLim2,");
			engEvalString(m_pEngine,"RES = .8*(UX/80 - LX/80 + UY/80 - LY/80),x = LX:RES:UX, y = LY:RES:UY, [X,Y] = meshgrid(x,y), R0 = sqrt((X - STARTX0).^2 + (Y-STARTY0).^2),R1 = sqrt((X - STARTX1).^2 + (Y - STARTY1).^2), ARROWX0 = [STARTX0 STARTX0], ARROWY0 = [STARTY0 STARTY0],ARROWX1 = [STARTX1 STARTX1], ARROWY1 = [STARTY1 STARTY1], ARROWZ = [1.8*LCAX 1.8*UCAX],;");
			
			
	

			//*(1./(1+RDAMP0.*R))*(1/(1+TDAMP0*t))*
			engEvalString(m_pEngine," Z =    (1./(1+RDAMP0*R0)).*(AMP0*(1/(1+TDAMP0*t))*sin(K0*R0 - W0*STime + PHI0))  +  (1./(1+RDAMP1*R1)).*(AMP1*(1/(1+TDAMP1*t))*sin(K1*R1 - W1*STime + PHI1))   ,subplot('Position',[.05 .11 .82 .8]),surf(X,Y,Z),grid minor,title(' 2 Wave Sources - 2D ','FontWeight','bold'),xlim([LX UX]),ylim([LY UY]),zlim([1.9*LCAX 1.9*UCAX]),caxis([LCAX UCAX]),hold on, plot3(ARROWX0,ARROWY0,ARROWZ,'b',ARROWX1,ARROWY1,ARROWZ,'c','LineWidth',6),hold off;");
			engEvalString(m_pEngine,"Interval = .04*SimSpeed/100; for t = STime:Interval:ETime Z =   ( (1./(1+(RDAMP0*R0))).*(AMP0*(1/(1+(.5*TDAMP0*t)))*sin(K0*R0 - W0*t + PHI0)) + (1./(1+RDAMP1*R1)).*(AMP1*(1/(1+TDAMP1*t))*sin(K1*R1 - W1*t + PHI1))  ), surf(X,Y,Z),grid minor, xlim([LX UX]),ylim([LY UY]),zlim([1.9*LCAX 1.9*UCAX]),caxis([LCAX UCAX]),view([20-XVIEW*t 40-YVIEW*t 25-40*abs(sin(ZVIEW*3.14*t/ETime))]),title(' 2 Wave Sources - 2D ','FontWeight','bold'), hold on, plot3(ARROWX0,ARROWY0,ARROWZ,'k',ARROWX1,ARROWY1,ARROWZ,'c','LineWidth',7),hold off, drawnow, end;");


						

			//engEvalString(m_pEngine,"for t = STime:0.1:ETime;  Y = AMP*sin(2.3*X - W*t + PHI); plot(X,Y,'r');ylim([LY UY]);xlim([LX UX]); drawnow; end;");
				 }break;








				// case only 3 wave sources are being plotted
			case (3):{

			if(HoldMedium.WAVESOURCES2[0].NAME == 'A')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'B')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'C')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'D')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source D' ");}



			if(HoldMedium.WAVESOURCES2[1].NAME == 'A')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES2[1].NAME == 'B')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES2[1].NAME == 'C')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES2[1].NAME == 'D')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source D' ");}


			if(HoldMedium.WAVESOURCES2[2].NAME == 'A')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES2[2].NAME == 'B')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES2[2].NAME == 'C')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES2[2].NAME == 'D')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source D' ");}







				engEvalString(m_pEngine,"  figure('units','normalized','outerposition',[0 0 1 1]),;");
						engEvalString(m_pEngine," subplot('Position',[.91 .84 .04 .02]), p = -2:.1:2; q = sin(p); q1 = sin(p),q2 = sin(p), plot(p,q,'k',p,q1,'c',p,q2,'r'),hleg = legend(NAME1,NAME2,NAME3 ),set(hleg,'position',[.89 .8 .1 .1],'FontWeight','bold'),");//
			engEvalString(m_pEngine," AMP0 = Amplitude0;AMP1 = Amplitude1;AMP2 = Amplitude2;     K0 = WaveNumber0;K1 = WaveNumber1;K2 = WaveNumber2;");
			engEvalString(m_pEngine," W0 = Omega0; W1 = Omega1;W2 = Omega2;    PHI0 = Phase0; PHI1 = Phase1,PHI2 = Phase2;  ");
			engEvalString(m_pEngine," LX = LowerXLim2;UX = UpperXLim2; LY = LowerYLim2; UY = UpperYLim2;UZ = UpperZLim2; LZ = LowerZLim2,");
			engEvalString(m_pEngine," RES = .8*(UX/80 - LX/80 + UY/80 - LY/80),x = LX:RES:UX, y = LY:RES:UY, [X,Y] = meshgrid(x,y), R0 = sqrt((X - STARTX0).^2 + (Y-STARTY0).^2),R1 = sqrt((X - STARTX1).^2 + (Y - STARTY1).^2),R2 = sqrt((X - STARTX2).^2 + (Y - STARTY2).^2),");
			engEvalString(m_pEngine," ARROWX0 = [STARTX0 STARTX0], ARROWY0 = [STARTY0 STARTY0],ARROWX1 = [STARTX1 STARTX1], ARROWY1 = [STARTY1 STARTY1],ARROWX2 = [STARTX2 STARTX2], ARROWY2 = [STARTY2 STARTY2], ARROWZ = [1.8*LCAX 1.8*UCAX],;");
		
			
				
		

			//*(1./(1+RDAMP0.*R))*(1/(1+TDAMP0*t))*
			engEvalString(m_pEngine," Z =    (1./(1+RDAMP0*R0)).*(AMP0*(1/(1+TDAMP0*t))*sin(K0*R0 - W0*STime + PHI0))  +  (1./(1+RDAMP1*R1)).*(AMP1*(1/(1+TDAMP1*t))*sin(K1*R1 - W1*STime + PHI1))   +  (1./(1+RDAMP2*R2)).*(AMP2*(1/(1+TDAMP2*t))*sin(K2*R2 - W2*STime + PHI2))   ,subplot('Position',[.05 .11 .82 .8]),surf(X,Y,Z),grid minor,title(' 3 Wave Sources - 2D ','FontWeight','bold'),xlim([LX UX]),ylim([LY UY]),zlim([1.8*LCAX 1.8*UCAX]),caxis([LCAX UCAX]),hold on, plot3(ARROWX0,ARROWY0,ARROWZ,'b',ARROWX1,ARROWY1,ARROWZ,'c',ARROWX2,ARROWY2,ARROWZ,'r','LineWidth',6),hold off;");
			engEvalString(m_pEngine,"Interval = .04*SimSpeed/100; for t = STime:Interval:ETime Z =    (1./(1+(RDAMP0*R0))).*(AMP0*(1/(1+(.5*TDAMP0*t)))*sin(K0*R0 - W0*t + PHI0)) + (1./(1+RDAMP1*R1)).*(AMP1*(1/(1+TDAMP1*t))*sin(K1*R1 - W1*t + PHI1))  +  (1./(1+RDAMP2*R2)).*(AMP2*(1/(1+TDAMP2*t))*sin(K2*R2 - W2*t + PHI2))  , surf(X,Y,Z),grid minor, xlim([LX UX]),ylim([LY UY]),zlim([1.8*LCAX 1.8*UCAX]),caxis([LCAX UCAX]),view([20-XVIEW*t 40-YVIEW*t 25-40*abs(sin(ZVIEW*3.14*t/ETime))]),title(' 3 Wave Sources - 2D ','FontWeight','bold'), hold on, plot3(ARROWX0,ARROWY0,ARROWZ,'k',ARROWX1,ARROWY1,ARROWZ,'c',ARROWX2,ARROWY2,ARROWZ,'r','LineWidth',7),hold off, drawnow, end;");


						




			//engEvalString(m_pEngine,"for t = STime:0.1:ETime;  Y = AMP*sin(2.3*X - W*t + PHI); plot(X,Y,'r');ylim([LY UY]);xlim([LX UX]); drawnow; end;");
				 }break;













					// case only 2 wave sources are being plotted
			case (4):{

			if(HoldMedium.WAVESOURCES2[0].NAME == 'A')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'B')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'C')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES2[0].NAME == 'D')
			{engEvalString(m_pEngine, "NAME1 = 'Wave Source D' ");}



			if(HoldMedium.WAVESOURCES2[1].NAME == 'A')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES2[1].NAME == 'B')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES2[1].NAME == 'C')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES2[1].NAME == 'D')
			{engEvalString(m_pEngine, "NAME2 = 'Wave Source D' ");}


			if(HoldMedium.WAVESOURCES2[2].NAME == 'A')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES2[2].NAME == 'B')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES2[2].NAME == 'C')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES2[2].NAME == 'D')
			{engEvalString(m_pEngine, "NAME3 = 'Wave Source D' ");}


			if(HoldMedium.WAVESOURCES2[3].NAME == 'A')
			{engEvalString(m_pEngine, "NAME4 = 'Wave Source A' ");}
			
			else if(HoldMedium.WAVESOURCES2[3].NAME == 'B')
			{engEvalString(m_pEngine, "NAME4 = 'Wave Source B' ");}
			
			else if(HoldMedium.WAVESOURCES2[3].NAME == 'C')
			{engEvalString(m_pEngine, "NAME4 = 'Wave Source C' ");}
			
			else if(HoldMedium.WAVESOURCES2[3].NAME == 'D')
			{engEvalString(m_pEngine, "NAME4 = 'Wave Source D' ");}




			

		

			
			



				engEvalString(m_pEngine,"  figure('units','normalized','outerposition',[0 0 1 1]);");
						engEvalString(m_pEngine," subplot('Position',[.9 .82 .04 .04]), p = -2:.1:2; q = sin(p); q1 = sin(p),q2 = sin(p),q3 = cos(p), plot(p,q,'k',p,q1,'c',p,q2,'r',p,q3,'m'),hleg = legend(NAME1,NAME2,NAME3,NAME4),set(hleg,'position',[.89 .8 .1 .1],'FontWeight','bold'),");//
			engEvalString(m_pEngine," AMP0 = Amplitude0;AMP1 = Amplitude1;AMP2 = Amplitude2;AMP3 = Amplitude3;     K0 = WaveNumber0;K1 = WaveNumber1;K2 = WaveNumber2;K3 = WaveNumber3;");
			engEvalString(m_pEngine," W0 = Omega0; W1 = Omega1;W2 = Omega2;W3 = Omega3;    PHI0 = Phase0; PHI1 = Phase1,PHI2 = Phase2;PHI3 = Phase3;  ");
			engEvalString(m_pEngine," LX = LowerXLim2;UX = UpperXLim2; LY = LowerYLim2; UY = UpperYLim2;UZ = UpperZLim2; LZ = LowerZLim2,");
			engEvalString(m_pEngine," RES = .8*(UX/80 - LX/80 + UY/80 - LY/80),x = LX:RES:UX, y = LY:RES:UY, [X,Y] = meshgrid(x,y), R0 = sqrt((X - STARTX0).^2 + (Y-STARTY0).^2),R1 = sqrt((X - STARTX1).^2 + (Y - STARTY1).^2),R2 = sqrt((X - STARTX2).^2 + (Y - STARTY2).^2),R3 = sqrt((X - STARTX3).^2 + (Y - STARTY3).^2),");
			engEvalString(m_pEngine," ARROWX0 = [STARTX0 STARTX0], ARROWY0 = [STARTY0 STARTY0],ARROWX1 = [STARTX1 STARTX1], ARROWY1 = [STARTY1 STARTY1],ARROWX2 = [STARTX2 STARTX2], ARROWY2 = [STARTY2 STARTY2],ARROWX3 = [STARTX3 STARTX3], ARROWY3 = [STARTY3 STARTY3], ARROWZ = [1.8*LCAX 1.8*UCAX];");
		
			

			


			//*(1./(1+RDAMP0.*R))*(1/(1+TDAMP0*t))*
			engEvalString(m_pEngine," Z =    (1./(1+RDAMP0*R0)).*(AMP0*(1/(1+TDAMP0*t))*sin(K0*R0 - W0*STime + PHI0))  +  (1./(1+RDAMP1*R1)).*(AMP1*(1/(1+TDAMP1*t))*sin(K1*R1 - W1*STime + PHI1))   +  (1./(1+RDAMP2*R2)).*(AMP2*(1/(1+TDAMP2*t))*sin(K2*R2 - W2*STime + PHI2))   +  (1./(1+RDAMP3*R3)).*(AMP3*(1/(1+TDAMP3*t))*sin(K3*R3 - W3*STime + PHI3))   ,subplot('Position',[.05 .11 .82 .8]),surf(X,Y,Z),grid minor,title(' 4 Wave Sources - 2D ','FontWeight','bold'),xlim([LX UX]),ylim([LY UY]),zlim([1.9*LCAX 1.9*UCAX]),caxis([LCAX UCAX]),hold on, plot3(ARROWX0,ARROWY0,ARROWZ,'b',ARROWX1,ARROWY1,ARROWZ,'c',ARROWX2,ARROWY2,ARROWZ,'r',ARROWX3,ARROWY3,ARROWZ,'m','LineWidth',6),hold off;");
			engEvalString(m_pEngine,"Interval = .04*SimSpeed/100; for t = STime:Interval:ETime Z =    (1./(1+(RDAMP0*R0))).*(AMP0*(1/(1+(.5*TDAMP0*t)))*sin(K0*R0 - W0*t + PHI0)) + (1./(1+RDAMP1*R1)).*(AMP1*(1/(1+TDAMP1*t))*sin(K1*R1 - W1*t + PHI1))  +  (1./(1+RDAMP2*R2)).*(AMP2*(1/(1+TDAMP2*t))*sin(K2*R2 - W2*t + PHI2))   +  (1./(1+RDAMP3*R3)).*(AMP3*(1/(1+TDAMP3*t))*sin(K3*R3 - W3*t + PHI3))  , surf(X,Y,Z),grid minor, xlim([LX UX]),ylim([LY UY]),zlim([1.9*LCAX 1.9*UCAX]),caxis([LCAX UCAX]),view([20-XVIEW*t 40-YVIEW*t 25-40*abs(sin(ZVIEW*3.14*t/ETime))]),title(' 4 Wave Sources - 2D ','FontWeight','bold'), hold on, plot3(ARROWX0,ARROWY0,ARROWZ,'k',ARROWX1,ARROWY1,ARROWZ,'c',ARROWX2,ARROWY2,ARROWZ,'r',ARROWX3,ARROWY3,ARROWZ,'m','LineWidth',7),hold off, drawnow, end;");


						
}break;// end case 4




		}// end switch on how many wave sources






}// end simulation function 2d















void Copy2DMedium( TwoDWaveMedium &CopyMedium,TwoDWaveMedium &UserMedium)
{

	CopyMedium.WaveVelocity = UserMedium.WaveVelocity;
	CopyMedium.LowerX = UserMedium.LowerX;
	CopyMedium.UpperX = UserMedium.UpperX;
	CopyMedium.LowerY = UserMedium.LowerY;
	CopyMedium.UpperY = UserMedium.UpperY;
	CopyMedium.LowerZ = UserMedium.LowerZ;
	CopyMedium.UpperZ = UserMedium.UpperZ;
	CopyMedium.STime = UserMedium.STime;
	CopyMedium.ETime = UserMedium.ETime;
	CopyMedium.SimSpeed = UserMedium.SimSpeed;
	CopyMedium.Resolution = UserMedium.Resolution;
	CopyMedium.MESH = UserMedium.MESH;
	CopyMedium.BCKGRND = UserMedium.BCKGRND;
	CopyMedium.COLORSTREAM = UserMedium.COLORSTREAM;
	CopyMedium.SetZAxis = UserMedium.SetZAxis;
	



	




}




void Copy2DSource(int iii,int Num, TwoDWaveMedium &CopyMedium, TwoDWaveMedium &UserMedium)
{


	//CopyMedium.WAVESOURCES2[Num]   = UserMedium.WAVESOURCES2[Num] 


	CopyMedium.WAVESOURCES2[iii].NAME   = UserMedium.WAVESOURCES2[Num].NAME;
	
	CopyMedium.WAVESOURCES2[iii].Amplitude   = UserMedium.WAVESOURCES2[Num].Amplitude; 

	CopyMedium.WAVESOURCES2[iii].Frequency   = UserMedium.WAVESOURCES2[Num].Frequency; 

	CopyMedium.WAVESOURCES2[iii].Wavelength   = UserMedium.WAVESOURCES2[Num].Wavelength; 

	CopyMedium.WAVESOURCES2[iii].WaveNumber   = UserMedium.WAVESOURCES2[Num].WaveNumber; 

	CopyMedium.WAVESOURCES2[iii].Omega   = UserMedium.WAVESOURCES2[Num].Omega; 

	CopyMedium.WAVESOURCES2[iii].PhaseConst   = UserMedium.WAVESOURCES2[Num].PhaseConst; 

	CopyMedium.WAVESOURCES2[iii].StartingX   = UserMedium.WAVESOURCES2[Num].StartingX; 

	CopyMedium.WAVESOURCES2[iii].StartingY   = UserMedium.WAVESOURCES2[Num].StartingY;
	
	CopyMedium.WAVESOURCES2[iii].WaveVelocity   = UserMedium.WAVESOURCES2[Num].WaveVelocity;

	CopyMedium.WAVESOURCES2[iii].RadialDamping   = UserMedium.WAVESOURCES2[Num].RadialDamping;


	CopyMedium.WAVESOURCES2[iii].TimeDamping   = UserMedium.WAVESOURCES2[Num].TimeDamping;



}






double IsDamped(int Num,TwoDWaveMedium &HoldMedium)
{

	int Return = 0;
	double TotalAmp = 0;


	for(int iii = 0; iii<Num; iii++)
	{
	
		if(HoldMedium.WAVESOURCES2[iii].RadialDamping == 0)
		{
		TotalAmp += HoldMedium.WAVESOURCES2[iii].Amplitude;
		Return = 1;
		}
		else{TotalAmp += .3*HoldMedium.WAVESOURCES2[iii].Amplitude;}

	
	}// end for loop on iii




	if(Return == 1)
	{return TotalAmp;}

	
	else if(Return == 0)
	{
	
	int MaxAmp = 0;

	for(int iii = 0; iii<Num; iii++)
	{
	if(HoldMedium.WAVESOURCES2[iii].Amplitude > MaxAmp)
	MaxAmp = HoldMedium.WAVESOURCES2[iii].Amplitude;
	}
	
	return MaxAmp;


	}
	else{return -1;}




}





#endif