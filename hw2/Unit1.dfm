object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 629
  ClientWidth = 988
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 8
    Top = 8
    Width = 105
    Height = 105
    AutoSize = True
    OnClick = Image1Click
  end
  object Image4: TImage
    Left = 729
    Top = 8
    Width = 255
    Height = 255
  end
  object Image5: TImage
    Left = 729
    Top = 269
    Width = 255
    Height = 255
  end
  object Image6: TImage
    Left = 468
    Top = 271
    Width = 255
    Height = 255
  end
  object BitBtn1: TBitBtn
    Left = 480
    Top = 39
    Width = 75
    Height = 25
    Caption = 'pdf'
    TabOrder = 0
    OnClick = BitBtn1Click
  end
  object BitBtn2: TBitBtn
    Left = 480
    Top = 8
    Width = 75
    Height = 25
    Caption = 'cdf'
    TabOrder = 1
    OnClick = BitBtn2Click
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Left = 600
    Top = 16
  end
  object MainMenu1: TMainMenu
    Left = 592
    Top = 88
    object File: TMenuItem
      Caption = 'File'
      object open: TMenuItem
        Caption = 'open'
        object image2: TMenuItem
          Caption = 'image'
          OnClick = image2Click
        end
      end
    end
    object Image3: TMenuItem
      Caption = 'Image'
      object Adjustments1: TMenuItem
        Caption = 'Adjustments'
        object Inverse1: TMenuItem
          Caption = 'Inverse'
          OnClick = Inverse1Click
        end
      end
    end
  end
  object ColorDialog1: TColorDialog
    Left = 584
    Top = 168
  end
end
