object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm1'
  ClientHeight = 479
  ClientWidth = 844
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object ThreadWorkLabel: TLabel
    Left = 8
    Top = 448
    Width = 79
    Height = 15
    Caption = #1042#1088#1077#1084#1103' '#1088#1072#1073#1086#1090#1099
  end
  object HistoryDataBase: TVirtualStringTree
    Left = 272
    Top = 8
    Width = 564
    Height = 463
    DefaultNodeHeight = 19
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    ScrollBarOptions.ScrollBars = ssVertical
    TabOrder = 0
    TreeOptions.SelectionOptions = [toFullRowSelect, toSelectNextNodeOnRemoval]
    OnGetText = HistoryDataBaseGetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'Id'
      end
      item
        Position = 1
        Text = 'Origin'
        Width = 112
      end
      item
        Position = 2
        Text = 'Color'
        Width = 137
      end
      item
        Position = 3
        Text = 'Mood'
        Width = 122
      end
      item
        Position = 4
        Text = 'Type'
        Width = 87
      end>
  end
  object WritePlease: TRichEdit
    Left = 8
    Top = 24
    Width = 249
    Height = 113
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    Lines.Strings = (
      'WritePlease')
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 1
    OnClick = WritePleaseClick
  end
  object CheckProv1: TCheckBox
    Left = 8
    Top = 160
    Width = 97
    Height = 17
    Caption = 'CheckProv1'
    TabOrder = 2
  end
  object CheckProv2: TCheckBox
    Left = 160
    Top = 160
    Width = 97
    Height = 17
    Caption = 'CheckProv2'
    TabOrder = 3
  end
  object ThreadButton1: TButton
    Left = 8
    Top = 263
    Width = 249
    Height = 49
    Caption = #1053#1072#1081#1090#1080' '#1074#1089#1077#1093' '#1082#1086#1096#1077#1082' '#1074' '#1087#1088#1080#1102#1090#1077
    TabOrder = 4
    OnClick = ThreadButton1Click
  end
  object ProgressBarThread: TProgressBar
    Left = 8
    Top = 409
    Width = 249
    Height = 25
    TabOrder = 5
  end
  object ThreadButton2: TButton
    Left = 8
    Top = 336
    Width = 249
    Height = 49
    Caption = #1053#1072#1081#1090#1080' '#1090#1086#1083#1100#1082#1086' '#1089' '#1093#1086#1088#1086#1096#1080#1084' '#1085#1072#1089#1090#1088#1086#1077#1085#1080#1077#1084
    TabOrder = 6
    OnClick = ThreadButton2Click
  end
  object NoGraphicsButton: TButton
    Left = 8
    Top = 200
    Width = 249
    Height = 41
    Caption = #1053#1072#1081#1090#1080' '#1082#1086#1096#1077#1082
    TabOrder = 7
    OnClick = NoGraphicsButtonClick
  end
  object OpenError: TOpenDialog
    Left = 792
    Top = 424
  end
end
