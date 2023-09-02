//---------------------------------------------------------------------------

#ifndef main_formH
#define main_formH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "kgl_primitive.h"
#include "kgl_gpu_program.h"
#include "glm/glm.hpp"
#include <Vcl.ExtCtrls.hpp>

#include <Vcl.Menus.hpp>
#include <FireDAC.VCLUI.Memo.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
  __published: // IDE-managed Components
	TPanel *_CodeEditorPanel;
	TMainMenu *_MainMenu;
	TImage *_ShaderView;
	TMenuItem *_MenuFile;
	TMenuItem *_MenuFile_New;
	TMenuItem *_MenuFile_Open;
	TPanel *_ResourcesPanel;
	TFDGUIxFormsMemo *_CodeEditorMemo;
    void __fastcall FormDestroy(TObject* Sender);
    void __fastcall FormPaint(TObject* Sender);
    void __fastcall FormResize(TObject* Sender);
	void __fastcall FormCreate(TObject *Sender);
  private: // User declarations
    bool __fastcall InitializeGL();
    void __fastcall OnResizeGL();
    void __fastcall DrawGL();
    void __fastcall ShutdownGL();
    void __fastcall InitScreenRectangleElement();
    void __fastcall RenderBeatHeart();
    void __fastcall OnIdle(TObject* sender,bool& done);
  private:
    bool _IsGLInitialized = false;
    int xs, ys;
    HDC hdc; // device context
    HGLRC hrc; // rendering context
    kgl::Primitive* rectangle_primitive_ = nullptr;
    kgl::GPUProgram* heart_beat_shader_ = nullptr;
        glm::vec2               screen_resolution_;
    glm::vec2               mouse_input_pos_;
  public: // User declarations
    __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm* MainForm;
//---------------------------------------------------------------------------
#endif




