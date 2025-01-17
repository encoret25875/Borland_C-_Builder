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
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1Click(TObject *Sender)
{
	 OpenPictureDialog1->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::image2Click(TObject *Sender)
{
	if( OpenPictureDialog1->Execute() )
		Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
	iImageWidth = Image1->Picture->Width;
	iImageHeight = Image1->Picture->Height;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Inverse1Click(TObject *Sender)
{
	for(j=0; j<iImageHeight; j++)
		{
		bPtrImageRow = (Byte *)Image1->Picture->Bitmap->ScanLine[j];
		for(i=0; i<iImageWidth; i++)
			for(k=0; k<3; k++)
				bPtrImageRow[3*i+k] = 255 - bPtrImageRow[3*i+k];
		}
	Image1->Refresh();
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
		bPtrImageRow = (Byte *)Image1->Picture->Bitmap->ScanLine[j];
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
		bPtrImageRow = (Byte *)Image1->Picture->Bitmap->ScanLine[j];
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



