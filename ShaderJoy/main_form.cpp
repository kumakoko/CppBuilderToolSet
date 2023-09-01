//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_form.h"
#include "glad.h"
#include "glad_wgl.h"
#include "glm/glm.hpp"
#include <windows.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm* MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner)
{
    _IsGLInitialized = false;
    hdc = NULL;
    hrc = NULL;
    InitializeGL();
}

__fastcall bool TMainForm::InitializeGL()
{
    if (_IsGLInitialized)
        return true;

    hdc = GetDC(this->Handle); // get device context
    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(pfd)); // set the pixel format for the DC
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;
    SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);
    hrc = wglCreateContext(hdc); // create current rendering context
    if (hrc == NULL) {
        ShowMessage("Could not initialize OpenGL Rendering context !!!");
        _IsGLInitialized = false;
        return false;
    }
    if (wglMakeCurrent(hdc, hrc) == false) {
        ShowMessage("Could not make current OpenGL Rendering context !!!");
        wglDeleteContext(hrc); // destroy rendering context
        _IsGLInitialized = false;
        return false;
    }

    gladLoadGL();

    OnResizeGL();
    glEnable(GL_DEPTH_TEST); // Zbuf
    glDisable(GL_CULL_FACE); // vynechavaj odvratene steny
    glDisable(GL_TEXTURE_2D); // pouzivaj textury, farbu pouzivaj z textury
    glDisable(GL_BLEND); // priehladnost
    glShadeModel(GL_SMOOTH); // gourard shading
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // background color
    _IsGLInitialized = true;
    return true;
}
//---------------------------------------------------------------------------

__fastcall void TMainForm::OnResizeGL()
{
    xs = ClientWidth;
    ys = ClientHeight;

    if (xs <= 0)
        xs = 1; // Prevent a divide by zero
    if (ys <= 0)
        ys = 1;
    if (!_IsGLInitialized)
        return;

    //glViewport(0, 0, xs, ys); // Set Viewport to window dimensions
    /*
    glMatrixMode(GL_PROJECTION); // operacie s projekcnou maticou
    glLoadIdentity(); // jednotkova matica projekcie
    gluPerspective(30, float(xs) / float(ys), 0.1,
        100.0); // matica=perspektiva,120 stupnov premieta z viewsize do 0.1
    glMatrixMode(GL_TEXTURE); // operacie s texturovou maticou
    glLoadIdentity(); // jednotkova matica textury
    glMatrixMode(GL_MODELVIEW); // operacie s modelovou maticou
    glLoadIdentity(); // jednotkova matica modelu (objektu)
    */
    DrawGL();
}

__fastcall void TMainForm::DrawGL()
{
    glClearColor(0.35f, 0.53f, 0.7f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SwapBuffers(hdc);
}

__fastcall void TMainForm::ShutdownGL()
{
    if (!_IsGLInitialized)
        return;
    wglMakeCurrent(NULL, NULL); // release current rendering context
    wglDeleteContext(hrc); // destroy rendering context
    _IsGLInitialized = 0;
}

void __fastcall TMainForm::FormDestroy(TObject* Sender)
{
    ShutdownGL();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormPaint(TObject* Sender)
{
    DrawGL();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormResize(TObject* Sender)
{
    OnResizeGL();
}
//---------------------------------------------------------------------------


