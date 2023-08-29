object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'MainForm'
  ClientHeight = 480
  ClientWidth = 640
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  WindowState = wsMaximized
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  TextHeight = 15
  object _Image: TImage
    Left = 0
    Top = 0
    Width = 551
    Height = 480
    Align = alClient
    OnMouseDown = _ImageMouseDown
    OnMouseMove = _ImageMouseMove
    OnMouseUp = _ImageMouseUp
    ExplicitLeft = 8
    ExplicitTop = 8
    ExplicitWidth = 530
    ExplicitHeight = 426
  end
  object _RightPanel: TPanel
    Left = 551
    Top = 0
    Width = 89
    Height = 480
    Align = alRight
    TabOrder = 0
    OnResize = _RightPanelResize
    ExplicitLeft = 544
    ExplicitTop = 8
    ExplicitHeight = 426
    object _ColorGrid: TColorGrid
      Left = 13
      Top = -6
      Width = 76
      Height = 432
      GridOrdering = go1x16
      TabOrder = 0
      OnChange = _ColorGridChange
    end
  end
end
