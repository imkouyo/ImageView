object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Form2'
  ClientHeight = 726
  ClientWidth = 939
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
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 939
    Height = 726
    ActivePage = TabSheet5
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Histogram'
      ExplicitLeft = 8
      ExplicitTop = 28
      ExplicitWidth = 966
      object Image1: TImage
        Left = 24
        Top = 40
        Width = 489
        Height = 449
        Center = True
        Stretch = True
      end
      object Image2: TImage
        Left = 584
        Top = 40
        Width = 256
        Height = 120
      end
      object Image3: TImage
        Left = 584
        Top = 200
        Width = 256
        Height = 120
      end
      object Image4: TImage
        Left = 584
        Top = 369
        Width = 256
        Height = 120
      end
      object Button1: TButton
        Left = 584
        Top = 520
        Width = 256
        Height = 41
        Caption = 'Image Histogram'
        TabOrder = 0
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 584
        Top = 584
        Width = 256
        Height = 41
        Caption = 'Histogram Equalization'
        TabOrder = 1
        OnClick = Button2Click
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Level Curve'
      ImageIndex = 1
      ExplicitLeft = 8
      ExplicitTop = 28
      object Image5: TImage
        Left = 72
        Top = 88
        Width = 369
        Height = 369
        Center = True
        Stretch = True
      end
      object Image6: TImage
        Left = 504
        Top = 88
        Width = 256
        Height = 256
        OnMouseDown = Image6MouseDown
      end
      object Label1: TLabel
        Left = 56
        Top = 488
        Width = 49
        Height = 13
        Caption = 'Input Max'
      end
      object Label2: TLabel
        Left = 269
        Top = 488
        Width = 45
        Height = 13
        Caption = 'Input Min'
      end
      object Label3: TLabel
        Left = 56
        Top = 536
        Width = 57
        Height = 13
        Caption = 'Output Max'
      end
      object Label4: TLabel
        Left = 261
        Top = 536
        Width = 53
        Height = 13
        Caption = 'Output Min'
      end
      object Button3: TButton
        Left = 128
        Top = 580
        Width = 313
        Height = 25
        Caption = 'Level'
        TabOrder = 0
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 504
        Top = 580
        Width = 297
        Height = 25
        Caption = 'Curve'
        TabOrder = 1
        OnClick = Button4Click
      end
      object Edit1: TEdit
        Left = 128
        Top = 488
        Width = 121
        Height = 21
        TabOrder = 2
        Text = 'Edit1'
      end
      object Edit2: TEdit
        Left = 320
        Top = 488
        Width = 121
        Height = 21
        TabOrder = 3
        Text = 'Edit2'
      end
      object Edit3: TEdit
        Left = 128
        Top = 534
        Width = 121
        Height = 21
        TabOrder = 4
        Text = 'Edit3'
      end
      object Edit4: TEdit
        Left = 320
        Top = 534
        Width = 121
        Height = 21
        TabOrder = 5
        Text = 'Edit4'
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Spatial Filtering'
      ImageIndex = 2
      ExplicitWidth = 966
      object Image7: TImage
        Left = 48
        Top = 80
        Width = 449
        Height = 465
        Center = True
        Stretch = True
      end
      object Button7: TButton
        Left = 640
        Top = 352
        Width = 137
        Height = 65
        Caption = 'midian filter'
        TabOrder = 0
        OnClick = Button7Click
      end
      object Button6: TButton
        Left = 640
        Top = 264
        Width = 137
        Height = 65
        Caption = 'pepper-and-salt noise'
        TabOrder = 1
        OnClick = Button6Click
      end
      object Button5: TButton
        Left = 640
        Top = 184
        Width = 137
        Height = 65
        Caption = 'Smoothing filter'
        TabOrder = 2
        OnClick = Button5Click
      end
      object Memo1: TMemo
        Left = 624
        Top = 536
        Width = 185
        Height = 89
        Lines.Strings = (
          'Memo1')
        TabOrder = 3
      end
      object Button8: TButton
        Left = 640
        Top = 448
        Width = 137
        Height = 65
        Caption = 'sharping filter'
        TabOrder = 4
        OnClick = Button8Click
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Color Models'
      ImageIndex = 3
      ExplicitLeft = 0
      ExplicitTop = 28
      object Image8: TImage
        Left = 56
        Top = 40
        Width = 256
        Height = 256
      end
      object Image9: TImage
        Left = 633
        Top = 40
        Width = 256
        Height = 256
      end
      object Image10: TImage
        Left = 56
        Top = 400
        Width = 256
        Height = 256
      end
      object Image11: TImage
        Left = 633
        Top = 400
        Width = 256
        Height = 256
      end
      object TrackBar1: TTrackBar
        Left = 336
        Top = 336
        Width = 256
        Height = 45
        TabOrder = 0
        OnChange = TrackBar1Change
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Yuv image'
      ImageIndex = 4
      ExplicitLeft = 8
      ExplicitTop = 28
      object Image12: TImage
        Left = 3
        Top = 64
        Width = 590
        Height = 569
        Center = True
        Stretch = True
      end
      object Image13: TImage
        Left = 624
        Top = 64
        Width = 256
        Height = 256
        OnMouseDown = Image13MouseDown
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 24
    Top = 672
    object File1: TMenuItem
      Caption = 'File...'
      object OpenImage1: TMenuItem
        Caption = 'Open Image'
        OnClick = OpenImage1Click
      end
    end
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Left = 76
    Top = 672
  end
end
