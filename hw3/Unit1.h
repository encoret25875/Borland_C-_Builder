//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TOpenPictureDialog *OpenPictureDialog1;
	TMainMenu *MainMenu1;
	TMenuItem *File;
	TMenuItem *open;
	TMenuItem *image2;
	TMenuItem *Image3;
	TMenuItem *Adjustments1;
	TMenuItem *Inverse1;
	TImage *Image4;
	TBitBtn *BitBtn1;
	TColorDialog *ColorDialog1;
	TImage *Image5;
	TImage *Image6;
	TBitBtn *BitBtn2;
	TPageControl *TPageControl1;
	TTabSheet *TTabSheetRed;
	TTabSheet *TTabSheetGreen;
	TTabSheet *TTabSheetBlue;
	TScrollBox *ScrollBox1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TScrollBox *ScrollBox2;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TMenuItem *N1;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit3;
	TEdit *Edit4;
	TButton *Button1;
	TTrackBar *TrackBar1;
	TTrackBar *TrackBar2;
	TTrackBar *TrackBar3;
	TTrackBar *TrackBar4;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *Edit5;
	TEdit *Edit6;
	TBitBtn *BitBtn3;
	TImage *Image8;
	TImage *Image7;
	TImage *Image9;
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall image2Click(TObject *Sender);
	void __fastcall Inverse1Click(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall TrackBar2Change(TObject *Sender);
	void __fastcall TrackBar3Change(TObject *Sender);
	void __fastcall TrackBar4Change(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Edit2Change(TObject *Sender);
	void __fastcall Edit3Change(TObject *Sender);
	void __fastcall Edit4Change(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall Image8MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);

private:	// User declarations
	int i,j,k;
	int iImageWidth, iImageHeight;
	BYTE *bPtrImageRow;
	BYTE *bPtrNewImageRow;
	int iHB[256],iHG[256],iHR[256];                 //統計用
	int iMax,iHRMax,iHGMax,iHBMax;					//統計用
	int iInputMax,iInputMin,iOutputMax,iOutputMin;	//調整色階用
	double dX,dY,dA,dB,dS,dT;                       //調整曲線用
	double dCurveTable[256];
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
