//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm* MainForm;


const int DOT_SIZE = 20;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TMainForm::_ImageMouseMove(
    TObject* Sender, TShiftState Shift, int X, int Y)
{
    TPoint Pt;
    TRect R;

    GetCursorPos(&Pt);

    if (Pt.x != FCursorPos.x || Pt.y != FCursorPos.y) {
        R = Rect(0, 0, FCursorBits->Width, FCursorBits->Height);
        OffsetRect(&R, FCursorPos.x, FCursorPos.y);
        _Image->Canvas->CopyRect(R, FDesktopBits->Canvas, R);

        if (FDrawing) {
            R = Rect(Pt.x, Pt.y, Pt.x + DOT_SIZE, Pt.y + DOT_SIZE);
            FDesktopBits->Canvas->Ellipse(
                Pt.x, Pt.y, Pt.x + DOT_SIZE, Pt.y + DOT_SIZE);
            _Image->Canvas->CopyRect(R, FDesktopBits->Canvas, R);
        }

        _Image->Canvas->Draw(Pt.x, Pt.y, FCursorBits);

        FCursorPos = Pt;
    }
}

void __fastcall TMainForm::FormActivate(TObject* Sender)
{
    GrabScreenImage();
}

// 进入移动状态
void __fastcall TMainForm::_ImageMouseUp(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    FDrawing = false;
}

// 进入涂鸦状态
void __fastcall TMainForm::_ImageMouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    FDrawing = true;
}

void __fastcall TMainForm::GrabScreenImage()
{
    FDesktopBits->Width = ClientWidth;
    FDesktopBits->Height = ClientHeight;

    TScreenCanvas* SC = new TScreenCanvas;
    try {
        BitBlt(FDesktopBits->Canvas->Handle, 0, 0, ClientWidth, ClientHeight,
            SC->Handle, 0, 0, SRCCOPY);

        _Image->Picture->Bitmap->Assign(FDesktopBits);
    } __finally
    {
        delete SC;
    }
}

void __fastcall TMainForm::FormCreate(TObject* Sender)
{
    FDrawing = false;

    FCursorBits = new Graphics::TBitmap;
    FCursorBits->LoadFromFile("hammer.bmp");
    FCursorBits->Transparent = true;
    FCursorBits->TransparentMode = tmAuto;

    FDesktopBits = new Graphics::TBitmap;

    _ColorGrid->ForegroundIndex = 9; //
    _ColorGridChange(_ColorGrid);
}

void __fastcall TMainForm::FormClose(TObject* Sender, TCloseAction &Action)
{
    delete FCursorBits;
    delete FDesktopBits;
}

void __fastcall TMainForm::WMSetFocus(TWMSetFocus &Message)
{
    ShowCursor(false);
}

void __fastcall TMainForm::WMKillFocus(TWMKillFocus &Message)
{
    ShowCursor(true);
}

void __fastcall TMainForm::_ColorGridChange(TObject* Sender)
{
    _Image->Canvas->Brush->Color = _ColorGrid->ForegroundColor;
    FDesktopBits->Canvas->Brush->Color = _ColorGrid->ForegroundColor;
    FDesktopBits->Canvas->Pen->Color = _ColorGrid->ForegroundColor;
}

void __fastcall TMainForm::_RightPanelResize(TObject *Sender)
{
  _ColorGrid->Width = _RightPanel->ClientWidth;
  _ColorGrid->Height = _RightPanel->ClientHeight;
}
//---------------------------------------------------------------------------

