//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Image8->Canvas->Brush->Color =(TColor)RGB(0,0,0);
	Image8->Canvas->FillRect(Rect(0,0,256,256));
	Image8->Canvas->MoveTo(0,255);
	Image8->Canvas->Pen->Color = (TColor)RGB(0,255,255);
	Image8->Canvas->LineTo(255,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1Click(TObject *Sender)
{
	 OpenPictureDialog1->Execute();
}
//---------------------------------------------------------------------------

//讀檔
void __fastcall TForm1::image2Click(TObject *Sender)
{
	if( OpenPictureDialog1->Execute() )
	{
		Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
		Image7->Picture->LoadFromFile(OpenPictureDialog1->FileName);
        Image10->Picture->LoadFromFile(OpenPictureDialog1->FileName);
	}
	iImageWidth  = Image1->Picture->Width;
	iImageHeight = Image1->Picture->Height;

}
//---------------------------------------------------------------------------

//負片
void __fastcall TForm1::Inverse1Click(TObject *Sender)
{
	for(j=0; j<iImageHeight; j++)
		{
		bPtrImageRow = (Byte *)Image7->Picture->Bitmap->ScanLine[j];
		for(i=0; i<iImageWidth; i++)
			for(k=0; k<3; k++)
				bPtrImageRow[3*i+k] = 255 - bPtrImageRow[3*i+k];
		}
	Image7->Refresh();
}
//---------------------------------------------------------------------------

//PDF
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
	//歸零
	for(i=0; i<256;i++)
		{
		iHB[i]=0;
		iHG[i]=0;
		iHR[i]=0;
		}
		iHRMax=0;
		iHGMax=0;
		iHBMax=0;
	for(int j=0; j<iImageHeight; j++)
		{
		if(RadioButton1->Checked)
			bPtrImageRow = (Byte *)Image1->Picture->Bitmap->ScanLine[j];
		else
			bPtrImageRow = (Byte *)Image7->Picture->Bitmap->ScanLine[j];
		for(i=0; i<iImageWidth; i++)
			{
			iHB[bPtrImageRow[3*i+0]]++;
			iHG[bPtrImageRow[3*i+1]]++;
			iHR[bPtrImageRow[3*i+2]]++;
			}
		}

	Image4->Canvas->Brush->Color =(TColor)RGB(0,0,0);
	Image4->Canvas->FillRect(Rect(0,0,256,256));
	Image5->Canvas->Brush->Color =(TColor)RGB(0,0,0);
	Image5->Canvas->FillRect(Rect(0,0,256,256));
	Image6->Canvas->Brush->Color =(TColor)RGB(0,0,0);
	Image6->Canvas->FillRect(Rect(0,0,256,256));
	for(i=0; i<256; i++)
	{
		if(iHR[i]>iHRMax)
			iHRMax = iHR[i];
		if(iHG[i]>iHGMax)
			iHGMax = iHG[i];
		if(iHB[i]>iHBMax)
			iHBMax = iHB[i];
	}
	for(j=0; j<256; j++)
	{
		 Image4->Canvas->Pen->Color = clRed;
		 Image4->Canvas->MoveTo(j,255);
		 Image4->Canvas->LineTo(j,255-iHR[j]*255/iHRMax);

		 Image5->Canvas->Pen->Color = clGreen;
		 Image5->Canvas->MoveTo(j,255);
		 Image5->Canvas->LineTo(j,255-iHG[j]*255/iHGMax);

		 Image6->Canvas->Pen->Color = clBlue;
		 Image6->Canvas->MoveTo(j,255);
		 Image6->Canvas->LineTo(j,255-iHB[j]*255/iHBMax);
	}



}
//---------------------------------------------------------------------------

//CDF
void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
	//清除之前的圖 & 之前的資料
	Image4->Canvas->Brush->Color =(TColor)RGB(0,0,0);
	Image4->Canvas->FillRect(Rect(0,0,256,256));
	Image5->Canvas->Brush->Color =(TColor)RGB(0,0,0);
	Image5->Canvas->FillRect(Rect(0,0,256,256));
	Image6->Canvas->Brush->Color =(TColor)RGB(0,0,0);
	Image6->Canvas->FillRect(Rect(0,0,256,256));
	for(i=0; i<256;i++)
		{
		iHB[i]=0;
		iHG[i]=0;
		iHR[i]=0;
		}
	//統計
	for(int j=0; j<iImageHeight; j++)
		{
		if(RadioButton1->Checked)
			bPtrImageRow = (Byte *)Image1->Picture->Bitmap->ScanLine[j];
		else
			bPtrImageRow = (Byte *)Image7->Picture->Bitmap->ScanLine[j];
		for(i=0; i<iImageWidth; i++)
			{
			iHB[bPtrImageRow[3*i+0]]++;
			iHG[bPtrImageRow[3*i+1]]++;
			iHR[bPtrImageRow[3*i+2]]++;
			}
		}

	for(j=1; j<256; j++)
		{
		iHB[j]+=iHB[j-1];
		iHG[j]+=iHG[j-1];
		iHR[j]+=iHR[j-1];
		}
	//畫圖
	Image4->Canvas->MoveTo(0,255);
	Image5->Canvas->MoveTo(0,255);
	Image6->Canvas->MoveTo(0,255);
	for(j=0; j<256; j++)
	{
		 Image4->Canvas->Pen->Color = clRed;
		 //Image4->Canvas->MoveTo(j,255);
		 Image4->Canvas->LineTo(j,255-iHR[j]*255/iHR[255]);

		 Image5->Canvas->Pen->Color = clGreen;
		 //Image5->Canvas->MoveTo(j,255);
		 Image5->Canvas->LineTo(j,255-iHG[j]*255/iHG[255]);

		 Image6->Canvas->Pen->Color = clBlue;
		 //Image6->Canvas->MoveTo(j,255);
		 Image6->Canvas->LineTo(j,255-iHB[j]*255/iHB[255]);
	}


}
//---------------------------------------------------------------------------

//灰階
void __fastcall TForm1::N1Click(TObject *Sender)
{
	for(j=0; j<iImageHeight; j++)
		{
			bPtrImageRow = (Byte *)Image7->Picture->Bitmap->ScanLine[j];
		for(i=0; i<iImageWidth; i++)
			{
				bPtrImageRow[3*i+0] = bPtrImageRow[3*i+1] = bPtrImageRow[3*i+2] =(float)(bPtrImageRow[3*i+0]*0.33+bPtrImageRow[3*i+1]*0.33+bPtrImageRow[3*i+2]*0.33);
			}
		}
	Image7->Refresh();
}
//---------------------------------------------------------------------------

//調整色階

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	iInputMax = StrToInt(Edit1->Text) ;
	iInputMin = StrToInt(Edit2->Text) ;
	iOutputMax= StrToInt(Edit3->Text) ;
	iOutputMin= StrToInt(Edit4->Text) ;
	for(j=0; j<iImageHeight; j++)
		{
		bPtrImageRow =    (Byte *)Image7->Picture->Bitmap->ScanLine[j];
		bPtrNewImageRow = (Byte *)Image7->Picture->Bitmap->ScanLine[j];
		for(i=0; i<iImageWidth; i++)
			for(k=0; k<3; k++)
				{
				if(bPtrImageRow[3*i+k]>iInputMax)
					bPtrNewImageRow[3*i+k] = iOutputMax;
				else if(bPtrImageRow[3*i+k]<iInputMin)
					bPtrNewImageRow[3*i+k] = iOutputMin;
				else
					bPtrNewImageRow[3*i+k] = iOutputMin + (bPtrImageRow[3*i+k] - iInputMin)*((iOutputMax-iOutputMin)/(iInputMax-iInputMin));
				}
		}
	Image7->Refresh();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
	Edit1 ->Text = TrackBar1 -> Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
	Edit2 ->Text = TrackBar2 -> Position;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TrackBar3Change(TObject *Sender)
{
		Edit3 ->Text = TrackBar3 -> Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar4Change(TObject *Sender)
{
	Edit4 ->Text = TrackBar4 -> Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
	TrackBar1 -> Position = StrToInt(Edit1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
	TrackBar2 -> Position = StrToInt(Edit2->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3Change(TObject *Sender)
{
	TrackBar3 -> Position = StrToInt(Edit3->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit4Change(TObject *Sender)
{
	TrackBar4 -> Position = StrToInt(Edit4->Text);
}
//---------------------------------------------------------------------------


//調整曲線
void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
	dS = StrToInt(Edit5 ->Text);
	dT = StrToInt(Edit6 ->Text);
	if(dS<=0)
		{
		dS=1;
		Edit5->Text = dS;
		}
	if(dS>=255)
		{
		dS=254;
		Edit5->Text = dS;
		}
	Image8->Canvas->Brush->Color =(TColor)RGB(0,0,0);
	Image8->Canvas->FillRect(Rect(0,0,256,256));
	Image8->Canvas->MoveTo(0,255);
	Image8->Canvas->Brush->Color =(TColor)RGB(255,0,255);
	Image8->Canvas->FillRect(Rect(dS-2,255-(dT-2),dS+2,255-(dT+2)));
	dA = (dT - dS)/((dS*dS) - 255*dS);
	dB = 1-255*dA;
	for(i=0;i<256;i++)
		{
		dCurveTable[i]= dA*i*i + dB*i;
		if(dCurveTable[i]>255)
			dCurveTable[i]=255;
		if(dCurveTable[i]<0)
			dCurveTable[i]=0;
		Image8->Canvas->Pen->Color = (TColor)RGB(0,255,255);
		Image8->Canvas->LineTo(i,255-dCurveTable[i]);
		}
	Image8->Refresh();


	//iCurveTable[i]

    for(j=0; j<iImageHeight; j++)
		{
		bPtrImageRow =    (Byte *)Image1->Picture->Bitmap->ScanLine[j];
		bPtrNewImageRow = (Byte *)Image7->Picture->Bitmap->ScanLine[j];
		for(i=0; i<iImageWidth; i++)
			for(k=0; k<3; k++)
				{
					bPtrNewImageRow[3*i+k] = dCurveTable[bPtrImageRow[3*i+k]];
				}
		}
}
//---------------------------------------------------------------------------

//調整曲線
void __fastcall TForm1::Image8MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Edit5 ->Text = X;
	Edit6 ->Text = 255-Y;
	if(X<=0)
		{
		dS=1;
		Edit5->Text = dS;
		}
	if(X>=255)
		{
		dS=254;
		Edit5->Text = dS;
		}
	dS = StrToInt(Edit5 ->Text);
	dT = StrToInt(Edit6 ->Text);

	Image8->Canvas->Brush->Color =(TColor)RGB(0,0,0);
	Image8->Canvas->FillRect(Rect(0,0,256,256));
	Image8->Canvas->MoveTo(0,255);
	Image8->Canvas->Brush->Color =(TColor)RGB(255,0,255);
	Image8->Canvas->FillRect(Rect(dS-2,255-dT-2,dS+2,255-dT+2));
	dA = (dT - dS)/(dS*dS - 255*dS);
	dB = 1-255*dA;
	for(i=0;i<256;i++)
		{
		dCurveTable[i]= dA*i*i + dB*i;
		if(dCurveTable[i]>255)
			dCurveTable[i]=255;
		if(dCurveTable[i]<0)
			dCurveTable[i]=0;
		Image8->Canvas->Pen->Color = (TColor)RGB(0,255,255);
		Image8->Canvas->LineTo(i,255-dCurveTable[i]);
		}
	Image8->Refresh();
}
//---------------------------------------------------------------------------
/*平滑空間濾波器(1)
遮罩
1 1 1
1 1 1
1 1 1
*/
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	for(j=1; j<iImageHeight-1; j++)
		{
		bFrontImageRow =  (Byte *)Image10->Picture->Bitmap->ScanLine[j-1];
		bPtrImageRow =    (Byte *)Image10->Picture->Bitmap->ScanLine[j];
		bBehindImageRow = (Byte *)Image10->Picture->Bitmap->ScanLine[j+1];
		bPtrNewImageRow=  (Byte *)Image10->Picture->Bitmap->ScanLine[j];
		for(i=1; i<iImageWidth-1; i++)
			for(k=0; k<3; k++)
			{

				bPtrNewImageRow[3*i+k] = (bFrontImageRow[3*(i-1)+k] + bFrontImageRow[3*i+k] +bFrontImageRow[3*(i+1)+k]
										+bPtrImageRow[3*(i-1)+k]   + bPtrImageRow[3*i+k]   +bPtrImageRow[3*(i+1)+k]
										+bBehindImageRow[3*(i-1)+k]+ bBehindImageRow[3*i+k]+bBehindImageRow[3*(i+1)+k])/9;
			}
		}
		Image10->Refresh();
		Label7->Caption = "(1)" ;
}
//---------------------------------------------------------------------------
/*
平滑空間濾波器(4)
遮罩
1 2 1
2 4 2
1 2 1
*/
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	for(j=1; j<iImageHeight-1; j++)
		{
		bFrontImageRow =  (Byte *)Image10->Picture->Bitmap->ScanLine[j-1];
		bPtrImageRow =    (Byte *)Image10->Picture->Bitmap->ScanLine[j];
		bBehindImageRow = (Byte *)Image10->Picture->Bitmap->ScanLine[j+1];
		bPtrNewImageRow=  (Byte *)Image10->Picture->Bitmap->ScanLine[j];
		for(i=1; i<iImageWidth-1; i++)
			for(k=0; k<3; k++)
			{
				bPtrNewImageRow[3*i+k] = (bFrontImageRow[3*(i-1)+k] + 2*bFrontImageRow[3*i+k] +bFrontImageRow[3*(i+1)+k]
										+2*bPtrImageRow[3*(i-1)+k]   + 4*bPtrImageRow[3*i+k]   +2*bPtrImageRow[3*(i+1)+k]
										+bBehindImageRow[3*(i-1)+k]+ 2*bBehindImageRow[3*i+k]+bBehindImageRow[3*(i+1)+k])/16;
			}
		}
		Image10->Refresh();
		Label7->Caption = "(4)" ;
}
//---------------------------------------------------------------------------
/*
中值濾波器
*/
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	for(j=1; j<iImageHeight-1; j++)
		{
		int Temp;
		bFrontImageRow =  (Byte *)Image10->Picture->Bitmap->ScanLine[j-1];
		bPtrImageRow =    (Byte *)Image10->Picture->Bitmap->ScanLine[j];
		bBehindImageRow = (Byte *)Image10->Picture->Bitmap->ScanLine[j+1];
		bPtrNewImageRow=  (Byte *)Image10->Picture->Bitmap->ScanLine[j];
		for(i=1; i<iImageWidth-1; i++)
			for(k=0; k<3; k++)
			{
				iSortTable[0] = bFrontImageRow[3*(i-1)+k];
				iSortTable[1] = bFrontImageRow[3*i+k];
				iSortTable[2] = bFrontImageRow[3*(i+1)+k];
				iSortTable[3] = bPtrImageRow[3*(i-1)+k];
				iSortTable[4] = bPtrImageRow[3*i+k];
				iSortTable[5] = bPtrImageRow[3*(i+1)+k];
				iSortTable[6] = bBehindImageRow[3*(i-1)+k];
				iSortTable[7] = bBehindImageRow[3*i+k];
				iSortTable[8] = bBehindImageRow[3*(i+1)+k];
				for(int q=0;q<9;q++)
					for(int w=q;w<9;w++)
						if(iSortTable[q] < iSortTable[w])
						{
							Temp = iSortTable[q];
							iSortTable[q] = iSortTable[w];
							iSortTable[w] = Temp;
						}
				bPtrNewImageRow[3*i+k] = iSortTable[4];
		   }
		}
		Image10->Refresh();
		Label7->Caption = "(中值濾波器)" ;
}
//---------------------------------------------------------------------------
//胡椒鹽雜訊
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	  int iRandNum = StrToInt(Edit7 ->Text);
	  iRandNum = ((iImageWidth*iImageHeight)*iRandNum)/100;

	  for(int p=0;p<iRandNum;p++)
	  {
		i = random(iImageWidth);
		j = random(iImageHeight);
		bPtrImageRow = (Byte *)Image10->Picture->Bitmap->ScanLine[j];
		for(k=0; k<3; k++)
					bPtrImageRow[3*i+k] = 255;
	  }
	Image10->Refresh();
}
//---------------------------------------------------------------------------
/*
銳化濾波器(5)
遮罩
0 1 0
1 5 1
0 1 0
*/
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	for(j=1; j<iImageHeight-1; j++)
		{
		int iInputTable[9];
		int iOutput;
		bFrontImageRow =  (Byte *)Image1->Picture->Bitmap->ScanLine[j-1];
		bPtrImageRow =    (Byte *)Image1->Picture->Bitmap->ScanLine[j];
		bBehindImageRow = (Byte *)Image1->Picture->Bitmap->ScanLine[j+1];
		bPtrNewImageRow=  (Byte *)Image10->Picture->Bitmap->ScanLine[j];
		for(i=1; i<iImageWidth-1; i++)
			for(k=0; k<3; k++)
			{
				iOutput =(bFrontImageRow[3*(i-1)+k]*0 + bFrontImageRow[3*i+k]*(-1) +bFrontImageRow[3*(i+1)+k]*0
						 +bPtrImageRow[3*(i-1)+k]*(-1)+ bPtrImageRow[3*i+k]*5      +bPtrImageRow[3*(i+1)+k]*(-1)
						 +bBehindImageRow[3*(i-1)+k]*0+ bBehindImageRow[3*i+k]*(-1)+bBehindImageRow[3*(i+1)+k]*0);
				if(iOutput>255)
					iOutput = 255;
				else if(iOutput<0)
					iOutput = 0;
				else
					bPtrNewImageRow[3*i+k] = iOutput;

			}
		}
		Image10->Refresh();
		Label7->Caption = "(5)" ;
}
//---------------------------------------------------------------------------
/*
銳化濾波器(9)
遮罩
-1 -1 -1
-1  9 -1
-1 -1 -1
*/
void __fastcall TForm1::Button7Click(TObject *Sender)
{
	for(j=1; j<iImageHeight-1; j++)
		{
		int iInputTable[9];
		int iOutput;
		bFrontImageRow =  (Byte *)Image1->Picture->Bitmap->ScanLine[j-1];
		bPtrImageRow =    (Byte *)Image1->Picture->Bitmap->ScanLine[j];
		bBehindImageRow = (Byte *)Image1->Picture->Bitmap->ScanLine[j+1];
		bPtrNewImageRow=  (Byte *)Image10->Picture->Bitmap->ScanLine[j];
		for(i=1; i<iImageWidth-1; i++)
			for(k=0; k<3; k++)
			{
				iOutput =(bFrontImageRow[3*(i-1)+k]*(-1) + bFrontImageRow[3*i+k]*(-1) +bFrontImageRow[3*(i+1)+k]*(-1)
						 +bPtrImageRow[3*(i-1)+k]*(-1)   + bPtrImageRow[3*i+k]*9      +bPtrImageRow[3*(i+1)+k]*(-1)
						 +bBehindImageRow[3*(i-1)+k]*(-1)+ bBehindImageRow[3*i+k]*(-1)+bBehindImageRow[3*(i+1)+k]*(-1));
				if(iOutput>255)
					iOutput = 255;
				else if(iOutput<0)
					iOutput = 0;
				else
					bPtrNewImageRow[3*i+k] = iOutput;

			}
		}
		Image10->Refresh();
		Label7->Caption = "(9)" ;
}
//---------------------------------------------------------------------------

