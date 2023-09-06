object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'Shader Joy'
  ClientHeight = 770
  ClientWidth = 1265
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
    Height = 655
    Align = alLeft
    TabOrder = 0
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
    end
  end
  object _ResourcesPanel: TPanel
    Left = 0
    Top = 655
    Width = 1265
    Height = 115
    Align = alBottom
    TabOrder = 1
  end
  object _ShaderView: TPanel
    Left = 455
    Top = 0
    Width = 810
    Height = 655
    Align = alClient
    TabOrder = 2
    OnMouseUp = _ShaderViewMouseUp
    ExplicitLeft = 461
    ExplicitWidth = 808
    ExplicitHeight = 656
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
