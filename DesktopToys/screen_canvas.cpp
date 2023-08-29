//---------------------------------------------------------------------------

#pragma hdrstop

#include "screen_canvas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TScreenCanvas::~TScreenCanvas()
{
    FreeContext();
}

void __fastcall TScreenCanvas::FreeContext()
{
    ReleaseDC(0, Handle);
    Handle = 0;
}

void __fastcall TScreenCanvas::CreateHandle(void)
{
    Handle = GetDC(0);
}

