object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 488
  ClientWidth = 732
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
    Left = 26
    Top = 58
    Width = 256
    Height = 256
    OnMouseDown = Image1MouseDown
  end
  object Image2: TImage
    Left = 188
    Top = 337
    Width = 85
    Height = 80
  end
  object Label1: TLabel
    Left = 188
    Top = 318
    Width = 64
    Height = 13
    Caption = #36984#25799#20043#38991#33394':'
  end
  object Label2: TLabel
    Left = 8
    Top = 176
    Width = 12
    Height = 23
    Caption = 'U'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 147
    Top = 29
    Width = 11
    Height = 23
    Caption = 'V'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Image4: TImage
    Left = 493
    Top = 58
    Width = 105
    Height = 105
  end
  object Label4: TLabel
    Left = 15
    Top = 418
    Width = 11
    Height = 23
    Caption = 'Y'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object TrackBar1: TTrackBar
    Left = 32
    Top = 418
    Width = 150
    Height = 45
    Max = 255
    TabOrder = 0
    OnChange = TrackBar1Change
  end
  object RadioButton1: TRadioButton
    Left = 40
    Top = 320
    Width = 113
    Height = 17
    Caption = 'RG'#24179#38754
    Checked = True
    TabOrder = 1
    TabStop = True
    OnClick = RadioButton1Click
  end
  object RadioButton2: TRadioButton
    Left = 40
    Top = 343
    Width = 113
    Height = 17
    Caption = 'GB'#24179#38754
    TabOrder = 2
    OnClick = RadioButton2Click
  end
  object RadioButton3: TRadioButton
    Left = 40
    Top = 366
    Width = 113
    Height = 17
    Caption = 'RB'#24179#38754
    TabOrder = 3
    OnClick = RadioButton3Click
  end
  object ScrollBox1: TScrollBox
    Left = 288
    Top = 50
    Width = 372
    Height = 369
    TabOrder = 4
    object Image3: TImage
      Left = 3
      Top = 3
      Width = 105
      Height = 105
      AutoSize = True
    end
  end
  object RadioButton4: TRadioButton
    Left = 40
    Top = 389
    Width = 113
    Height = 17
    Caption = 'UV'#24179#38754
    TabOrder = 5
    OnClick = RadioButton4Click
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Left = 16
    Top = 8
  end
  object MainMenu1: TMainMenu
    Left = 96
    Top = 8
    object file1: TMenuItem
      Caption = 'open'
      OnClick = file1Click
    end
  end
end
