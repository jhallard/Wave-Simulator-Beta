#include <windows.h>
#include <vector>
#include <cmath>


#include "WaveSimHeader.h"
#include "WaveDefines.h"
#include "OneDWaveClass.h"
#include "TwoDWaveClass.h"


//OneDWaveMedium MasterMedium1D;

static HWND OneDHWND = NULL;
static HWND TwoDHWND = NULL;

HWND &ReturnOneDHWND()
{

	return OneDHWND;

}


HWND &ReturnTwoDHWND()
{

	return TwoDHWND;

}


HINSTANCE MainInstance; // main instance of our program

int WINAPI WinMain( HINSTANCE MainInstance, 
	HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, 
	int nCmdShow )
{


  MSG  msg ; // name of the messages we send out   
  HWND hwnd; // main handle to the window

  
	// ****main window definition and registration*****
  
   WNDCLASSEX WaveMain = {0};
  WaveMain.cbSize           = sizeof(WNDCLASSEX);
  WaveMain.lpfnWndProc      = (WNDPROC) WaveMainProc;
  WaveMain.hInstance        = MainInstance;
  WaveMain.hbrBackground    = BackGround;
  WaveMain.lpszClassName    = TEXT("WaveSimMain");
  RegisterClassEx(&WaveMain);
  hwnd = CreateWindow( WaveMain.lpszClassName, TEXT("Wave Simulator"),
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                250, 40, 600, 690, NULL, NULL, MainInstance, NULL);  



  // Constructors for our wavemedium classes

  //MasterMedium1D.SetWaveVelocity();


  
  while( GetMessage(&msg, NULL, 0, 0)) {
	  TranslateMessage(&msg);
	  DispatchMessage(&msg);
  }
  return (int) msg.wParam;
}




// MAIN MENU CALLBACK PROCEDURE

LRESULT CALLBACK WaveMainProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

	HWND MainMenuTitleBox;     // hanle to the static box that holds the main menu title image
	HWND Twodwavepic;
	HWND Onedwavepic;

	HANDLE MainMenuTitleImage; // handle to the itmap image of our main menu title image
	HANDLE Twodwavepicimage;
	HANDLE Onedwavepicimage;

	HINSTANCE hInstance;

	// registration of the different windows classes
	
	// one D window
	WNDCLASSEX OneDWaveWindow = {0};
  OneDWaveWindow.cbSize           = sizeof(WNDCLASSEX);
  OneDWaveWindow.lpfnWndProc      = (WNDPROC) OneDWaveProc;
  OneDWaveWindow.hInstance        = MainInstance;
  OneDWaveWindow.hbrBackground    = BackGround;
  OneDWaveWindow.lpszClassName    = TEXT("OneDWaveSim");
  RegisterClassEx(&OneDWaveWindow);
  
	// two d window
    WNDCLASSEX TwoDWaveWindow = {0};
  TwoDWaveWindow.cbSize           = sizeof(WNDCLASSEX);
  TwoDWaveWindow.lpfnWndProc      = (WNDPROC) TwoDWaveProc;
  TwoDWaveWindow.hInstance        = MainInstance;
  TwoDWaveWindow.hbrBackground    = BackGround;
  TwoDWaveWindow.lpszClassName    = TEXT("TwoDWaveSim");
  RegisterClassEx(&TwoDWaveWindow);



	switch(msg)
	{



	case WM_CREATE:
		{



				//****************** BUTTONS BELOW ***************************
			//___________________________________________________________________\\

			// CREATE 1D WAVE BUTTON
	CreateWindow(TEXT("button"), TEXT("Create 1D Waves"),    
	      WS_VISIBLE | WS_CHILD ,
	      75, 605, 140, 30,        
	      hwnd, (HMENU) IDB_CREATE1D, NULL, NULL); 

	// CREATE 2D WAVE BUTTON
	CreateWindow(TEXT("button"), TEXT("Create 2D Waves"),    
	      WS_VISIBLE | WS_CHILD ,
	      225, 605, 140, 30,        
	      hwnd, (HMENU) IDB_CREATE2D, NULL, NULL); 

	// CREATE 1D WAVE BUTTON
	CreateWindow(TEXT("button"), TEXT("Close Program"),    
	      WS_VISIBLE | WS_CHILD ,
	      375, 605, 140, 30,        
	      hwnd, (HMENU) IDB_CLOSEPROGRAM, NULL, NULL); 




				//****************** IMAGES BELOW ***************************
			//___________________________________________________________________\\



			  		 		//CREATES THE TITLE IMAGE FOR THE MAIN MENU TITLE
MainMenuTitleBox = CreateWindowEx (NULL, L"STATIC", NULL,
WS_CHILD | WS_VISIBLE | SS_BITMAP, 80 , 0, 0, 0, hwnd, 0, NULL, NULL);

MainMenuTitleImage = LoadImage(NULL, L"C:\\Users\\John\\Pictures\\WaveSimPics\\MainTitle.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
SendMessage(MainMenuTitleBox, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) MainMenuTitleImage);



							// the picture of the 2d wave for the main menu
Twodwavepic = CreateWindowEx (NULL, L"STATIC", NULL,
WS_CHILD | WS_VISIBLE | SS_BITMAP, 70, 310, 0, 0, hwnd, 0, NULL, NULL);

Twodwavepicimage = LoadImage(NULL, L"C:\\Users\\John\\Pictures\\WaveSimPics\\2DWavePic.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
SendMessage(Twodwavepic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) Twodwavepicimage);




							// the picture of the 1d wave
Onedwavepic = CreateWindowEx (NULL, L"STATIC", NULL,
WS_CHILD | WS_VISIBLE | SS_BITMAP, 70, 80, 0, 0, hwnd, 0, NULL, NULL);

Onedwavepicimage = LoadImage(NULL,L"C:\\Users\\John\\Pictures\\WaveSimPics\\1DWavePic.bmp", IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE);
SendMessage(Onedwavepic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) Onedwavepicimage);


		}
		break; // end case WM CREATE





		// ____++++++++============= CASE WM COMMAND BELOW =============+++++++++++++_____________   \\


	case WM_COMMAND:
		{


			switch(LOWORD(wParam))
			{




				case IDB_CREATE1D:
				{


					// create the window to display the 1d wave simulation editor
					OneDHWND = CreateWindow( OneDWaveWindow.lpszClassName, TEXT("Wave Simulator - 1-D Waves"),
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                200, 140, 830, 500, NULL, NULL, MainInstance, NULL);


				}break; // end case CREATE1D Sim



			case IDB_CREATE2D:
				{


					// create the window to display the 2d wave simulation editor
					TwoDHWND = CreateWindow( TwoDWaveWindow.lpszClassName, TEXT("Wave Simulator - 2-D Waves"),
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                200, 140, 830, 500, NULL, NULL, MainInstance, NULL);


				}break; // end case CREATE2D Sim




			case(IDB_CLOSEPROGRAM):
				PostQuitMessage(0);
				break;


			}// END SWITCH ON LOWORDwParam FOR WM COMMAND
			

		}
		break; //END CASE WM COMMAND



		



	case WM_DESTROY:
		PostQuitMessage(0);
		break;// end case WM_DESTROY



	} // END SWITCH ON MESSAGE

	  return (DefWindowProc(hwnd, msg, wParam, lParam)); 

}




//OneDWaveMedium &Return1DWaveMedium()
//{
//
//	return MasterMedium1D;
//
//
//}


