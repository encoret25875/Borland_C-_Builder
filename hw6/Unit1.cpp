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
   /*	for(i=0;i<256;i++)
		for(j=0;j<256;j++)
			Image1->Canvas->Pixels[i][j] = (TColor)RGB(i,j,0);    */
	Byte *ptr;
	Image1->Picture->Bitmap->Height = 256;
	Image1->Picture->Bitmap->Width = 256;
	Image1->Picture->Bitmap->PixelFormat = pf24bit;

	for (int i=0; i < 256; i++) {
		ptr = (Byte*) Image1->Picture->Bitmap->ScanLine[i];
		for (j = 0; j < 256; j++) {
			ptr[j*3+2] = (Byte)i;
			ptr[j*3+1] = (Byte)j;
			ptr[j*3] = (Byte)0;
		}

	}

	Image1->Refresh();

	Image2->Picture->Bitmap->Height = 85;
	Image2->Picture->Bitmap->Width = 85;
	Image2->Picture->Bitmap->PixelFormat = pf24bit;
	for (int i=0; i < 85; i++) {
		ptr = (Byte*) Image2->Picture->Bitmap->ScanLine[i];
		for (j = 0; j < 85; j++) {
			ptr[j*3+2] = 0;
			ptr[j*3+1] = 0;
			ptr[j*3]   = 0;
		}

	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
	int color = TrackBar1->Position;
	Byte *ptr;
	Image1->Picture->Bitmap->Height = 256;
	Image1->Picture->Bitmap->Width = 256;
	Image1->Picture->Bitmap->PixelFormat = pf24bit;
	int iY,iU,iV;
	int iR,iG,iB;
	int iC,iD,iE;

	for (int i=0; i < 256; i++)
	{
		ptr = (Byte*) Image1->Picture->Bitmap->ScanLine[i];
		for (j = 0; j < 256; j++)
		{
			if(RadioButton1->Checked)
			{
				ptr[j*3+2] = (Byte)i;
				ptr[j*3+1] = (Byte)j;
				ptr[j*3] = (Byte)color;
			}
			else if(RadioButton2->Checked)
			{
				ptr[j*3+2] = (Byte)color;
				ptr[j*3+1] = (Byte)i;
				ptr[j*3] =   (Byte)j;
			}
			else if(RadioButton3->Checked)
			{
				ptr[j*3+2] = (Byte)i;
				ptr[j*3+1] = (Byte)color;
				ptr[j*3] =   (Byte)j;
			}
			else if(RadioButton4->Checked)
			{
				iY = TrackBar1->Position;
				iU = j;
				iV = i;
				//照公式將修改後的YUV值轉為RGB值
				iC = iY - 16;
				iD = iU - 128;
				iE = iV - 128;

				iR = (( 298 * iC            + 409 * iE + 128) >> 8);
				iG = (( 298 * iC - 100 * iD - 208 * iE + 128) >> 8);
				iB = (( 298 * iC + 516 * iD            + 128) >> 8);

				if(iR>255)
					iR = 255;
				if(iR<0)
					iR = 0;
				if(iG>255)
					iG = 255;
				if(iG<0)
					iG = 0;
				if(iB>255)
					iB = 255;
				if(iB<0)
					iB = 0;
				ptr[j*3+2] = iR;
				ptr[j*3+1] = iG;
				ptr[j*3]   = iB;
			}
		}

	}
	Image1->Refresh();


}
//---------------------------------------------------------------------------


void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Byte *ptr;
	Image2->Picture->Bitmap->Height = 85;
	Image2->Picture->Bitmap->Width = 85;
	Image2->Picture->Bitmap->PixelFormat = pf24bit;
	bPtrImageRow = (Byte *)Image1->Picture->Bitmap->ScanLine[Y];
	int color[3];
	color[0]= bPtrImageRow[3*X+0];
	color[1]= bPtrImageRow[3*X+1];
	color[2]= bPtrImageRow[3*X+2];
	//顯示選擇之顏色
	for(int i=0;i<85;i++)
	{
	ptr = (Byte*) Image2->Picture->Bitmap->ScanLine[i];
		for(int j=0;j<85;j++)
		{
				ptr[j*3+2] = color[2];
				ptr[j*3+1] = color[1];
				ptr[j*3]   = color[0];
		}
	}
	Image2->Refresh();
	Image1->Refresh();
	//---------------------------------------------------
	int iY,iU,iV;
	int iR,iG,iB;
	int iC,iD,iE;

	for(j=0; j<iImageHeight; j++)
		{
		bPtrImageRow = (Byte *)Image4->Picture->Bitmap->ScanLine[j];
		bPtrNewImageRow = (Byte *)Image3->Picture->Bitmap->ScanLine[j];
		for(i=0; i<iImageWidth; i++)
			{
				//取像素點的RGB值
				iR = bPtrImageRow[3*i+2];
				iG = bPtrImageRow[3*i+1];
				iB = bPtrImageRow[3*i+0];
				//YUV分別代表 Y=>亮度 UV=>彩度
				//利用公式從RGB找出Y值
				iY = ( (  66 * iR + 129 * iG +  25 * iB + 128) >> 8) +  16;
				//iU = ( ( -38 * iR -  74 * iG + 112 * iB + 128) >> 8) + 128;
				//iV = ( ( 112 * iR -  94 * iG -  18 * iB + 128) >> 8) + 128;
				//因為像素點的值使用完了，所以直接使用其空間來存放我們要修改成的顏色
				iR = color[2];
				iG = color[1];
				iB = color[0];

				//要做成單色圖片話，我們需要保留他的亮度(Y) 所以不需要做處理
				//iY = ( (  66 * iR + 129 * iG +  25 * iB + 128) >> 8) +  16;
				iU = ( ( -38 * iR -  74 * iG + 112 * iB + 128) >> 8) + 128;
				iV = ( ( 112 * iR -  94 * iG -  18 * iB + 128) >> 8) + 128;
				//照公式將修改後的YUV值轉為RGB值
				iC = iY - 16;
				iD = iU - 128;
				iE = iV - 128;

				iR = (( 298 * iC            + 409 * iE + 128) >> 8);
				iG = (( 298 * iC - 100 * iD - 208 * iE + 128) >> 8);
				iB = (( 298 * iC + 516 * iD            + 128) >> 8);
				//因為YUV轉RGB會超出RGB的有效範圍值，所以需要額外規定範圍以避免超出
				if(iR>255)
					iR = 255;
				if(iR<0)
					iR = 0;
				if(iG>255)
					iG = 255;
				if(iG<0)
					iG = 0;
				if(iB>255)
					iB = 255;
				if(iB<0)
					iB = 0;

				bPtrNewImageRow[3*i+2] = iR;
				bPtrNewImageRow[3*i+1] = iG;
				bPtrNewImageRow[3*i+0] = iB;

			}

		}


	  Image3->Refresh();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
	for (int i=0; i < 256; i++) {
		Byte *ptr = (Byte*) Image1->Picture->Bitmap->ScanLine[i];
		for (j = 0; j < 256; j++) {
			ptr[j*3+2] = i;
			ptr[j*3+1] = j;
			ptr[j*3] = 0;
		}
	}
	Image1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
	for (int i=0; i < 256; i++) {
		Byte *ptr = (Byte*) Image1->Picture->Bitmap->ScanLine[i];
		for (j = 0; j < 256; j++) {
				ptr[j*3+2] = 0;
				ptr[j*3+1] = i;
				ptr[j*3]   = j;
		}
	}
	Image1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
	for (int i=0; i < 256; i++) {
		Byte *ptr = (Byte*) Image1->Picture->Bitmap->ScanLine[i];
		for (j = 0; j < 256; j++) {
				ptr[j*3+2] = i;
				ptr[j*3+1] = 0;
				ptr[j*3] =   j;
		}
	}
	Image1->Refresh();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
	int iY,iU,iV;
	int iR,iG,iB;
	int iC,iD,iE;
	for (int i=0; i < 256; i++)
	{
		Byte *ptr = (Byte*) Image1->Picture->Bitmap->ScanLine[i];
		for (j = 0; j < 256; j++)
		{
				iY = TrackBar1->Position;
				iU = j;
				iV = i;
				//照公式將修改後的YUV值轉為RGB值
				iC = iY - 16;
				iD = iU - 128;
				iE = iV - 128;

				iR = (( 298 * iC            + 409 * iE + 128) >> 8);
				iG = (( 298 * iC - 100 * iD - 208 * iE + 128) >> 8);
				iB = (( 298 * iC + 516 * iD            + 128) >> 8);

				if(iR>255)
					iR = 255;
				if(iR<0)
					iR = 0;
				if(iG>255)
					iG = 255;
				if(iG<0)
					iG = 0;
				if(iB>255)
					iB = 255;
				if(iB<0)
					iB = 0;
				ptr[j*3+2] = iR;
				ptr[j*3+1] = iG;
				ptr[j*3]   = iB;
		}
	}
	Image1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::file1Click(TObject *Sender)
{
	if( OpenPictureDialog1->Execute() )
		{Image3->Picture->LoadFromFile(OpenPictureDialog1->FileName);
		 Image4->Picture->LoadFromFile(OpenPictureDialog1->FileName);}
	iImageWidth  = Image3->Picture->Width;
	iImageHeight = Image3->Picture->Height;
}
//---------------------------------------------------------------------------





