object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 537
  ClientWidth = 918
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesktopCenter
  TextHeight = 15
  object InfoLabel: TLabel
    Left = 8
    Top = 247
    Width = 3
    Height = 15
  end
  object OpenDB: TButton
    Left = 8
    Top = 276
    Width = 177
    Height = 57
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1041#1044
    TabOrder = 0
    OnClick = OpenDBClick
  end
  object HistoryDataBase: TVirtualStringTree
    Left = 8
    Top = 8
    Width = 884
    Height = 233
    DefaultNodeHeight = 19
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 1
    TreeOptions.SelectionOptions = [toFullRowSelect, toSelectNextNodeOnRemoval]
    OnAddToSelection = HistoryDataBaseAddToSelection
    OnGetText = HistoryDataBaseGetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Options = [coAllowClick, coDraggable, coEnabled, coParentBidiMode, coParentColor, coResizable, coShowDropMark, coVisible, coAutoSpring, coSmartResize, coWrapCaption, coUseCaptionAlignment, coEditable, coStyleColor]
        Position = 0
        Text = 'Id'
      end
      item
        Position = 1
        Text = 'Url'
        Width = 150
      end
      item
        Position = 2
        Text = 'Info'
        Width = 200
      end>
  end
  object DeleteStrock: TButton
    Left = 472
    Top = 276
    Width = 193
    Height = 57
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1089#1090#1088#1086#1082#1091
    TabOrder = 2
    OnClick = DeleteStrockClick
  end
  object DeleteDataBase: TButton
    Left = 707
    Top = 276
    Width = 185
    Height = 57
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1080#1089#1090#1086#1088#1080#1102' '#1041#1044
    TabOrder = 3
    OnClick = DeleteDataBaseClick
  end
  object FileNameEdit: TEdit
    Left = 8
    Top = 481
    Width = 884
    Height = 23
    TabOrder = 4
    Text = #1055#1091#1090#1100' '#1082' '#1041#1044
  end
  object FillNode: TButton
    Left = 232
    Top = 275
    Width = 177
    Height = 58
    Caption = #1047#1072#1087#1086#1083#1085#1080#1090#1100' '#1089#1090#1088#1091#1082#1090#1091#1088#1091
    TabOrder = 5
    OnClick = FillNodeClick
  end
  object Tutorial: TRichEdit
    Left = 8
    Top = 339
    Width = 884
    Height = 136
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    Lines.Strings = (
      'Tutorial')
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 6
    OnClick = TutorialChange
  end
  object OpenDataBaseDialog: TOpenDialog
    Left = 872
    Top = 504
  end
end
