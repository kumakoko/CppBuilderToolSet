//---------------------------------------------------------------------------

#ifndef screen_canvasH
#define screen_canvasH
//---------------------------------------------------------------------------
#include <Vcl.Graphics.hpp>
class TScreenCanvas : public TCanvas
{
  private:
    void __fastcall FreeContext();
  protected:
    virtual void __fastcall CreateHandle(void);
  public:
    __fastcall virtual ~TScreenCanvas();
};
#endif

