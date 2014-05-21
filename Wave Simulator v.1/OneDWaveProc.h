#ifndef	   ONEDWAVEPROC_H
#define    ONEDWAVEPROC_H

#include "WaveSimHeader.h"
#include "WaveDefines.h"
#include "OneDWaveClass.h"
#include "OneDSimulation.h"
#include <string>
#include <sstream>
#include <stdio.h>
#include <commctrl.h>

static HWND CHECKBOX;


HBRUSH BackGround1 = CreateSolidBrush(RGB(0,0,0));//(RGB(400, 400, 400));
HBRUSH BGND1 = CreateSolidBrush(RGB(0,0,0));

void UpdateSimSpeedLabel();			// updates the simulation speed trackbar label
void UpdateStartTimeLabel(void);	// updates the start time of the simulation
void UpdateEndTimeLabel(void);		// updates the end time of the simualtion

 void UpdatePhaseLabel(int Num);	// updates the phase label for the dialog window

 void UpdateWaveSourceList(int);		// updates the wave source list on the main page


static OneDWaveMedium MasterMedium1D;

  HWND STIMESTATIC,ETIMESTATIC;		// start and end time static text that will change
  HWND SIMSPEEDSTATIC;					// will hold the simulation speed 
  HWND STIMETRACK;
  HWND ETIMETRACK;
  HWND SIMSPEEDTRACK; // the hwnd for all of the tracker bars




  HWND PHASECONSTSTATIC; // for the static text that corresponds to the track bar
  HWND PHASECONSTTRACK;  // for the phase constant trackbar in the dialog


  HWND AMPEDIT;			// edit box in the dialog to store the amplitude
  HWND FREQEDIT;		// edit box for the dialog to store the frequency
  HWND POSEDIT;			// edit box for the dialog to store the position

  int WaveSourceNum = 0;		// the number of the current new wave source to be added
  int WaveEditNumber = 5;		// the number of the current wave source to be edit
  bool VelocityChange1 = 0;		// lets us know if the user is only changing velocity

  LRESULT CALLBACK OneDWaveSourceProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam); // dialog call back to enter wave source specs
  LRESULT CALLBACK OneDWaveSourceEditProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam); // for when they want to edit the wave sources


  HINSTANCE hInstance;

LRESULT CALLBACK OneDWaveProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

	// these values are for organizing the list of wave source 
	//values that appear on the left of the menu box
		int DLG1FIRSTROW =  80;
		int DLG1SECONDROW = 165;
		int DLG1THIRDROW =  250;
		int DLG1FOURTHROW = 335;
		int DIF = 20; // the difference between the titles and the values 

	


	// Image Handle and window defines below

	HWND MainTitle; // hnwn for the title for this window

	HANDLE MainTitleImage; // handle for the main title image


	static HWND WaveSpeedEditBox;   // box where user enters the wave speed

	static HWND XLOWBOX,XHIGHBOX,YLOWBOX,YHIGHBOX; // edit boxes for the x and y limits

	

	switch (msg)
	{


	






	case WM_CREATE:
		{


			//SendMessageW(hwnd,WM_SETFONT,(long)hfont,0);


						//------------ IMAGES BELOW -----------------


			MainTitle = CreateWindowEx (NULL, L"STATIC", NULL,
WS_CHILD | WS_VISIBLE | SS_BITMAP, 180 , 0, 0, 0, hwnd, 0, NULL, NULL);

MainTitleImage = LoadImage(NULL, L"C:\\Users\\John\\Pictures\\WaveSimPics\\1dWaveTitle.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
SendMessage(MainTitle, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) MainTitleImage);





			// ----------************ BUTTONS BELOW ***************---------


			// CREATE 1D WAVE SOURCE BUTTON
	CreateWindow(TEXT("button"), TEXT(" Create New Wave Source"),    
	      WS_VISIBLE | WS_CHILD ,
	      115, 420, 200, 30,        
	      hwnd, (HMENU) IDB_CREATE1DSOURCE, NULL, NULL);			




			// SAVE WAVE SPEED BUTTON
		CreateWindow(TEXT("button"), TEXT(" Set"),    
	      WS_VISIBLE | WS_CHILD ,
	      660, 77, 60, 25,        
	      hwnd, (HMENU) IDB_SAVEWAVESPEED, NULL, NULL);	


		// ANIMATE SYSTEM BUTTON
		CreateWindow(TEXT("button"), TEXT(" Animate System"),    
	      WS_VISIBLE | WS_CHILD ,
	      480, 390, 180, 50,        
	      hwnd, (HMENU) IDB_CREATEPLOT, NULL, NULL);		

		// HELP/OPEN TUTORIAL
		CreateWindow(TEXT("button"), TEXT(" Help "),    
	      WS_VISIBLE | WS_CHILD ,
	      660, 390, 100, 25,        
	      hwnd, (HMENU) IDB_OPENTUTORIAL1D, NULL, NULL);	


		// HELP/OPEN TUTORIAL
		CreateWindow(TEXT("button"), TEXT(" Advanced "),    
	      WS_VISIBLE | WS_CHILD ,
	      660, 415, 100, 25,        
	      hwnd, (HMENU) IDB_1DADVANCEDOPTIONS, NULL, NULL);








			//----- TEXT BOXES AND EDIT BOXES BELOW -----




	// These two are to get the wave speed of the medium from the user
		// takes in the objects mass
	
		int WAVESPEEDROW = 80;

	       CreateWindowW(L"STATIC", L"Wave Speed [m/s] :",
          WS_VISIBLE | WS_CHILD ,
          450, WAVESPEEDROW, 210, 30,
          hwnd, (HMENU) IDS_WAVESPEEDTEXT  , NULL, NULL);	  
	
	WaveSpeedEditBox = CreateWindowW(L"Edit", L"10", 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        590, WAVESPEEDROW-3, 60, 25, hwnd, (HMENU) IDE_WAVESPEEDEDIT ,
        NULL, NULL);


	// these next three are to get the x axis limits from the user

	int XAXISLIMITSROW = 135;
	CreateWindowW(L"STATIC", L"X Axis Limits [m] :",
          WS_VISIBLE | WS_CHILD ,
          450, XAXISLIMITSROW, 150, 30,
          hwnd, (HMENU) IDS_XAXISTEXT1D  , NULL, NULL);	 

	CreateWindowW(L"STATIC", L" to ",
          WS_VISIBLE | WS_CHILD ,
          660, XAXISLIMITSROW-15, 15, 30,
          hwnd, (HMENU) 9000  , NULL, NULL);
	
	XLOWBOX = CreateWindowW(L"Edit", L"-10",			// lower x limit edit box
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        590, XAXISLIMITSROW-3, 60, 25, hwnd, (HMENU) IDE_LXAXISLIMITS1D ,
        NULL, NULL);
		
	XHIGHBOX = CreateWindowW(L"Edit", L"10",			// upper x limit edit box
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        690, XAXISLIMITSROW-3, 60, 25, hwnd, (HMENU) IDE_HXAXISLIMITS1D ,
        NULL, NULL);



	









	//  ---================ TRACKBARS AND THEIR TITLES ===========---------

	//					START TIME TRACK BAR

	 // the left side label of 10, means the lowest they can go is 10%
   HWND hLeftLabel = CreateWindowW(L"STATIC", L"0", 
    WS_CHILD | WS_VISIBLE, 0, 0, 7, 20, hwnd, (HMENU)1, NULL, NULL);

// the right side label of 500, means they highest they can go is 500% simspeed
  HWND hRightLabel = CreateWindowW(L"STATIC", L"60", 
    WS_CHILD | WS_VISIBLE, 0, 0, 30, 20, hwnd, (HMENU)2, NULL, NULL);

   CreateWindowW(L"STATIC", L"Start Time [s] :", WS_CHILD | WS_VISIBLE, 
    470, 200, 100, 20, hwnd, (HMENU)3, NULL, NULL);

// this text changes as they change their selection to show them the speed
	STIMESTATIC = CreateWindowW(L"STATIC", L"0", WS_CHILD | WS_VISIBLE, 
    570, 200, 30, 20, hwnd, (HMENU) IDS_STIMETEXT, NULL, NULL);

   INITCOMMONCONTROLSEX icex;

  icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
  icex.dwICC  = ICC_LISTVIEW_CLASSES;
  InitCommonControlsEx(&icex); 

  STIMETRACK = CreateWindowW(L"msctls_trackbar32", L"Starting Time",
      WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
      450, 230, 130, 30, hwnd, (HMENU) IDS_STIMETRACKBAR, NULL, NULL);

  SendMessageW(STIMETRACK, TBM_SETRANGE,  TRUE, MAKELONG(0, 60)); 
  SendMessageW(STIMETRACK, TBM_SETPAGESIZE, 0,  10); 
  SendMessageW(STIMETRACK, TBM_SETTICFREQ, 20, 0); 
  SendMessageW(STIMETRACK, TBM_SETPOS, TRUE, 0); 
  SendMessageW(STIMETRACK, TBM_SETBUDDY, TRUE, (LPARAM) hLeftLabel); 
  SendMessageW(STIMETRACK, TBM_SETBUDDY, FALSE, (LPARAM) hRightLabel); 




  //					END TIME TRACK BAR

	 // the left side label of 0, meaning the lowest they can go is zero
   HWND hLeftLabel1 = CreateWindowW(L"STATIC", L"0", 
    WS_CHILD | WS_VISIBLE, 0, 0, 7, 20, hwnd, (HMENU)5, NULL, NULL);

// the right side label of 500, means they highest they can go is 500% simspeed
  HWND hRightLabel1 = CreateWindowW(L"STATIC", L"60", 
    WS_CHILD | WS_VISIBLE, 0, 0, 30, 20, hwnd, (HMENU)6, NULL, NULL);

   CreateWindowW(L"STATIC", L"End Time [s] :", WS_CHILD | WS_VISIBLE, 
    650, 200, 100, 20, hwnd, (HMENU)22, NULL, NULL);

// this text changes as they change their selection to show them the speed
	ETIMESTATIC = CreateWindowW(L"STATIC", L"15", WS_CHILD | WS_VISIBLE, 
    755, 200, 30, 20, hwnd, (HMENU) IDS_ETIMETEXT, NULL, NULL);

 

  ETIMETRACK = CreateWindowW(L"msctls_trackbar32", L"Ending Time",
      WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
      640, 230, 130, 30, hwnd, (HMENU) IDS_ETIMETRACKBAR, NULL, NULL);

  SendMessageW(ETIMETRACK, TBM_SETRANGE,  TRUE, MAKELONG(0, 60)); 
  SendMessageW(ETIMETRACK, TBM_SETPAGESIZE, 0,  10); 
  SendMessageW(ETIMETRACK, TBM_SETTICFREQ, 20, 0); 
  SendMessageW(ETIMETRACK, TBM_SETPOS, TRUE, 15); 
  SendMessageW(ETIMETRACK, TBM_SETBUDDY, TRUE, (LPARAM) hLeftLabel1); 
  SendMessageW(ETIMETRACK, TBM_SETBUDDY, FALSE, (LPARAM) hRightLabel1); 



  //					SIMS SPEED TRACK BAR

	 // the left side label of 0, meaning the lowest they can go is zero
   HWND hLeftLabel2 = CreateWindowW(L"STATIC", L"10", 
    WS_CHILD | WS_VISIBLE, 0, 0, 15, 20, hwnd, (HMENU)10, NULL, NULL);

// the right side label of 500, means they highest they can go is 500% simspeed
  HWND hRightLabel2 = CreateWindowW(L"STATIC", L"300", 
    WS_CHILD | WS_VISIBLE, 0, 0, 30, 20, hwnd, (HMENU)11, NULL, NULL);

   CreateWindowW(L"STATIC", L" Simulation Speed [%] :", WS_CHILD | WS_VISIBLE, 
    520, 290, 150, 20, hwnd, (HMENU)4, NULL, NULL);

// this text changes as they change their selection to show them the speed
	SIMSPEEDSTATIC = CreateWindowW(L"STATIC", L"100", WS_CHILD | WS_VISIBLE, 
    680, 290, 30, 20, hwnd, (HMENU) IDS_SIMSPEEDTEXT, NULL, NULL);

 

    SIMSPEEDTRACK = CreateWindowW(L"msctls_trackbar32", L"Sim Speed",
      WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
      500, 320, 200, 30, hwnd, (HMENU)IDS_SIMSPEEDTRACKBAR, NULL, NULL);//IDS_SIMSPEEDTRACKBAR

  SendMessageW(SIMSPEEDTRACK, TBM_SETRANGE,  TRUE, MAKELONG(0, 300)); 
  SendMessageW(SIMSPEEDTRACK, TBM_SETPAGESIZE, 0,  10); 
  SendMessageW(SIMSPEEDTRACK, TBM_SETTICFREQ, 20, 0); 
  SendMessageW(SIMSPEEDTRACK, TBM_SETPOS, TRUE, 100); 
  SendMessageW(SIMSPEEDTRACK, TBM_SETBUDDY, TRUE, (LPARAM) hLeftLabel2); 
  SendMessageW(SIMSPEEDTRACK, TBM_SETBUDDY, FALSE, (LPARAM) hRightLabel2); 








			// --- GROUP BOXES BELOW --

CreateWindow(TEXT("BUTTON"), TEXT("Create/Edit Wave Sources"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
             10,            /* X Position */
             50,            /* Y Position */
             420,           /* X Width */
             410,           /* Y Height */
             hwnd, (HMENU) -1, NULL, NULL);











		}break;// end case WM_CREATE





		





		// for the trackbar callbacks
		case WM_HSCROLL:
			{
			
			if((HWND)(lParam) == STIMETRACK)
				 UpdateStartTimeLabel();

			if((HWND)(lParam) == ETIMETRACK)
				 UpdateEndTimeLabel();

			if((HWND)(lParam) == SIMSPEEDTRACK)
				 UpdateSimSpeedLabel();

				 // if the scroll is coming from the simspeed box
			

			
			}
			 break; // end case WM_HSCROLL












		case WM_COMMAND:
			{


				switch(LOWORD(wParam))
				{



					// when the user wants to set or change the speed of waves in the medium
				case IDB_SAVEWAVESPEED: {


        int length = GetWindowTextLengthW(WaveSpeedEditBox) + 1;
         wchar_t* text =  new wchar_t[length+1];

         GetWindowTextW(WaveSpeedEditBox, text, length);
        
		 char holdvalue[100];
		 double VELOCITY = 1;

		 for(int iii = 0;iii<length;iii++)
		holdvalue[iii] = *(text+iii);		  
		
		 VELOCITY = atof(holdvalue); // converts c string to doubles

		

		 int TESTINSERT = MasterMedium1D.SetWaveVelocity(VELOCITY);

		 if(TESTINSERT == -1)
		 { MessageBox(hwnd,L"Velocity Must Be Greater Than 0 and Less Than 1000 ",L"Invalid Entry",MB_OK | MB_ICONWARNING);
		   wchar_t buf[250];
			swprintf(buf, L"%.2f", MasterMedium1D.WaveVelocity);
		 SetWindowTextW(WaveSpeedEditBox,  buf);}
		 
		 VelocityChange1 = TRUE;
		 if(WaveSourceNum != 0){
			 for(int iii = 0; iii < WaveSourceNum;iii++)
				{ UpdateWaveSourceList( iii);}
			 
		 }
		VelocityChange1 = 0;

		delete [] text;
		
		
			}// end case user wants to set wave speed
break;



			






			// THIS IS THE BUTTON THEY PRESS WHEN THEY WANT TO ADD A NEW WAVE SOURCE
		
				case IDB_CREATE1DSOURCE:
					{

						//PostQuitMessage(0);

						// we don't allow the user to make another dialog box if they already have 4 wave sources
						if(WaveSourceNum <  4){
						DialogBoxW(hInstance, MAKEINTRESOURCE(IDD_1DWAVEDIALOG),
							hwnd, reinterpret_cast<DLGPROC>(OneDWaveSourceProc));}
						else{MessageBoxW(hwnd,L"This program can only handle 4 different wave sources at one time",L" Maximum Wave Sources Reached!",MB_OK | MB_ICONWARNING);}


					}
					break; // END CASE IDB_CREATE1DWAVESOURCE



						//  BELOW ARE THE CALLBACKS FOR THE CHECK BUTTONS
						// THAT ALLOW THE USER TO DECIDE WHICH WAVE SOURCES HE WANTS TO INCLUDE


					// if the user hits the checkbox for wave A
				case IDC_INCLUDEA1D:
					{

						 BOOL checked = IsDlgButtonChecked(hwnd, IDC_INCLUDEA1D);

					 if(checked)
						 {
				CheckDlgButton(hwnd, IDC_INCLUDEA1D, BST_UNCHECKED);
				MasterMedium1D.WAVESOURCES[0].IncludeInPlot = 0;
						 }
					else{CheckDlgButton(hwnd, IDC_INCLUDEA1D, BST_CHECKED);
					MasterMedium1D.WAVESOURCES[0].IncludeInPlot = 1;}


					}break; 


						// if the user hits the checkbox for wave B
				case IDC_INCLUDEB1D:
					{

						 BOOL checked = IsDlgButtonChecked(hwnd, IDC_INCLUDEB1D);

					 if(checked)
						 {
				CheckDlgButton(hwnd, IDC_INCLUDEB1D, BST_UNCHECKED);
				MasterMedium1D.WAVESOURCES[1].IncludeInPlot = 0;
						 }
					else{CheckDlgButton(hwnd, IDC_INCLUDEB1D, BST_CHECKED);MasterMedium1D.WAVESOURCES[1].IncludeInPlot = 1;}



					}break; 



						// if the user hits the checkbox for wave B
				case IDC_INCLUDEC1D:
					{

						 BOOL checked = IsDlgButtonChecked(hwnd, IDC_INCLUDEC1D);

					 if(checked)
						 {
				CheckDlgButton(hwnd, IDC_INCLUDEC1D, BST_UNCHECKED);
				MasterMedium1D.WAVESOURCES[2].IncludeInPlot = 0;
						 }
					else{CheckDlgButton(hwnd, IDC_INCLUDEC1D, BST_CHECKED);MasterMedium1D.WAVESOURCES[2].IncludeInPlot = 1;}



					}break; 





							// if the user hits the checkbox for wave B
				case IDC_INCLUDED1D:
					{

						 BOOL checked = IsDlgButtonChecked(hwnd, IDC_INCLUDED1D);

					 if(checked)
						 {
				CheckDlgButton(hwnd, IDC_INCLUDED1D, BST_UNCHECKED);
				MasterMedium1D.WAVESOURCES[3].IncludeInPlot = 0;
						 }
					else{CheckDlgButton(hwnd, IDC_INCLUDED1D, BST_CHECKED);MasterMedium1D.WAVESOURCES[3].IncludeInPlot = 1;}



					}break; 



					// END CASES FOR THE CHECKBOXES TO INCLUDE THE DIFFERENT WAVE SOURCES






					


						

					// this message is recieved only if the user has successfully created a new wave source!
					// so we will update the "wall" with the wave source details
				case ID_MESSAGE_UPDATEONED:
					{

						switch((lParam))		// the LPARAM IS THE WAVESOURCE NUMBER, 0 = A, 1 = B, ETC;
						{
						

						case(0): // CASE: the user just created/edited wave source A
							{



								

									// this if makes it so that we don't make all the buttons and titles reappear
								// if they only changed the velocity or edited a value
									if(WaveEditNumber != lParam && VelocityChange1 != TRUE)
									{

										// button to edit wave source A
									CreateWindow(TEXT("button"), TEXT(" Edit A "),    
								 WS_VISIBLE | WS_CHILD ,
								 285, DLG1FIRSTROW+20, 60, 30,        
								hwnd, (HMENU) IDB_EDITWAVESOURCEA, NULL, NULL);	


								// this creates the checkbox button to include
										// Wave Source Letter Name


					CreateWindowW(L"STATIC", L"Include A?", 
					 WS_CHILD | WS_VISIBLE, 350, DLG1FIRSTROW, 70, 20, hwnd, (HMENU) -111, NULL, NULL);

					 CreateWindowW(L"button", L"",
						WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
						370, DLG1FIRSTROW+DIF, 30, 35,
						hwnd, (HMENU) IDC_INCLUDEA1D , NULL, NULL);
					 CheckDlgButton(hwnd, IDC_INCLUDEA1D , BST_CHECKED);
					 MasterMedium1D.WAVESOURCES[0].IncludeInPlot = 1;
									


					
					
								// Wave Source Letter Name
					CreateWindowW(L"STATIC", L"Name", 
					 WS_CHILD | WS_VISIBLE, 20, DLG1FIRSTROW, 40, 20, hwnd, (HMENU) -11, NULL, NULL);

					CreateWindowW(L"STATIC", L"A", 
					 WS_CHILD | WS_VISIBLE, 25, DLG1FIRSTROW+DIF, 10, 20, hwnd, (HMENU) -13, NULL, NULL);
					
					
					
					// THESE NEXT THREE SHOW THE AMPLITUDE OF THE WAVE SOURCE
					 CreateWindowW(L"STATIC", L"Amplitude [m]", 
					 WS_CHILD | WS_VISIBLE, 80, DLG1FIRSTROW, 120, 20, hwnd, (HMENU) -14, NULL, NULL);
					 
									}// end if

									if( VelocityChange1 != TRUE)
									{
					wchar_t CAmplitude[30];
					swprintf(CAmplitude, L"%.2f", MasterMedium1D.WAVESOURCES[lParam].Amplitude);
					
					 CreateWindowW(L"STATIC", CAmplitude, 
					 WS_CHILD | WS_VISIBLE, 100, DLG1FIRSTROW+DIF, 40, 20, hwnd, (HMENU) ASOURCEAMP, NULL, NULL);



					 // THESE NEXT THREE SHOW THE FREQUENCY OF THE WAVE SOURCE
					  CreateWindowW(L"STATIC", L"Frequency [1/s]", 
					 WS_CHILD | WS_VISIBLE, 180, DLG1FIRSTROW, 110, 20, hwnd, (HMENU) -17, NULL, NULL);

					wchar_t CFrequency[30];
					swprintf(CFrequency, L"%.2f", MasterMedium1D.WAVESOURCES[lParam].Frequency);
					

					
					 CreateWindowW(L"STATIC", CFrequency, 
					 WS_CHILD | WS_VISIBLE, 190, DLG1FIRSTROW+DIF, 40, 20, hwnd, (HMENU) ASOURCEFREQ, NULL, NULL);
					 

									}//endif


					 
					 
					// THIS OUTPUTS THE WAVE EQUATION FOR THE SPECIFIC WAVE SOURCE
					 HWND EQUATION1 = CreateWindowW(L"STATIC", L"0", 
					 WS_CHILD | WS_VISIBLE, 30, DLG1FIRSTROW+2*DIF, 250, 20, hwnd, (HMENU) -20, NULL, NULL);
					 wchar_t buf20[70];
					
				// set the wave velocity to that of the medium
					 MasterMedium1D.WAVESOURCES[lParam].WaveVelocity = MasterMedium1D.WaveVelocity;	
					
					 // set the wavelength by dividing the velocity by the fequency
					  MasterMedium1D.WAVESOURCES[lParam].Wavelength =  MasterMedium1D.WAVESOURCES[lParam].WaveVelocity/ MasterMedium1D.WAVESOURCES[lParam].Frequency;
					
					  //find the phase constant by dividing the percentage of max amplitude by pi over 2
					  MasterMedium1D.WAVESOURCES[lParam].PhaseConst = asin(MasterMedium1D.WAVESOURCES[lParam].PhaseConstPerc/(100.0));

					// saves the wave number 2pi/wavelength to the wave specs
					  MasterMedium1D.WAVESOURCES[lParam].WaveNumber = (2*3.1415)/ MasterMedium1D.WAVESOURCES[lParam].Wavelength;
					
				  // saves the omega of each wave to the specific wave specs
					  if(MasterMedium1D.WAVESOURCES[lParam].Direction == 1)
					  MasterMedium1D.WAVESOURCES[lParam].Omega = (2*3.14159)*MasterMedium1D.WAVESOURCES[lParam].Frequency;
					  else{MasterMedium1D.WAVESOURCES[lParam].Omega = -1*(2*3.14159)*MasterMedium1D.WAVESOURCES[lParam].Frequency;}
					
					swprintf(buf20, L"%.2f*sin(%.2f*x - %.2f*t + %.2f)",
						 MasterMedium1D.WAVESOURCES[lParam].Amplitude, // insert amplitude
						 MasterMedium1D.WAVESOURCES[lParam].WaveNumber,	// insert k
						 MasterMedium1D.WAVESOURCES[lParam].Omega,      // insert omega
						 MasterMedium1D.WAVESOURCES[lParam].PhaseConst);// insert phase constant	


					 SetWindowTextW(EQUATION1, buf20);		




							}break; // end case A wave source creation









						case(1):// CASE: the user just created/edited wave source B
							{

									
									// this if makes it so that we don't make all the buttons and titles reappear
								// if they only changed the velocity or edited a value
									if(WaveEditNumber != lParam && VelocityChange1 != TRUE)
									{

										
								// button to edit wave source A
									CreateWindow(TEXT("button"), TEXT(" Edit B "),    
								 WS_VISIBLE | WS_CHILD ,
								 285, DLG1SECONDROW+20, 60, 30,        
								hwnd, (HMENU) IDB_EDITWAVESOURCEB, NULL, NULL);	

					

										// this creates the checkbox button to include
										// Wave Source Letter Name


					CreateWindowW(L"STATIC", L"Include B?", 
					 WS_CHILD | WS_VISIBLE, 350, DLG1SECONDROW, 70, 20, hwnd, (HMENU) -111, NULL, NULL);

					 CreateWindowW(L"button", L"",
						WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
						370, DLG1SECONDROW+DIF, 30, 35,
						hwnd, (HMENU) IDC_INCLUDEB1D , NULL, NULL);
					 CheckDlgButton(hwnd, IDC_INCLUDEB1D , BST_CHECKED);

					 MasterMedium1D.WAVESOURCES[1].IncludeInPlot = 1;
									



					
								// Wave Source Letter Name
					CreateWindowW(L"STATIC", L"Name", 
					 WS_CHILD | WS_VISIBLE, 20, DLG1SECONDROW, 40, 20, hwnd, (HMENU) -31, NULL, NULL);

					CreateWindowW(L"STATIC", L"B", 
					 WS_CHILD | WS_VISIBLE, 25, DLG1SECONDROW+DIF, 10, 20, hwnd, (HMENU) -33, NULL, NULL);
					
					
					
					// THESE NEXT THREE SHOW THE AMPLITUDE OF THE WAVE SOURCE
					 CreateWindowW(L"STATIC", L"Amplitude [m]", 
					 WS_CHILD | WS_VISIBLE, 80, DLG1SECONDROW, 120, 20, hwnd, (HMENU) -34, NULL, NULL);
					 

									} // endif

									
								if(VelocityChange1 != TRUE)
								{
					wchar_t CAmplitude[30];
					swprintf(CAmplitude, L"%.2f", MasterMedium1D.WAVESOURCES[lParam].Amplitude);
					
					 CreateWindowW(L"STATIC", CAmplitude, 
					 WS_CHILD | WS_VISIBLE, 100, DLG1SECONDROW+DIF, 40, 20, hwnd, (HMENU) BSOURCEAMP, NULL, NULL);



					 // THESE NEXT THREE SHOW THE FREQUENCY OF THE WAVE SOURCE
					  CreateWindowW(L"STATIC", L"Frequency [1/s]", 
					 WS_CHILD | WS_VISIBLE, 180, DLG1SECONDROW, 110, 20, hwnd, (HMENU) -37, NULL, NULL);

					wchar_t CFrequency[30];
					swprintf(CFrequency, L"%.2f", MasterMedium1D.WAVESOURCES[lParam].Frequency);
					

					// the right side label of 500, means they highest they can go is 500% simspeed
					 CreateWindowW(L"STATIC", CFrequency, 
					 WS_CHILD | WS_VISIBLE, 190, DLG1SECONDROW+DIF, 40, 20, hwnd, (HMENU) BSOURCEFREQ, NULL, NULL);


								}//endif


					 
					 
					// THIS OUTPUTS THE WAVE EQUATION FOR THE SPECIFIC WAVE SOURCE
					 HWND EQUATION2 = CreateWindowW(L"STATIC", L"0", 
					 WS_CHILD | WS_VISIBLE, 30, DLG1SECONDROW+2*DIF, 250, 20, hwnd, (HMENU) -40, NULL, NULL);
					 wchar_t buf20[70];
					
				// set the wave velocity to that of the medium
					 MasterMedium1D.WAVESOURCES[lParam].WaveVelocity = MasterMedium1D.WaveVelocity;	
					
					 // set the wavelength by dividing the velocity by the fequency
					  MasterMedium1D.WAVESOURCES[lParam].Wavelength =  MasterMedium1D.WAVESOURCES[lParam].WaveVelocity/ MasterMedium1D.WAVESOURCES[lParam].Frequency;
					
					  //find the phase constant by dividing the percentage of max amplitude by pi over 2
					  MasterMedium1D.WAVESOURCES[lParam].PhaseConst = asin(MasterMedium1D.WAVESOURCES[lParam].PhaseConstPerc/(100.0));

					// saves the wave number 2pi/wavelength to the wave specs
					  MasterMedium1D.WAVESOURCES[lParam].WaveNumber = (2*3.1415)/ MasterMedium1D.WAVESOURCES[lParam].Wavelength;
					
				  // saves the omega of each wave to the specific wave specs
					  if(MasterMedium1D.WAVESOURCES[lParam].Direction == 1)
					  MasterMedium1D.WAVESOURCES[lParam].Omega = (2*3.14159)*MasterMedium1D.WAVESOURCES[lParam].Frequency;
					  else{MasterMedium1D.WAVESOURCES[lParam].Omega = -1*(2*3.14159)*MasterMedium1D.WAVESOURCES[lParam].Frequency;}
					
					swprintf(buf20, L"%.2f*sin(%.2f*x - %.2f*t + %.2f)",
						 MasterMedium1D.WAVESOURCES[lParam].Amplitude, // insert amplitude
						 MasterMedium1D.WAVESOURCES[lParam].WaveNumber,	// insert k
						 MasterMedium1D.WAVESOURCES[lParam].Omega,      // insert omega
						 MasterMedium1D.WAVESOURCES[lParam].PhaseConst);// insert phase constant	


					 SetWindowTextW(EQUATION2, buf20);				// insert phase constant






							}break;// end case B wave source creation








						case(2):// CASE: the user just created/edited wave source A
							{


								
									// this if makes it so that we don't make all the buttons and titles reappear
								// if they only changed the velocity or edited a value
									if(WaveEditNumber != lParam && VelocityChange1 != TRUE)
									{

										// button to edit wave source A
									CreateWindow(TEXT("button"), TEXT(" Edit C "),    
								 WS_VISIBLE | WS_CHILD ,
								 285, DLG1THIRDROW+20, 60, 30,        
								hwnd, (HMENU) IDB_EDITWAVESOURCEC, NULL, NULL);	




									// this creates the checkbox button to include
										// Wave Source Letter Name
					CreateWindowW(L"STATIC", L"Include C?", 
					 WS_CHILD | WS_VISIBLE, 350, DLG1THIRDROW, 70, 20, hwnd, (HMENU) -131, NULL, NULL);

					 CreateWindowW(L"button", L"",
						WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
						370, DLG1THIRDROW+DIF, 30, 35,
						hwnd, (HMENU) IDC_INCLUDEC1D , NULL, NULL);
					 CheckDlgButton(hwnd, IDC_INCLUDEC1D , BST_CHECKED);

					 MasterMedium1D.WAVESOURCES[2].IncludeInPlot = 1;
									


					
					
								// Wave Source Letter Name
					CreateWindowW(L"STATIC", L"Name", 
					 WS_CHILD | WS_VISIBLE, 20, DLG1THIRDROW, 40, 20, hwnd, (HMENU) -51, NULL, NULL);

					CreateWindowW(L"STATIC", L"C", 
					 WS_CHILD | WS_VISIBLE, 25, DLG1THIRDROW+DIF, 10, 20, hwnd, (HMENU) -53, NULL, NULL);
					
					
					
					// THESE NEXT THREE SHOW THE AMPLITUDE OF THE WAVE SOURCE
					 CreateWindowW(L"STATIC", L"Amplitude [m]", 
					 WS_CHILD | WS_VISIBLE, 80, DLG1THIRDROW, 120, 20, hwnd, (HMENU) -54, NULL, NULL);
					 

									}//endif

										
									if( VelocityChange1 != TRUE)
									{
					wchar_t CAmplitude[30];
					swprintf(CAmplitude, L"%.2f", MasterMedium1D.WAVESOURCES[lParam].Amplitude);
					
					 CreateWindowW(L"STATIC", CAmplitude, 
					 WS_CHILD | WS_VISIBLE, 100, DLG1THIRDROW+DIF, 40, 20, hwnd, (HMENU) CSOURCEAMP, NULL, NULL);



					 // THESE NEXT THREE SHOW THE FREQUENCY OF THE WAVE SOURCE
					  CreateWindowW(L"STATIC", L"Frequency [1/s]", 
					 WS_CHILD | WS_VISIBLE, 180, DLG1THIRDROW, 110, 20, hwnd, (HMENU) -57, NULL, NULL);

					wchar_t CFrequency[30];
					swprintf(CFrequency, L"%.2f", MasterMedium1D.WAVESOURCES[lParam].Frequency);
					

					// the right side label of 500, means they highest they can go is 500% simspeed
					 CreateWindowW(L"STATIC", CFrequency, 
					 WS_CHILD | WS_VISIBLE, 190, DLG1THIRDROW+DIF, 30, 40, hwnd, (HMENU) CSOURCEFREQ, NULL, NULL);


									}//endif


					 
					 
					// THIS OUTPUTS THE WAVE EQUATION FOR THE SPECIFIC WAVE SOURCE
					 HWND EQUATION3 = CreateWindowW(L"STATIC", L"0", 
					 WS_CHILD | WS_VISIBLE, 30, DLG1THIRDROW+2*DIF, 250, 20, hwnd, (HMENU) -60, NULL, NULL);
					 wchar_t buf20[70];
					
				// set the wave velocity to that of the medium
					 MasterMedium1D.WAVESOURCES[lParam].WaveVelocity = MasterMedium1D.WaveVelocity;	
					
					 // set the wavelength by dividing the velocity by the fequency
					  MasterMedium1D.WAVESOURCES[lParam].Wavelength =  MasterMedium1D.WAVESOURCES[lParam].WaveVelocity/ MasterMedium1D.WAVESOURCES[lParam].Frequency;
					
					  //find the phase constant by dividing the percentage of max amplitude by pi over 2
					  MasterMedium1D.WAVESOURCES[lParam].PhaseConst = asin(MasterMedium1D.WAVESOURCES[lParam].PhaseConstPerc/(100.0));

					// saves the wave number 2pi/wavelength to the wave specs
					  MasterMedium1D.WAVESOURCES[lParam].WaveNumber = (2*3.1415)/ MasterMedium1D.WAVESOURCES[lParam].Wavelength;
					
					  // saves the omega of each wave to the specific wave specs
					  if(MasterMedium1D.WAVESOURCES[lParam].Direction == 1)
					  MasterMedium1D.WAVESOURCES[lParam].Omega = (2*3.14159)*MasterMedium1D.WAVESOURCES[lParam].Frequency;
					  else{MasterMedium1D.WAVESOURCES[lParam].Omega = -1*(2*3.14159)*MasterMedium1D.WAVESOURCES[lParam].Frequency;}
					
					swprintf(buf20, L"%.2f*sin(%.2f*x - %.2f*t + %.2f)",
						 MasterMedium1D.WAVESOURCES[lParam].Amplitude, // insert amplitude
						 MasterMedium1D.WAVESOURCES[lParam].WaveNumber,	// insert k
						 MasterMedium1D.WAVESOURCES[lParam].Omega,      // insert omega
						 MasterMedium1D.WAVESOURCES[lParam].PhaseConst);// insert phase constant


					 SetWindowTextW(EQUATION3, buf20);				



							}break; // end case C wave source creation









						case (3):// CASE: the user just created/edited wave source D
							{


							

										// this if makes it so that we don't make all the buttons and titles reappear
								// if they only changed the velocity or edited a value
									if(WaveEditNumber != lParam && VelocityChange1 != TRUE)
									{


											// button to edit wave source A
									CreateWindow(TEXT("button"), TEXT(" Edit D "),    
								 WS_VISIBLE | WS_CHILD ,
								 285, DLG1FOURTHROW+20, 60, 30,        
								hwnd, (HMENU) IDB_EDITWAVESOURCED, NULL, NULL);	


								// this creates the checkbox button to include
								// Wave Source Letter Name


					CreateWindowW(L"STATIC", L"Include D?", 
					 WS_CHILD | WS_VISIBLE, 350, DLG1FOURTHROW, 70, 20, hwnd, (HMENU) -131, NULL, NULL);

					 CreateWindowW(L"button", L"",
						WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
						370, DLG1FOURTHROW+DIF, 30, 35,
						hwnd, (HMENU) IDC_INCLUDED1D , NULL, NULL);
					 CheckDlgButton(hwnd, IDC_INCLUDED1D , BST_CHECKED);

					 MasterMedium1D.WAVESOURCES[3].IncludeInPlot = 1;
									




					
					
								// Wave Source Letter Name
					CreateWindowW(L"STATIC", L"Name", 
					 WS_CHILD | WS_VISIBLE, 20, DLG1FOURTHROW, 40, 20, hwnd, (HMENU) -71, NULL, NULL);

					CreateWindowW(L"STATIC", L"C", 
					 WS_CHILD | WS_VISIBLE, 25, DLG1FOURTHROW+DIF, 10, 20, hwnd, (HMENU) -73, NULL, NULL);
					
					
					
					// THESE NEXT THREE SHOW THE AMPLITUDE OF THE WAVE SOURCE
					 CreateWindowW(L"STATIC", L"Amplitude [m]", 
					 WS_CHILD | WS_VISIBLE, 80, DLG1FOURTHROW, 120, 20, hwnd, (HMENU) -74, NULL, NULL);
					 

									}//endif

									if(VelocityChange1 != TRUE)
									{
					wchar_t CAmplitude[30];
					swprintf(CAmplitude, L"%.2f", MasterMedium1D.WAVESOURCES[lParam].Amplitude);
					
					 CreateWindowW(L"STATIC", CAmplitude, 
					 WS_CHILD | WS_VISIBLE, 100, DLG1FOURTHROW+DIF, 30, 40, hwnd, (HMENU) DSOURCEAMP, NULL, NULL);



					 // THESE NEXT THREE SHOW THE FREQUENCY OF THE WAVE SOURCE
					  CreateWindowW(L"STATIC", L"Frequency [1/s]", 
					 WS_CHILD | WS_VISIBLE, 180, DLG1FOURTHROW, 110, 20, hwnd, (HMENU) -77, NULL, NULL);

					wchar_t CFrequency[30];
					swprintf(CFrequency, L"%.2f", MasterMedium1D.WAVESOURCES[lParam].Frequency);
					

					// the right side label of 500, means they highest they can go is 500% simspeed
					 CreateWindowW(L"STATIC", CFrequency, 
					 WS_CHILD | WS_VISIBLE, 190, DLG1FOURTHROW+DIF, 40, 20, hwnd, (HMENU) DSOURCEFREQ, NULL, NULL);


									}// endif


					 
					 
					// THIS OUTPUTS THE WAVE EQUATION FOR THE SPECIFIC WAVE SOURCE
					 HWND EQUATION4 = CreateWindowW(L"STATIC", L"0", 
					 WS_CHILD | WS_VISIBLE, 30, DLG1FOURTHROW+2*DIF, 250, 20, hwnd, (HMENU) -80, NULL, NULL);
					 wchar_t buf20[70];
					
					 // set the wave velocity to that of the medium
					 MasterMedium1D.WAVESOURCES[lParam].WaveVelocity = MasterMedium1D.WaveVelocity;	
					
					 // set the wavelength by dividing the velocity by the fequency
					  MasterMedium1D.WAVESOURCES[lParam].Wavelength =  MasterMedium1D.WAVESOURCES[lParam].WaveVelocity/ MasterMedium1D.WAVESOURCES[lParam].Frequency;
					
					  //find the phase constant by dividing the percentage of max amplitude by pi over 2
					  MasterMedium1D.WAVESOURCES[lParam].PhaseConst = asin(MasterMedium1D.WAVESOURCES[lParam].PhaseConstPerc/(100.0));

					// saves the wave number 2pi/wavelength to the wave specs
					  MasterMedium1D.WAVESOURCES[lParam].WaveNumber = (2*3.1415)/ MasterMedium1D.WAVESOURCES[lParam].Wavelength;
					
					    // saves the omega of each wave to the specific wave specs
					  if(MasterMedium1D.WAVESOURCES[lParam].Direction == 1)
					  MasterMedium1D.WAVESOURCES[lParam].Omega = (2*3.14159)*MasterMedium1D.WAVESOURCES[lParam].Frequency;
					  else{MasterMedium1D.WAVESOURCES[lParam].Omega = -1*(2*3.14159)*MasterMedium1D.WAVESOURCES[lParam].Frequency;}
					
					swprintf(buf20, L"%.2f*sin(%.2f*x - %.2f*t + %.2f)",
						 MasterMedium1D.WAVESOURCES[lParam].Amplitude, // insert amplitude
						 MasterMedium1D.WAVESOURCES[lParam].WaveNumber,	// insert k
						 MasterMedium1D.WAVESOURCES[lParam].Omega,      // insert omega
						 MasterMedium1D.WAVESOURCES[lParam].PhaseConst);// insert phase constant	
					 SetWindowTextW(EQUATION4, buf20);				



							}break; // end case D wave source


						}// end switch on LOWORDparam of which wave to update


					}
					break; // END CASE UPDATE 1D WAVE SOURCE LABELS





					// yes, you are still inside case wm_command..


					// ATTENTION MOTHEER FUCKER
					// BELOW ARE THE CALLBACKS THAT CREATE THE DIALOG WINDOW TO EDIT
					// THE SPECIFIC WAVE SOURCES!!




					case IDB_EDITWAVESOURCEA:
						{

							WaveEditNumber = 0;
							DialogBoxW(hInstance, MAKEINTRESOURCE(IDD_1DWAVEDIALOG),
							hwnd, reinterpret_cast<DLGPROC>(OneDWaveSourceEditProc));


						}break; // END CASE EDIT WAVE SOURCE A


					
					case IDB_EDITWAVESOURCEB:
						{

							WaveEditNumber = 1;
							DialogBoxW(hInstance, MAKEINTRESOURCE(IDD_1DWAVEDIALOG),
							hwnd, reinterpret_cast<DLGPROC>(OneDWaveSourceEditProc));


						}break; // END CASE EDIT WAVE SOURCE B



						
					case IDB_EDITWAVESOURCEC:
						{

							WaveEditNumber = 2;
							DialogBoxW(hInstance, MAKEINTRESOURCE(IDD_1DWAVEDIALOG),
							hwnd, reinterpret_cast<DLGPROC>(OneDWaveSourceEditProc));


						}break; // END CASE EDIT WAVE SOURCE C



						
					case IDB_EDITWAVESOURCED:
						{

							WaveEditNumber = 3;
							DialogBoxW(hInstance, MAKEINTRESOURCE(IDD_1DWAVEDIALOG),
							hwnd, reinterpret_cast<DLGPROC>(OneDWaveSourceEditProc));


						}break; // END CASE EDIT WAVE SOURCE D
			




				//###############
				//#####################3
				//##########################

				// AFTEREVERYTHING IS ENETERED THIS IS WHERE WE BEGIN THE SIMULATION!!!!


				//###########################
				//#####################
				//################


				case IDB_CREATEPLOT:
					{

						// the only thing we need to read in are the x limits
		int length = GetWindowTextLengthW(XLOWBOX) + 1;
         wchar_t* text =  new wchar_t[length+1];


         GetWindowTextW(XLOWBOX, text, length);
        
		 char holdvalue[100];
		 double LOWX = 1;

		 for(int iii = 0;iii<length;iii++)
		holdvalue[iii] = *(text+iii);		  
		
		 LOWX = atof(holdvalue); // converts c string to doubles
		 MasterMedium1D.LowerX = LOWX;


		 int length1 = GetWindowTextLengthW(XHIGHBOX) + 1;
         wchar_t* text1 =  new wchar_t[length1+1];


         GetWindowTextW(XHIGHBOX, text1, length1);
        
		 char holdvalue1[100];
		 double HIGHX = 1;

		 for(int iii = 0;iii<length1;iii++)
		holdvalue1[iii] = *(text1+iii);		  
		
		 HIGHX = atof(holdvalue1); // converts c string to doubles

		 MasterMedium1D.UpperX = HIGHX;






		 OneDWaveSimulation(WaveSourceNum, MasterMedium1D);

		 
		 delete [] text;

		 delete [] text1;
						

				}break; // end case user wants to plot





			}// end switch on wParam inside WM_COMMAND case

			}// END CASE WM_COMMAND!!!
			break;
	









		case WM_DESTROY:
			WaveSourceNum = 0;
			WaveEditNumber = 5;
			MasterMedium1D.ZeroClass();
			for(int i = 0;i < 4;i++)
				MasterMedium1D.WAVESOURCES[i].ZeroClass();







			// creates the text color for the window
		case WM_CTLCOLORSTATIC:
	{
	HBRUSH BackGround = CreateSolidBrush(RGB(0,0,0));//(RGB(400, 400, 400));
    HDC hdc = (HDC)wParam;
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));
    return (LONG) BackGround;
	}




	}// end switch on MSG

	  return (DefWindowProc(hwnd, msg, wParam, lParam)); 

}









// end 1D menu callback, Dialog callback for create wave source next






























LRESULT CALLBACK OneDWaveSourceProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{


	  int ERRORVALUE = 0;


HDC hdc = GetDC(hWndDlg);

	HFONT hfont;
 
hfont = CreateFontW(20,
                   0,
                   0,
                   0,
                   FW_BOLD,
                   0,
                   0,
                   0,
                   ANSI_CHARSET,
                   OUT_DEFAULT_PRECIS,
                   CLIP_DEFAULT_PRECIS,
                   DEFAULT_QUALITY,
                   DEFAULT_PITCH,
                   L"Georgia");






 

	switch(Msg)
	{


	

	case WM_INITDIALOG:
		{

			SendMessageW(hWndDlg,WM_SETFONT,(UINT)hfont, NULL);
			
			// CREATE 1D WAVE SOURCE BUTTON
	CreateWindow(TEXT("button"), TEXT(" Save Wave Source"),    
	      WS_VISIBLE | WS_CHILD ,
	      20, 290, 140, 30,        
	      hWndDlg, (HMENU) IDB_SAVE1DWAVESOURCE, NULL, NULL);

			// cancle create 1d wave source
	CreateWindow(TEXT("button"), TEXT(" Cancel "),    
	      WS_VISIBLE | WS_CHILD ,
	      170, 290, 140, 30,        
	      hWndDlg, (HMENU) IDB_CANCLE1DWAVESOURCE, NULL, NULL);

			if(WaveSourceNum == 0)
			{
				CreateWindowW(L"STATIC", L"Wave Source - A",
          WS_VISIBLE | WS_CHILD ,
          100, 10, 210, 30,
          hWndDlg, (HMENU) IDS_WAVELETTERTEXT  , NULL, NULL);	

			}

			if(WaveSourceNum == 1)
			{
				CreateWindowW(L"STATIC", L"Wave Source - B",
          WS_VISIBLE | WS_CHILD ,
          100, 10, 210, 30,
          hWndDlg, (HMENU) IDS_WAVELETTERTEXT  , NULL, NULL);	

			}

			if(WaveSourceNum == 2)
			{
				CreateWindowW(L"STATIC", L"Wave Source - C",
          WS_VISIBLE | WS_CHILD ,
          100, 10, 210, 30,
          hWndDlg, (HMENU) IDS_WAVELETTERTEXT  , NULL, NULL);	

			}

		 
			if(WaveSourceNum == 3)
			{
				CreateWindowW(L"STATIC", L"Wave Source - D",
          WS_VISIBLE | WS_CHILD ,
          100, 10, 210, 30,
          hWndDlg, (HMENU) IDS_WAVELETTERTEXT  , NULL, NULL);	

			}

					// AMPLITUDE

			CreateWindowW(L"STATIC", L"Wave Source Amplitude [m] :",
          WS_VISIBLE | WS_CHILD ,
          30, 50, 190, 30,
          hWndDlg, (HMENU) IDS_ENTERAMP  , NULL, NULL);


			wchar_t TEMPAMP[20];
			swprintf(TEMPAMP, L"%.2f", MasterMedium1D.WAVESOURCES[WaveSourceNum].Amplitude);
			AMPEDIT = CreateWindowW(L"EDIT", TEMPAMP,
          WS_VISIBLE | WS_CHILD ,
          245, 50, 60, 20,
          hWndDlg, (HMENU) IDE_ENTERAMP  , NULL, NULL);

					// FREQUENCY
			CreateWindowW(L"STATIC", L"Wave Source Frequency [hz] :",
          WS_VISIBLE | WS_CHILD ,
          30, 90, 195, 30,
          hWndDlg, (HMENU) IDS_ENTERFREQ  , NULL, NULL);

			wchar_t TEMPFREQ[20];
			swprintf(TEMPFREQ, L"%.2f", MasterMedium1D.WAVESOURCES[WaveSourceNum].Frequency);
			FREQEDIT =  CreateWindowW(L"EDIT", TEMPFREQ,
          WS_VISIBLE | WS_CHILD ,
          245, 90, 60, 20,
          hWndDlg, (HMENU) IDE_ENTERFREQ  , NULL, NULL);


			// FREQUENCY
			 CreateWindowW(L"STATIC", L"Wave Source Position [m] :",
          WS_VISIBLE | WS_CHILD ,
          30, 130, 195, 30,
          hWndDlg, (HMENU) IDS_ENTERXSTART  , NULL, NULL);

			 wchar_t TEMPPOS[20];
			swprintf(TEMPPOS, L"%.2f", MasterMedium1D.WAVESOURCES[WaveSourceNum].StartingX);
		POSEDIT =	CreateWindowW(L"EDIT", TEMPPOS,
          WS_VISIBLE | WS_CHILD ,
          245, 130, 60, 20,
          hWndDlg, (HMENU) IDE_ENTERXSTART  , NULL, NULL);



						//PHASE CONSTANT TRACK BAR

	 // the left side label of 10, means the lowest they can go is 10%
   HWND hLeftLabel4 = CreateWindowW(L"STATIC", L"-100%", 
    WS_CHILD | WS_VISIBLE, 0, 0, 35, 20, hWndDlg, (HMENU)21, NULL, NULL);

// the right side label of 500, means they highest they can go is 500% simspeed
  HWND hRightLabel4 = CreateWindowW(L"STATIC", L"100%", 
    WS_CHILD | WS_VISIBLE, 0, 0, 35, 20, hWndDlg, (HMENU)22, NULL, NULL);

   CreateWindowW(L"STATIC", L"Starting Amplitude % :", WS_CHILD | WS_VISIBLE, 
    70, 170, 150, 20, hWndDlg, (HMENU)23, NULL, NULL);

// this text changes as they change their selection to show them the speed
	PHASECONSTSTATIC = CreateWindowW(L"STATIC", L"0", WS_CHILD | WS_VISIBLE, 
    230, 170, 30, 20, hWndDlg, (HMENU) IDS_PHASECONST, NULL, NULL);

   INITCOMMONCONTROLSEX icex;

  icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
  icex.dwICC  = ICC_LISTVIEW_CLASSES;
  InitCommonControlsEx(&icex); 

  PHASECONSTTRACK = CreateWindowW(L"msctls_trackbar32", L"Starting Amplitude %",
      WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
      60, 200, 200, 30, hWndDlg, (HMENU) IDT_PHASECONSTTRACK, NULL, NULL);

  SendMessageW(PHASECONSTTRACK, TBM_SETRANGE,  TRUE, MAKELONG(-100, 100)); 
  SendMessageW(PHASECONSTTRACK, TBM_SETPAGESIZE, 0,  10); 
  SendMessageW(PHASECONSTTRACK, TBM_SETTICFREQ, 20, 0); 
  SendMessageW(PHASECONSTTRACK, TBM_SETPOS, TRUE, 0); 
  SendMessageW(PHASECONSTTRACK, TBM_SETBUDDY, TRUE, (LPARAM) hLeftLabel4); 
  SendMessageW(PHASECONSTTRACK, TBM_SETBUDDY, FALSE, (LPARAM) hRightLabel4); 



  CHECKBOX = CreateWindowW(L"button", L"Has Negative Velocity",
WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
50, 230, 200, 35,
hWndDlg, (HMENU) IDC_NEGATIVECHECKBOX , NULL, NULL);

   if(MasterMedium1D.WAVESOURCES[WaveSourceNum].Direction == 1)
CheckDlgButton(hWndDlg, IDC_NEGATIVECHECKBOX , BST_UNCHECKED);
   else{
	   CheckDlgButton(hWndDlg, IDC_NEGATIVECHECKBOX , BST_CHECKED);}
			





		}
		break; // end case WM_INITIALDIALOG


		case WM_HSCROLL:
			{

				
			
				UpdatePhaseLabel(WaveSourceNum);

			}
			break;









	case WM_COMMAND:
		{


			if(lParam == (UINT)CHECKBOX)
			{
				
			
				

				BOOL checked = IsDlgButtonChecked(hWndDlg, IDC_NEGATIVECHECKBOX);

					 if(checked)
						 {
				CheckDlgButton(hWndDlg, IDC_NEGATIVECHECKBOX, BST_UNCHECKED);
				MasterMedium1D.WAVESOURCES[WaveSourceNum].Direction = 1;
						 }
					 else{CheckDlgButton(hWndDlg, IDC_NEGATIVECHECKBOX, BST_CHECKED);MasterMedium1D.WAVESOURCES[WaveSourceNum].Direction = 0;}


			}

		switch((wParam))
		{

			
		

		





		case IDB_SAVE1DWAVESOURCE:
			{
				// COLLECTS THE AMPLITUDE VALUE FROM THE EDIT BXO
				 int length = GetWindowTextLengthW(AMPEDIT) + 1;
         wchar_t* text =  new wchar_t[length+1];



         GetWindowTextW(AMPEDIT, text, length);
        
		 char holdvalue[100];
		 double AMP = 1;

		 for(int iii = 0;iii<length;iii++)
		holdvalue[iii] = *(text+iii);		  
		
		 AMP = atof(holdvalue); // converts c string to doubles
		 if(AMP == 0)
		 {MessageBox(hWndDlg,L"Amplitude Must Be Greater than Zero!",L"Invalid Entry",MB_OK | MB_ICONWARNING);ERRORVALUE = 2;}
		 else{ERRORVALUE = 0;}




		 
		 


		  // COLLECTS THE FSTARTING POSITION FROM THE EDIT BOX
		 				 length = GetWindowTextLengthW(POSEDIT) + 1;
         wchar_t* text2 =  new wchar_t[length+1];

         GetWindowTextW(POSEDIT, text2, length);
        
		 char holdvalue2[100];
		 double POS = 1;

		 for(int iii = 0;iii<length;iii++)
		holdvalue2[iii] = *(text2+iii);		  
		
		 POS = atof(holdvalue2); // converts c string to doubles

	








		 // COLLECTS THE FREQUENCY VALUE FROM THE EDIT BOX
		 				  length = GetWindowTextLengthW(FREQEDIT) + 1;
         wchar_t* text1 =  new wchar_t[length+1];

         GetWindowTextW(FREQEDIT, text1, length);
        
		 char holdvalue1[100];
		 double FREQ = 1;

		 for(int iii = 0;iii<length;iii++)
		holdvalue1[iii] = *(text1+iii);		  
		
		 FREQ = atof(holdvalue1); // converts c string to doubles

		 if(FREQ <= 0)
			 {MessageBox(hWndDlg,L"Frequency Must be Greater Than Zero!",L"Invalid Entry",MB_OK | MB_ICONWARNING);
		 ERRORVALUE = 1;}
		 
		 if(FREQ > 0 && AMP != 0)
			{ERRORVALUE = 0;}
		 
		
			
		 
		


		 if(ERRORVALUE != 1 && ERRORVALUE != 2)
		 {
			 // close the dialog
			 EndDialog(hWndDlg,0); 
				
			 // set the frequency of the wave source
		  MasterMedium1D.WAVESOURCES[WaveSourceNum].Frequency = FREQ;

			// set the position of the wave source
		  MasterMedium1D.WAVESOURCES[WaveSourceNum].StartingX = POS;

		  // set the amplitude of the wave source
		 MasterMedium1D.WAVESOURCES[WaveSourceNum].Amplitude = AMP;

		 // set the phase constant percentage
		 LRESULT pos = SendMessageW(PHASECONSTTRACK, TBM_GETPOS, 0, 0);
		MasterMedium1D.WAVESOURCES[WaveSourceNum].PhaseConstPerc = pos;

		//update the wave source list on the main 1d wave menu
		 UpdateWaveSourceList(WaveSourceNum);

		 // make it so the user enters the next wave wave
		 WaveSourceNum++;

		 delete [] text;

		 delete [] text1;

		 delete [] text2;
			}
		 


		 

		



			}
			break;// END CASE CREATE 1D SOURCE




		case IDB_CANCLE1DWAVESOURCE:
			EndDialog(hWndDlg, 0);

			break;



			

			

		}// end switch on message





		}
		break;// end case WMCOMMAND



	case WM_CTLCOLORDLG:
		{
		return (long)BGND1;//BackGround1;
		}
			break; // end case color background




			case WM_CTLCOLORSTATIC:
{
HDC hdcStatic = (HDC)wParam;
SetTextColor(hdcStatic, RGB(255, 255, 255));
SetBkMode(hdcStatic, TRANSPARENT);
return (long)BGND1;//CreateSolidBrush(RGB(0, 0, 0));
}

  

			


		case WM_PAINT:
			{
		
			}
			break;// end case WMPAINT


		case WM_CLOSE:
		
			EndDialog(hWndDlg,0);
			break;


		

	}

	return FALSE;
}

























// MAKE SURE YOU ARE WORKING IN THE RIGHT CALLBACK@@@@<_________________--------------














// this dialog proc is used to edit the wave sources
LRESULT CALLBACK OneDWaveSourceEditProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{


	  int ERRORVALUE = 0;


HDC hdc = GetDC(hWndDlg);

	HFONT hfont;
 
hfont = CreateFontW(20,
                   0,
                   0,
                   0,
                   FW_BOLD,
                   0,
                   0,
                   0,
                   ANSI_CHARSET,
                   OUT_DEFAULT_PRECIS,
                   CLIP_DEFAULT_PRECIS,
                   DEFAULT_QUALITY,
                   DEFAULT_PITCH,
                   L"Georgia");






 

	switch(Msg)
	{


	

	case WM_INITDIALOG:
		{

			SendMessageW(hWndDlg,WM_SETFONT,(UINT)hfont, NULL);
			
			// CREATE 1D WAVE SOURCE BUTTON
	CreateWindow(TEXT("button"), TEXT(" Save Wave Source"),    
	      WS_VISIBLE | WS_CHILD ,
	      20, 290, 140, 30,        
	      hWndDlg, (HMENU) IDB_SAVE1DWAVESOURCE, NULL, NULL);

			// cancle create 1d wave source
	CreateWindow(TEXT("button"), TEXT(" Cancel "),    
	      WS_VISIBLE | WS_CHILD ,
	      170, 290, 140, 30,        
	      hWndDlg, (HMENU) IDB_CANCLE1DWAVESOURCE, NULL, NULL);

			if(WaveEditNumber == 0)
			{
				CreateWindowW(L"STATIC", L"Wave Source - A",
          WS_VISIBLE | WS_CHILD ,
          100, 10, 210, 30,
          hWndDlg, (HMENU) IDS_WAVELETTERTEXT  , NULL, NULL);	

			}

			if(WaveEditNumber == 1)
			{
				CreateWindowW(L"STATIC", L"Wave Source - B",
          WS_VISIBLE | WS_CHILD ,
          100, 10, 210, 30,
          hWndDlg, (HMENU) IDS_WAVELETTERTEXT  , NULL, NULL);	

			}

			if(WaveEditNumber == 2)
			{
				CreateWindowW(L"STATIC", L"Wave Source - C",
          WS_VISIBLE | WS_CHILD ,
          100, 10, 210, 30,
          hWndDlg, (HMENU) IDS_WAVELETTERTEXT  , NULL, NULL);	

			}

		 
			if(WaveEditNumber == 3)
			{
				CreateWindowW(L"STATIC", L"Wave Source - D",
          WS_VISIBLE | WS_CHILD ,
          100, 10, 210, 30,
          hWndDlg, (HMENU) IDS_WAVELETTERTEXT  , NULL, NULL);	

			}

					// AMPLITUDE

			CreateWindowW(L"STATIC", L"Wave Source Amplitude [m] :",
          WS_VISIBLE | WS_CHILD ,
          30, 50, 190, 30,
          hWndDlg, (HMENU) IDS_ENTERAMP  , NULL, NULL);


			wchar_t TEMPAMP[20];
			swprintf(TEMPAMP, L"%.2f", MasterMedium1D.WAVESOURCES[WaveEditNumber].Amplitude);
			AMPEDIT = CreateWindowW(L"EDIT", TEMPAMP,
          WS_VISIBLE | WS_CHILD ,
          245, 50, 60, 20,
          hWndDlg, (HMENU) IDE_ENTERAMP  , NULL, NULL);

					// FREQUENCY
			CreateWindowW(L"STATIC", L"Wave Source Frequency [hz] :",
          WS_VISIBLE | WS_CHILD ,
          30, 90, 195, 30,
          hWndDlg, (HMENU) IDS_ENTERFREQ  , NULL, NULL);

			wchar_t TEMPFREQ[20];
			swprintf(TEMPFREQ, L"%.2f", MasterMedium1D.WAVESOURCES[WaveEditNumber].Frequency);
			FREQEDIT =  CreateWindowW(L"EDIT", TEMPFREQ,
          WS_VISIBLE | WS_CHILD ,
          245, 90, 60, 20,
          hWndDlg, (HMENU) IDE_ENTERFREQ  , NULL, NULL);


			// FREQUENCY
			 CreateWindowW(L"STATIC", L"Wave Source Position [m] :",
          WS_VISIBLE | WS_CHILD ,
          30, 130, 195, 30,
          hWndDlg, (HMENU) IDS_ENTERXSTART  , NULL, NULL);

			 wchar_t TEMPPOS[20];
			swprintf(TEMPPOS, L"%.2f", MasterMedium1D.WAVESOURCES[WaveEditNumber].StartingX);
		POSEDIT =	CreateWindowW(L"EDIT", TEMPPOS,
          WS_VISIBLE | WS_CHILD ,
          245, 130, 60, 20,
          hWndDlg, (HMENU) IDE_ENTERXSTART  , NULL, NULL);



						//PHASE CONSTANT TRACK BAR

	 // the left side label of 10, means the lowest they can go is 10%
   HWND hLeftLabel4 = CreateWindowW(L"STATIC", L"-100%", 
    WS_CHILD | WS_VISIBLE, 0, 0, 35, 20, hWndDlg, (HMENU)21, NULL, NULL);

// the right side label of 500, means they highest they can go is 500% simspeed
  HWND hRightLabel4 = CreateWindowW(L"STATIC", L"100%", 
    WS_CHILD | WS_VISIBLE, 0, 0, 35, 20, hWndDlg, (HMENU)22, NULL, NULL);

   CreateWindowW(L"STATIC", L"Starting Amplitude % :", WS_CHILD | WS_VISIBLE, 
    70, 170, 150, 20, hWndDlg, (HMENU)23, NULL, NULL);


   wchar_t PHASEBUF[20];
   swprintf(PHASEBUF,L"%.0f",MasterMedium1D.WAVESOURCES[WaveEditNumber].PhaseConstPerc);
// this text changes as they change their selection to show them the speed
	PHASECONSTSTATIC = CreateWindowW(L"STATIC", PHASEBUF, WS_CHILD | WS_VISIBLE, 
    230, 170, 30, 20, hWndDlg, (HMENU) IDS_PHASECONST, NULL, NULL);

   INITCOMMONCONTROLSEX icex;

  icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
  icex.dwICC  = ICC_LISTVIEW_CLASSES;
  InitCommonControlsEx(&icex); 

  PHASECONSTTRACK = CreateWindowW(L"msctls_trackbar32", L"Starting Amplitude %",
      WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
      60, 200, 200, 30, hWndDlg, (HMENU) IDT_PHASECONSTTRACK, NULL, NULL);

  SendMessageW(PHASECONSTTRACK, TBM_SETRANGE,  TRUE, MAKELONG(-100, 100)); 
  SendMessageW(PHASECONSTTRACK, TBM_SETPAGESIZE, 0,  10); 
  SendMessageW(PHASECONSTTRACK, TBM_SETTICFREQ, 20, 0); 
  SendMessageW(PHASECONSTTRACK, TBM_SETPOS, TRUE, MasterMedium1D.WAVESOURCES[WaveEditNumber].PhaseConstPerc); 
  SendMessageW(PHASECONSTTRACK, TBM_SETBUDDY, TRUE, (LPARAM) hLeftLabel4); 
  SendMessageW(PHASECONSTTRACK, TBM_SETBUDDY, FALSE, (LPARAM) hRightLabel4); 



  CHECKBOX  =  CreateWindowW(L"button", L"Has Negative Velocity",
WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,
50, 250, 200, 25,
hWndDlg, (HMENU) IDC_NEGATIVECHECKBOX , NULL, NULL);

   if(MasterMedium1D.WAVESOURCES[WaveEditNumber].Direction == 1)
	   CheckDlgButton(hWndDlg, IDC_NEGATIVECHECKBOX , BST_UNCHECKED);
   else{
	   CheckDlgButton(hWndDlg, IDC_NEGATIVECHECKBOX , BST_CHECKED);}
			





		}
		break; // end case WM_INITIALDIALOG


		case WM_HSCROLL:
			{

				
			
				UpdatePhaseLabel(WaveEditNumber);
				

			}
			break;









	case WM_COMMAND:
		{

		if(lParam == (UINT)CHECKBOX)
			{
				
			
				BOOL checked = IsDlgButtonChecked(hWndDlg, IDC_NEGATIVECHECKBOX);

					 if(checked)
						 {
				CheckDlgButton(hWndDlg, IDC_NEGATIVECHECKBOX, BST_UNCHECKED);
				MasterMedium1D.WAVESOURCES[WaveEditNumber].Direction = 1;
						 }
					 else{CheckDlgButton(hWndDlg, IDC_NEGATIVECHECKBOX, BST_CHECKED);MasterMedium1D.WAVESOURCES[WaveEditNumber].Direction = 0;}


			}

		switch(wParam)
		{





		case IDB_SAVE1DWAVESOURCE:
			{

				
			


				// COLLECTS THE AMPLITUDE VALUE FROM THE EDIT BXO
				 int length = GetWindowTextLengthW(AMPEDIT) + 1;
         wchar_t* text =  new wchar_t[length+1];


         GetWindowTextW(AMPEDIT, text, length);
        
		 char holdvalue[100];
		 double AMP = 1;

		 for(int iii = 0;iii<length;iii++)
		holdvalue[iii] = *(text+iii);		  
		
		 AMP = atof(holdvalue); // converts c string to doubles
		 if(AMP == 0)
		 {MessageBox(hWndDlg,L"Amplitude Must Be Greater than Zero!",L"Invalid Entry",MB_OK | MB_ICONWARNING);ERRORVALUE = 2;}
		 else{ERRORVALUE = 0;}




		 
		 


		  // COLLECTS THE FSTARTING POSITION FROM THE EDIT BOX
		 				 length = GetWindowTextLengthW(POSEDIT) + 1;
         wchar_t* text2 =  new wchar_t[length+1];

         GetWindowTextW(POSEDIT, text2, length);
        
		 char holdvalue2[100];
		 double POS = 1;

		 for(int iii = 0;iii<length;iii++)
		holdvalue2[iii] = *(text2+iii);		  
		
		 POS = atof(holdvalue2); // converts c string to doubles

	








		 // COLLECTS THE FREQUENCY VALUE FROM THE EDIT BOX
		 				  length = GetWindowTextLengthW(FREQEDIT) + 1;
         wchar_t* text1 =  new wchar_t[length+1];

         GetWindowTextW(FREQEDIT, text1, length);
        
		 char holdvalue1[100];
		 double FREQ = 1;

		 for(int iii = 0;iii<length;iii++)
		holdvalue1[iii] = *(text1+iii);		  
		
		 FREQ = atof(holdvalue1); // converts c string to doubles

		 if(FREQ <= 0)
			 {MessageBox(hWndDlg,L"Frequency Must be Greater Than Zero!",L"Invalid Entry",MB_OK | MB_ICONWARNING);
		 ERRORVALUE = 1;}
		 
		 if(FREQ > 0 && AMP != 0)
			{ERRORVALUE = 0;}
		 
		
			
		 
		
		 // IF ALL OF THE INPUTS PASS ERROR ANALYSIS ABOVE
		 // WE SAVE THEM TO THE CLASS 

		 if(ERRORVALUE != 1 && ERRORVALUE != 2)
		 {
			 // close dialog window
			 EndDialog(hWndDlg,0);

			 // set the frequency of the wave source
		  MasterMedium1D.WAVESOURCES[WaveEditNumber].Frequency = FREQ;

			// set the initial position of the wave source
		  MasterMedium1D.WAVESOURCES[WaveEditNumber].StartingX = POS;

			// set the initial amplitude of the wave source
		 MasterMedium1D.WAVESOURCES[WaveEditNumber].Amplitude = AMP;

			// This part saves the percentage of maximum amplitude (PhasePercentage) only when the user chooses to save the wave source
		  LRESULT pos = SendMessageW(PHASECONSTTRACK, TBM_GETPOS, 0, 0);
		MasterMedium1D.WAVESOURCES[WaveEditNumber].PhaseConstPerc = pos;

			// update the wavesourcelist that appears on the main 1d wave menu
		 UpdateWaveSourceList(WaveEditNumber);
		 WaveEditNumber = 5;

		 delete [] text;

		 delete [] text1;


		 delete [] text2;
			}
		 


		 

		



			}
			break;// END CASE CREATE 1D SOURCE




		case IDB_CANCLE1DWAVESOURCE:
			EndDialog(hWndDlg, 0);

			break;



			

		}// end switch on wparam

		}break;// end case WMCOMMAND



	case WM_CTLCOLORDLG:
		{
		return (long)BGND1;//BackGround1;
		}
			break; // end case color background




			case WM_CTLCOLORSTATIC:
{
HDC hdcStatic = (HDC)wParam;
SetTextColor(hdcStatic, RGB(255, 255, 255));
SetBkMode(hdcStatic, TRANSPARENT);
return (long)BGND1;//CreateSolidBrush(RGB(0, 0, 0));
}

  

			


		case WM_PAINT:
			{
		
			}
			break;// end case WMPAINT


		case WM_CLOSE:
			EndDialog(hWndDlg,0);

			break;


		

	}

	return FALSE;
}
















// these update the trackbar labels as the user changes them
void UpdateSimSpeedLabel()
{
  LRESULT speed = SendMessageW(SIMSPEEDTRACK, TBM_GETPOS, 0, 0);
  MasterMedium1D.SimSpeed = speed;
  wchar_t buf[4];
  wsprintfW(buf, L"%ld", speed);

  SetWindowText(SIMSPEEDSTATIC, buf);
}

 void UpdateStartTimeLabel(void)
 {
  LRESULT pos = SendMessageW(STIMETRACK, TBM_GETPOS, 0, 0);
  MasterMedium1D.STime = pos;
  wchar_t buf[4];
  wsprintfW(buf, L"%ld", pos);

  SetWindowTextW(STIMESTATIC, buf);
}

 void UpdateEndTimeLabel(void)
 {
  LRESULT pos = SendMessageW(ETIMETRACK, TBM_GETPOS, 0, 0);
  MasterMedium1D.ETime = pos;
  wchar_t buf[4];
  wsprintfW(buf, L"%ld", pos);

  SetWindowTextW(ETIMESTATIC, buf);
}





  void UpdatePhaseLabel(int Num)
 {
  LRESULT pos = SendMessageW(PHASECONSTTRACK, TBM_GETPOS, 0, 0);
  //MasterMedium1D.WAVESOURCES[Num].PhaseConstPerc = pos;
  wchar_t buf[10];
  wsprintfW(buf, L"%ld", pos);

  SetWindowTextW(PHASECONSTSTATIC, buf);
}







void UpdateWaveSourceList(int Num)
{

	SendMessage((HWND)ReturnOneDHWND(),WM_COMMAND,(long)ID_MESSAGE_UPDATEONED, Num);

}









#endif



 /*int YAXISLIMITSROW = 165;
	// y axis limits edit boxes and static text below
		CreateWindowW(L"STATIC", L"Y Axis Limits [m] :",
          WS_VISIBLE | WS_CHILD ,
          390, YAXISLIMITSROW, 150, 30,
          hwnd, (HMENU) IDS_YAXISTEXT1D  , NULL, NULL);	 

	CreateWindowW(L"STATIC", L" to ",
          WS_VISIBLE | WS_CHILD ,
          600, YAXISLIMITSROW-15, 15, 30,
          hwnd, (HMENU) 9000  , NULL, NULL);
	
	YLOWBOX = CreateWindowW(L"Edit", L"-10",			// lower x limit edit box
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        530, YAXISLIMITSROW-3, 60, 25, hwnd, (HMENU) IDE_LYAXISLIMITS1D ,
        NULL, NULL);
		
	YHIGHBOX = CreateWindowW(L"Edit", L"10",			// upper x limit edit box
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        630, YAXISLIMITSROW-3, 60, 25, hwnd, (HMENU) IDE_HYAXISLIMITS1D ,
        NULL, NULL);
		*/