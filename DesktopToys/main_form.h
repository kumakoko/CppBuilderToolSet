//---------------------------------------------------------------------------

#ifndef main_formH
#define main_formH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ColorGrd.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "screen_canvas.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
  __published: // IDE-managed Components
    TColorGrid* _ColorGrid;
    TImage* _Image;
    TPanel *_RightPanel;

    void __fastcall _ImageMouseMove(
        TObject* Sender, TShiftState Shift, int X, int Y);
    void __fastcall FormActivate(TObject* Sender);
    void __fastcall _ImageMouseUp(
        TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall _ImageMouseDown(
        TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall FormCreate(TObject* Sender);
    void __fastcall FormClose(TObject* Sender, TCloseAction &Action);
    void __fastcall _ColorGridChange(TObject* Sender);
    void __fastcall _RightPanelResize(TObject *Sender);
  private: // User declarations
    bool FDrawing = false;
    TPoint FCursorPos;
    TScreenCanvas* _ScreenCanvas = nullptr;
    Graphics::TBitmap* FCursorBits = nullptr;
    Graphics::TBitmap* FDesktopBits = nullptr;
    void __fastcall GrabScreenImage();
    void __fastcall WMSetFocus(TWMSetFocus &Message);
    void __fastcall WMKillFocus(TWMKillFocus &Message);
  public: // User declarations
    __fastcall TMainForm(TComponent* Owner);
    BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_SETFOCUS, TWMSetFocus, WMSetFocus);
        VCL_MESSAGE_HANDLER(WM_KILLFOCUS, TWMKillFocus, WMKillFocus);
    END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm* MainForm;
//---------------------------------------------------------------------------
#endif

