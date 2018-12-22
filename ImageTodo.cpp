//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "ImageTodo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
int imageWidth,imageHeight;
unsigned char *imageRowInitialPosition;
int hashTable [256];
//---------------------------------------------------------------------------
float setValue(float v) {
	if(v>255)
		return 255;
	else if (v<0) {
		return 0;
		 }
	else
		return v;
}
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	TrackBar1->Max = 255;
	TrackBar1->Min = 0;
	TrackBar1->SetTick(256);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::OpenImage1Click(TObject *Sender)
{
	if(OpenPictureDialog1->Execute())
	{
		Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
		Image7->Picture->LoadFromFile(OpenPictureDialog1->FileName);
		imageWidth = Image1->Picture->Width;
		imageHeight = Image1->Picture->Height;
		Image5->Picture->LoadFromFile(OpenPictureDialog1->FileName);
		Image12->Picture->LoadFromFile(OpenPictureDialog1->FileName);
        int r,g,b,Y;
		float R,G,B;
		for(int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			Y =  128;
			R  = Y + 1.13983 * (i - 128);
			G  = Y - 0.39465 * (j - 128) - 0.58060 * (i - 128);
			B  = Y + 2.03211 * (j - 128);
			r =  setValue(R);
			g = setValue(G);
			b = setValue(B);
			Image13->Canvas->Pen->Color = (TColor)RGB(r,g,b);
			Image13->Canvas->Ellipse(j-1,i-1,j+1,i+1);
		}
	}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
	Image2->Picture = NULL;
	Image3->Picture = NULL;
	Image4->Picture = NULL;


	int redPixelCount[256], greenPixelCount[256], bluePixelCount[256];
	int redPixelMax = 0, greenPixelMax = 0, bluePixelMax = 0;
	float tempRedPixel,tempGreenPixel,tempBluePixel;
	for (int i = 0; i < 256; i++)
	{
		redPixelCount[i] = 0;
		greenPixelCount[i] = 0;
		bluePixelCount[i] = 0;
	}
	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image1->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			redPixelCount[imageRowInitialPosition[j*3]] += 1;
			greenPixelCount[imageRowInitialPosition[j*3+1]] += 1;
			bluePixelCount[imageRowInitialPosition[j*3+2]] += 1;
		}
	}
	for (int i = 1; i < 256; i++) {
		redPixelCount[i] = redPixelCount[i] + redPixelCount[i-1];
		greenPixelCount[i] = greenPixelCount[i] + greenPixelCount[i-1];
		bluePixelCount[i] = bluePixelCount[i] + bluePixelCount[i-1];
	}
	for (int i = 0; i < 256; i++)
	{
		if(redPixelMax < redPixelCount[i])
			redPixelMax = redPixelCount[i];
		if(greenPixelMax < greenPixelCount[i])
			greenPixelMax = greenPixelCount[i];
		if(bluePixelMax < bluePixelCount[i])
			bluePixelMax = bluePixelCount[i];
	}

	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image1->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			imageRowInitialPosition[j*3] = (float)redPixelCount[imageRowInitialPosition[j*3]]/(float)redPixelMax * 255;
			imageRowInitialPosition[j*3+1] = (float)greenPixelCount[imageRowInitialPosition[j*3+1]]/(float)greenPixelMax * 255;
			imageRowInitialPosition[j*3+2] = (float)bluePixelCount[imageRowInitialPosition[j*3+2]]/(float)bluePixelMax * 255;
		}
	}
   Image1->Refresh();
   redPixelMax = 0, greenPixelMax = 0, bluePixelMax = 0;
   for (int i = 0; i < 256; i++)
	{
		redPixelCount[i] = 0;
		greenPixelCount[i] = 0;
		bluePixelCount[i] = 0;
	}
    	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image1->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			redPixelCount[imageRowInitialPosition[j*3]] += 1;
			greenPixelCount[imageRowInitialPosition[j*3+1]] += 1;
			bluePixelCount[imageRowInitialPosition[j*3+2]] += 1;
		}
	}
	for (int i = 0; i < 256; i++)
	{
		if(redPixelMax < redPixelCount[i])
			redPixelMax = redPixelCount[i];
		if(greenPixelMax < greenPixelCount[i])
			greenPixelMax = greenPixelCount[i];
		if(bluePixelMax < bluePixelCount[i])
			bluePixelMax = bluePixelCount[i];
	}
	Image2->Canvas->Pen->Width = 2;
	Image3->Canvas->Pen->Width = 2;
	Image4->Canvas->Pen->Width = 2;



	Image2->Canvas->Pen->Color = (TColor)RGB(244,66,104);
	Image3->Canvas->Pen->Color = (TColor)RGB(57,130,65);
	Image4->Canvas->Pen->Color = (TColor)RGB(62,114,145);
	for (int i = 0; i < 256; i++) {
		Image2->Canvas->MoveTo(i+2,115);
		Image3->Canvas->MoveTo(i+2,115);
		Image4->Canvas->MoveTo(i+2,115);
		tempRedPixel = (float)redPixelCount[i]/(float)redPixelMax*100;
		tempGreenPixel = (float)greenPixelCount[i]/(float)greenPixelMax*100;
		tempBluePixel = (float)bluePixelCount[i]/(float)bluePixelMax*100;
		Image2->Canvas->LineTo(i+2,115 - tempRedPixel);
		Image3->Canvas->LineTo(i+2,115 - tempGreenPixel);
		Image4->Canvas->LineTo(i+2,115 - tempBluePixel);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
    Image2->Picture = NULL;
	Image3->Picture = NULL;
	Image4->Picture = NULL;


	int redPixelCount[256], greenPixelCount[256], bluePixelCount[256];
	int redPixelMax = 0, greenPixelMax = 0, bluePixelMax = 0;
	float tempRedPixel,tempGreenPixel,tempBluePixel;
	for (int i = 0; i < 256; i++)
	{
		redPixelCount[i] = 0;
		greenPixelCount[i] = 0;
		bluePixelCount[i] = 0;
	}
	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image1->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			redPixelCount[imageRowInitialPosition[j*3]] += 1;
			greenPixelCount[imageRowInitialPosition[j*3+1]] += 1;
			bluePixelCount[imageRowInitialPosition[j*3+2]] += 1;
		}
	}
	for (int i = 0; i < 256; i++)
	{
		if(redPixelMax < redPixelCount[i])
			redPixelMax = redPixelCount[i];
		if(greenPixelMax < greenPixelCount[i])
			greenPixelMax = greenPixelCount[i];
		if(bluePixelMax < bluePixelCount[i])
			bluePixelMax = bluePixelCount[i];
	}
	Image2->Canvas->Pen->Width = 2;
	Image3->Canvas->Pen->Width = 2;
	Image4->Canvas->Pen->Width = 2;



	Image2->Canvas->Pen->Color = (TColor)RGB(244,66,104);
	Image3->Canvas->Pen->Color = (TColor)RGB(57,130,65);
	Image4->Canvas->Pen->Color = (TColor)RGB(62,114,145);
	for (int i = 0; i < 256; i++) {
		Image2->Canvas->MoveTo(i+2,115);
		Image3->Canvas->MoveTo(i+2,115);
		Image4->Canvas->MoveTo(i+2,115);
		tempRedPixel = (float)redPixelCount[i]/(float)redPixelMax*100;
		tempGreenPixel = (float)greenPixelCount[i]/(float)greenPixelMax*100;
		tempBluePixel = (float)bluePixelCount[i]/(float)bluePixelMax*100;
		Image2->Canvas->LineTo(i+2,115 - tempRedPixel);
		Image3->Canvas->LineTo(i+2,115 - tempGreenPixel);
		Image4->Canvas->LineTo(i+2,115 - tempBluePixel);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button3Click(TObject *Sender)
{
	int inputHighlevel = StrToInt(Edit1->Text);
	int inputLowlevel = StrToInt(Edit2->Text);
	int outHighlevel = StrToInt(Edit3->Text);
	int outLowlevel = StrToInt(Edit4->Text);
	float levelmap[256];
	for(int i = 0; i< 256; i++)
	 {
		if(i <= inputLowlevel ) {
			levelmap[i] = outLowlevel + (outHighlevel-outLowlevel) /(inputHighlevel-inputLowlevel);
		}
		else if(i  >= inputHighlevel) {
			levelmap[i] = outLowlevel + (inputHighlevel-inputLowlevel)* (outHighlevel-outLowlevel) /(inputHighlevel-inputLowlevel);
		}
		else
			levelmap[i] = outLowlevel + (i - inputLowlevel)* (outHighlevel-outLowlevel) / (inputHighlevel-inputLowlevel);
	 }
	 for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image5->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			for (int k = 0; k < 3; k++) {
				imageRowInitialPosition[j*3+k] = levelmap[imageRowInitialPosition[j*3+k]];
			}

		}
	}
   Image5->Refresh();
   Image6->Canvas->MoveTo(0,256-outLowlevel);
   Image6->Canvas->LineTo(outLowlevel,256-outLowlevel);
   Image6->Canvas->LineTo(outHighlevel,256-outHighlevel);
   Image6->Canvas->LineTo(256,256-outHighlevel);
   
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Image6MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Image6->Picture = NULL;
	int iT = 255-Y;
	int iS = X;
	float c = iT-iS;
	float d = iS*iS - 255*iS;
	float variableA = c / d;
	float variableB = (1 - variableA *255);
	float curveY;
	int t ;
	for (int i = 0; i < 256; i++) {
		curveY = variableA *i*i  + variableB*i;
		t = curveY;
		if(t > 255 )
			t = 255;
		else if(t < 0)
			t = 0;
		Image6->Canvas->Ellipse(i-1,255-t+1,i+1,255-t-1);
		hashTable[i] = t;
	}
	Image6->Canvas->Pen->Color= (TColor)RGB(255,0,0);
	Image6->Canvas->Ellipse(X-2,255-Y+2,X+2,255-Y-2);	
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button4Click(TObject *Sender)
{
	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image5->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				imageRowInitialPosition[j*3+k] = hashTable[imageRowInitialPosition[j*3+k]];
			}
		}
	}
	Image5->Refresh();	
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button5Click(TObject *Sender)
{
	int** redFilterMap = new int* [imageHeight];
	int** greenFilterMap = new int* [imageHeight];
	int** blueFilterMap = new int* [imageHeight];
	int** initRedFilterMap = new int* [imageHeight];
	int** initGreenFilterMap = new int* [imageHeight];
	int** initBlueFilterMap = new int* [imageHeight];
	int slideMap[4096];
	int tempCount; 
	for (int i = 0; i < 4096; i++)
		slideMap[i] = i / 16;
	for (int i = 0; i < imageHeight; i++){
		redFilterMap[i] = new int [imageWidth];
		greenFilterMap[i] = new int [imageWidth];
		blueFilterMap[i] = new int [imageWidth];
		initRedFilterMap[i] = new int [imageWidth];
		initGreenFilterMap[i] = new int [imageWidth];
		initBlueFilterMap[i] = new int [imageWidth];
	}

	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image7->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			initRedFilterMap[i][j] = imageRowInitialPosition[j*3];
			initGreenFilterMap[i][j] = imageRowInitialPosition[j*3+1];
			initBlueFilterMap[i][j] = imageRowInitialPosition[j*3+2];
			redFilterMap[i][j] = imageRowInitialPosition[j*3];
			greenFilterMap[i][j] = imageRowInitialPosition[j*3+1];
			blueFilterMap[i][j] = imageRowInitialPosition[j*3+2];
		}
	}
	for (int i = 1; i < imageHeight-1; i++)
	{
		for (int j = 1; j < imageWidth-1; j++)
		{
			tempCount =   initRedFilterMap[i-1][j-1] * 1
						+ initRedFilterMap[i-1][j-1] * 2
						+ initRedFilterMap[i-1][j+1] * 1
						+ initRedFilterMap[i][j-1] * 2
						+ initRedFilterMap[i][j] * 4
						+ initRedFilterMap[i][j+1] * 2
						+ initRedFilterMap[i+1][j-1] * 1
						+ initRedFilterMap[i+1][j] * 2
						+ initRedFilterMap[i+1][j+1] * 1;
			redFilterMap[i][j]  = slideMap[tempCount];			
			tempCount =initGreenFilterMap[i-1][j-1] * 1
					+ initGreenFilterMap[i-1][j-1] * 2
					+ initGreenFilterMap[i-1][j+1] * 1
					+ initGreenFilterMap[i][j-1] * 2
					+ initGreenFilterMap[i][j] * 4
					+ initGreenFilterMap[i][j+1] * 2
					+ initGreenFilterMap[i+1][j-1] * 1
					+ initGreenFilterMap[i+1][j] * 2
					+ initGreenFilterMap[i+1][j+1] * 1;
			greenFilterMap[i][j]  = slideMap[tempCount];
			tempCount = initBlueFilterMap[i-1][j-1] * 1
					+ initBlueFilterMap[i-1][j-1] * 2
					+ initBlueFilterMap[i-1][j+1] * 1
					+ initBlueFilterMap[i][j-1] * 2
					+ initBlueFilterMap[i][j] * 4
					+ initBlueFilterMap[i][j+1] * 2
					+ initBlueFilterMap[i+1][j-1] * 1
					+ initBlueFilterMap[i+1][j] * 2
					+ initBlueFilterMap[i+1][j+1] * 1;
			blueFilterMap[i][j]  = slideMap[tempCount];
		}
	}
	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image7->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			imageRowInitialPosition[j*3] = redFilterMap[i][j];
			imageRowInitialPosition[j*3+1] = greenFilterMap[i][j];
			imageRowInitialPosition[j*3+2] = blueFilterMap[i][j];
		}
	}
	Image7->Refresh();
	delete[] redFilterMap; 
	delete[] greenFilterMap;
	delete[] blueFilterMap;
	delete[] initRedFilterMap;
	delete[] initGreenFilterMap;
	delete[] initBlueFilterMap;	



		
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button6Click(TObject *Sender)
{
	srand( time(NULL) );
	int r;
	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image7->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			r = (rand()%100) +1;
			if( r > 95) {
				imageRowInitialPosition[j*3] = 0;
				imageRowInitialPosition[j*3+1] = 0;
				imageRowInitialPosition[j*3+2] = 0;
			}
			else if( r < 5) {
				imageRowInitialPosition[j*3] = 255;
				imageRowInitialPosition[j*3+1] = 255;
				imageRowInitialPosition[j*3+2] = 255;
            }
		}
	}
	Image7->Refresh();	
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button7Click(TObject *Sender)
{
	int** redFilterMap = new int* [imageHeight];
	int** greenFilterMap = new int* [imageHeight];
	int** blueFilterMap = new int* [imageHeight];
	int** initRedFilterMap = new int* [imageHeight];
	int** initGreenFilterMap = new int* [imageHeight];
	int** initBlueFilterMap = new int* [imageHeight];
	int temparray[9];
	int min_idx;
	int temp; 
	for (int i = 0; i < imageHeight; i++){
		redFilterMap[i] = new int [imageWidth];
		greenFilterMap[i] = new int [imageWidth];
		blueFilterMap[i] = new int [imageWidth];
		initRedFilterMap[i] = new int [imageWidth];
		initGreenFilterMap[i] = new int [imageWidth];
		initBlueFilterMap[i] = new int [imageWidth];
	}
	Memo1->Lines->Add("1");
	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image7->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			initRedFilterMap[i][j] = imageRowInitialPosition[j*3];
			initGreenFilterMap[i][j] = imageRowInitialPosition[j*3+1];
			initBlueFilterMap[i][j] = imageRowInitialPosition[j*3+2];
			redFilterMap[i][j] = imageRowInitialPosition[j*3];
			greenFilterMap[i][j] = imageRowInitialPosition[j*3+1];
			blueFilterMap[i][j] = imageRowInitialPosition[j*3+2];
		}
	}
	Memo1->Lines->Add("2");
	for (int i = 1; i < imageHeight-1; i++)
	{
		for (int j = 1; j < imageWidth-1; j++)
		{
			temparray[0] = initRedFilterMap[i-1][j-1];
			temparray[1] = initRedFilterMap[i-1][j-1];
			temparray[2] = initRedFilterMap[i-1][j+1];
			temparray[3] = initRedFilterMap[i][j-1];
			temparray[4] = initRedFilterMap[i][j];
			temparray[5] = initRedFilterMap[i][j+1];
			temparray[6] = initRedFilterMap[i+1][j-1];
			temparray[7] = initRedFilterMap[i+1][j];
			temparray[8] = initRedFilterMap[i+1][j+1];
			for (int k = 0; k < 9; k++) 
			{ 
				min_idx = k; 
				for (int l = k+1; l < 9 ; l++) 
				  if (temparray[l] < temparray[min_idx]) 
					min_idx = l;
				temp = temparray[min_idx];
				temparray[min_idx] = temparray[k]; 
				temparray[k] = temp;
			} 
			redFilterMap[i][j] = temparray[4]; 		
			temparray[0] = initGreenFilterMap[i-1][j-1];
			temparray[1] = initGreenFilterMap[i-1][j-1];
			temparray[2] = initGreenFilterMap[i-1][j+1];
			temparray[3] = initGreenFilterMap[i][j-1];
			temparray[4] = initGreenFilterMap[i][j];
			temparray[5] = initGreenFilterMap[i][j+1];
			temparray[6] = initGreenFilterMap[i+1][j-1];
			temparray[7] = initGreenFilterMap[i+1][j];
			temparray[8] = initGreenFilterMap[i+1][j+1];
			for (int k = 0; k < 9; k++) 
			{ 
				min_idx = k; 
				for (int l = k+1; l < 9 ; l++) 
				  if (temparray[l] < temparray[min_idx]) 
					min_idx = l;
				temp = temparray[min_idx];
				temparray[min_idx] = temparray[k]; 
				temparray[k] = temp;
			} 
			greenFilterMap[i][j] = temparray[4]; 
			temparray[0] = initBlueFilterMap[i-1][j-1];
			temparray[1] = initBlueFilterMap[i-1][j-1];
			temparray[2] = initBlueFilterMap[i-1][j+1];
			temparray[3] = initBlueFilterMap[i][j-1];
			temparray[4] = initBlueFilterMap[i][j];
			temparray[5] = initBlueFilterMap[i][j+1];
			temparray[6] = initBlueFilterMap[i+1][j-1];
			temparray[7] = initBlueFilterMap[i+1][j];
			temparray[8] = initBlueFilterMap[i+1][j+1];
			for (int k = 0; k < 9; k++) 
			{ 
				min_idx = k; 
				for (int l = k+1; l < 9 ; l++) 
				  if (temparray[l] < temparray[min_idx]) 
					min_idx = l;
				temp = temparray[min_idx];
				temparray[min_idx] = temparray[k]; 
				temparray[k] = temp;
			} 
			blueFilterMap[i][j] = temparray[4]; 
		}
	}
	Memo1->Lines->Add("3");
	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image7->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			imageRowInitialPosition[j*3] = redFilterMap[i][j];
			imageRowInitialPosition[j*3+1] = greenFilterMap[i][j];
			imageRowInitialPosition[j*3+2] = blueFilterMap[i][j];
		}
	}
	Memo1->Lines->Add("4");
	Image7->Refresh();
	delete[] redFilterMap; 
	delete[] greenFilterMap;
	delete[] blueFilterMap;
	delete[] initRedFilterMap;
	delete[] initGreenFilterMap;
	delete[] initBlueFilterMap;	
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button8Click(TObject *Sender)
{
	int** redFilterMap = new int* [imageHeight];
	int** greenFilterMap = new int* [imageHeight];
	int** blueFilterMap = new int* [imageHeight];
	int** initRedFilterMap = new int* [imageHeight];
	int** initGreenFilterMap = new int* [imageHeight];
	int** initBlueFilterMap = new int* [imageHeight];
	int slideMap[4096];
	int tempCount;
	for (int i = 0; i < imageHeight; i++){
		redFilterMap[i] = new int [imageWidth];
		greenFilterMap[i] = new int [imageWidth];
		blueFilterMap[i] = new int [imageWidth];
		initRedFilterMap[i] = new int [imageWidth];
		initGreenFilterMap[i] = new int [imageWidth];
		initBlueFilterMap[i] = new int [imageWidth];
	}

	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image7->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			initRedFilterMap[i][j] = imageRowInitialPosition[j*3];
			initGreenFilterMap[i][j] = imageRowInitialPosition[j*3+1];
			initBlueFilterMap[i][j] = imageRowInitialPosition[j*3+2];
			redFilterMap[i][j] = imageRowInitialPosition[j*3];
			greenFilterMap[i][j] = imageRowInitialPosition[j*3+1];
			blueFilterMap[i][j] = imageRowInitialPosition[j*3+2];
		}
	}
	for (int i = 1; i < imageHeight-1; i++)
	{
		for (int j = 1; j < imageWidth-1; j++)
		{
			tempCount  = + initRedFilterMap[i-1][j] * -1
						 + initRedFilterMap[i][j-1] * -1
						 + initRedFilterMap[i][j] * 5
						 + initRedFilterMap[i][j+1] * -1
						 + initRedFilterMap[i+1][j] * -1;
			if (tempCount > 255) {
				tempCount = 255;
			}
			else if (tempCount < 0) {
				tempCount = 0;
			}
			redFilterMap[i][j] = tempCount;
			tempCount  = + initGreenFilterMap[i-1][j] * -1
						 + initGreenFilterMap[i][j-1] * -1
						 + initGreenFilterMap[i][j] * 5
						 + initGreenFilterMap[i][j+1] * -1
						 + initGreenFilterMap[i+1][j] * -1;

			if (tempCount > 255) {
				tempCount = 255;
			}
			else if (tempCount < 0) {
				tempCount = 0;
			}
			greenFilterMap[i][j] = tempCount;
			tempCount  = + initBlueFilterMap[i-1][j] * -1
						 + initBlueFilterMap[i][j-1] * -1
						 + initBlueFilterMap[i][j] * 5
						 + initBlueFilterMap[i][j+1] * -1
						 + initBlueFilterMap[i+1][j] * -1;
			if (tempCount > 255) {
				tempCount = 255;
			}
			else if (tempCount < 0) {
				tempCount = 0;
			}
			blueFilterMap[i][j] = tempCount;
		}
	}
	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image7->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			imageRowInitialPosition[j*3] = redFilterMap[i][j];
			imageRowInitialPosition[j*3+1] = greenFilterMap[i][j];
			imageRowInitialPosition[j*3+2] = blueFilterMap[i][j];
		}
	}
	Image7->Refresh();
	delete[] redFilterMap; 
	delete[] greenFilterMap;
	delete[] blueFilterMap;
	delete[] initRedFilterMap;
	delete[] initGreenFilterMap;
	delete[] initBlueFilterMap;		
}
//---------------------------------------------------------------------------
void __fastcall TForm2::TrackBar1Change(TObject *Sender)
{
	int r,g,b,Y;
	float R,G,B;



	for(int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			Y =  TrackBar1->Position;
			R  = Y + 1.13983 * (i - 128);
			G  = Y - 0.39465 * (j - 128) - 0.58060 * (i - 128);
			B  = Y + 2.03211 * (j - 128);
			r =  setValue(R);
			g = setValue(G);
			b = setValue(B);
			Image11->Canvas->Pen->Color = (TColor)RGB(r,g,b);
			Image11->Canvas->Ellipse(j-1,i-1,j+1,i+1);
			Image8->Canvas->Pen->Color = (TColor)RGB(i,j,TrackBar1->Position);
			Image8->Canvas->Ellipse(j-1,i-1,j+1,i+1);
			Image9->Canvas->Pen->Color = (TColor)RGB(TrackBar1->Position,i,j);
			Image9->Canvas->Ellipse(j-1,i-1,j+1,i+1);
			Image10->Canvas->Pen->Color = (TColor)RGB(i,TrackBar1->Position,j);
			Image10->Canvas->Ellipse(j-1,i-1,j+1,i+1);
		}
	}	
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Image13MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	int average;
	int r,g,b,uY;
	float R,G,B;

	for (int i = 0; i < imageHeight; i++)
	{
		imageRowInitialPosition = (unsigned char *)Image12->Picture->Bitmap->ScanLine[i];
		for (int j = 0; j < imageWidth; j++)
		{
			average =  (imageRowInitialPosition[j*3]+imageRowInitialPosition[j*3+1] +imageRowInitialPosition[j*3+2]) /3 ;
			uY =  average * 0.299 + average * 0.587 + average * 0.114;
			R  = uY + 1.13983 * (X - 128);
			G  = uY - 0.39465 * (Y - 128) - 0.58060 * (X - 128);
			B  = uY + 2.03211 * (Y - 128);
			r =  setValue(R);
			g = setValue(G);
			b = setValue(B);
			imageRowInitialPosition[j*3] = r;
			imageRowInitialPosition[j*3+1] = g;
			imageRowInitialPosition[j*3+2] = b;

		}
	}
    Image12->Refresh();
}
//---------------------------------------------------------------------------
