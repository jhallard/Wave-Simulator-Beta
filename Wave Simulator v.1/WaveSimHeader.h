#ifndef WAVESIMHEADER_H
#define WAVESIMHEADER_H

#include <Windows.h>


// wave call back procedures include files
#include "OneDWaveProc.h"
#include <string>
#include "TwoDWaveProc.h"





// +++++++++++++++++++COLORS USED IN THIS PROGRAM+++++++++++++++++++++++++++


// Colors used in this program
HBRUSH BackGround = CreateSolidBrush(RGB(0,0,0));//(RGB(400, 400, 400));
HBRUSH Text = CreateSolidBrush(RGB(255, 255, 255));









// ++++++++++++++++++ CALLBACK FUNCTIONS ++++++++++++++++++++++++



// callback for main window
LRESULT CALLBACK WaveMainProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK TwoDWaveProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK OneDWaveProc(HWND, UINT, WPARAM, LPARAM);








// ++++++++++++++++functions that need to be called from all files+++++++++++++++++++++++++



OneDWaveMedium &Return1DWaveMedium();

TwoDWaveMedium &Return2DWaveMedium();






//+++++++++++++++++++++ Window Declarations! ++++++++++++++++++++++++






#endif