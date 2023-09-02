object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'Shader Joy'
  ClientHeight = 771
  ClientWidth = 1269
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = _MainMenu
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnPaint = FormPaint
  OnResize = FormResize
  TextHeight = 15
  object _CodeEditorPanel: TPanel
    Left = 0
    Top = 0
    Width = 455
    Height = 656
    Align = alLeft
    TabOrder = 0
    ExplicitHeight = 655
    object _CodeEditorMemo: TFDGUIxFormsMemo
      Left = 1
      Top = 1
      Width = 453
      Height = 654
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      Lines.Strings = (
        '_CodeEditorMemo')
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 0
      WordWrap = False
      ExplicitHeight = 653
    end
  end
  object _ResourcesPanel: TPanel
    Left = 0
    Top = 656
    Width = 1269
    Height = 115
    Align = alBottom
    TabOrder = 1
    ExplicitTop = 655
    ExplicitWidth = 1265
  end
  object _ShaderView: TPanel
    Left = 455
    Top = 0
    Width = 814
    Height = 656
    Align = alClient
    TabOrder = 2
    OnMouseUp = _ShaderViewMouseUp
    ExplicitLeft = 461
    ExplicitWidth = 808
  end
  object _MainMenu: TMainMenu
    Left = 272
    Top = 664
    object _MenuFile: TMenuItem
      Caption = 'File'
      object _MenuFile_New: TMenuItem
        Caption = 'New'
      end
      object _MenuFile_Open: TMenuItem
        Caption = 'Open'
      end
    end
  end
end
