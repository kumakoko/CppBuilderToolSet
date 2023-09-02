//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_form.h"
#include "glad.h"
#include "glad_wgl.h"
#include "glm/glm.hpp"
#include "kgl_defines.h"
#include "boost/format.hpp"
#include <windows.h>
#include <ctime>

#ifndef GLM_FORCE_SSE2
    #define GLM_FORCE_SSE2
#endif

#ifndef GLM_FORCE_INLINE
    #define GLM_FORCE_INLINE
#endif

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

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
}

__fastcall bool TMainForm::InitializeGL()
{
    if (_IsGLInitialized)
        return true;

    //hdc = GetDC(this->Handle); // get device context
    hdc = GetDC(_ShaderView->Handle);

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

    InitScreenRectangleElement();

    _IsGLInitialized = true;
    return true;
}
//---------------------------------------------------------------------------

__fastcall void TMainForm::OnResizeGL()
{
    //xs = ClientWidth;
    //ys = ClientHeight;
    xs = _ShaderView->ClientWidth;
    ys = _ShaderView->ClientHeight;

    screen_resolution_.x = static_cast<float>(xs);
    screen_resolution_.y = static_cast<float>(ys);

    boost::format fmt("x = %d y = %d");
    fmt % xs % ys;

    OutputDebugStringA(fmt.str().c_str());

    if (xs <= 0)
        xs = 1; // Prevent a divide by zero
    if (ys <= 0)
        ys = 1;
    if (!_IsGLInitialized)
        return;

    glViewport(0, 0, xs, ys);

    DrawGL();
}

__fastcall void TMainForm::DrawGL()
{
    glClearColor(0.35f, 0.53f, 0.7f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    RenderBeatHeart();
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
    KGL_SAFE_DELETE(heart_beat_shader_);
    KGL_SAFE_DELETE(rectangle_primitive_);
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

void __fastcall TMainForm::InitScreenRectangleElement()
{
    GLfloat vertices[] = {
        // 位置          // 颜色            //纹理坐标1 //纹理坐标2 //纹理坐标3 //纹理坐标4
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, // 右上角
        1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, // 右下角
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, // 左下角
        -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f //左上角
    };

    GLuint indices[] = { 0, 1, 3, 1, 2, 3 };

    kgl::VertexAttribute va_position;
    va_position.index = 0;
    va_position.normalized = GL_FALSE;
    va_position.type = GL_FLOAT;
    va_position.size = 3; // 一个“顶点位置”的属性由3个分量组成
    va_position.stride = 14 * sizeof(GLfloat); // 每个顶点的步长
    va_position.pointer = nullptr;

    kgl::VertexAttribute va_color;
    va_color.index = 1;
    va_color.normalized = GL_FALSE;
    va_color.type = GL_FLOAT;
    va_color.size = 3; // 一个“顶点颜色”的属性由3个分量组成
    va_color.stride = 14 * sizeof(GLfloat); //每个顶点的步长
    va_color.pointer = reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat));

    kgl::VertexAttribute va_texture_coord_1;
    va_texture_coord_1.index = 2;
    va_texture_coord_1.normalized = GL_FALSE;
    va_texture_coord_1.type = GL_FLOAT;
    va_texture_coord_1.size = 2; // 一个“顶点坐标”的属性由3个分量组成
    va_texture_coord_1.stride = 14 * sizeof(GLfloat); // 每个顶点的步长
    va_texture_coord_1.pointer = reinterpret_cast<GLvoid*>(
        6 * sizeof(GLfloat)); // 纹理坐标数据在字段中的起始指针处

    kgl::VertexAttribute va_texture_coord_2;
    va_texture_coord_2.index = 3;
    va_texture_coord_2.normalized = GL_FALSE;
    va_texture_coord_2.type = GL_FLOAT;
    va_texture_coord_2.size = 2; // 一个“顶点坐标”的属性由3个分量组成
    va_texture_coord_2.stride = 14 * sizeof(GLfloat); // 每个顶点的步长
    va_texture_coord_2.pointer = reinterpret_cast<GLvoid*>(
        8 * sizeof(GLfloat)); // 纹理坐标数据在字段中的起始指针处

    kgl::VertexAttribute va_texture_coord_3;
    va_texture_coord_3.index = 4;
    va_texture_coord_3.normalized = GL_FALSE;
    va_texture_coord_3.type = GL_FLOAT;
    va_texture_coord_3.size = 2; // 一个“顶点坐标”的属性由3个分量组成
    va_texture_coord_3.stride = 14 * sizeof(GLfloat); // 每个顶点的步长
    va_texture_coord_3.pointer = reinterpret_cast<GLvoid*>(
        10 * sizeof(GLfloat)); // 纹理坐标数据在字段中的起始指针处

    kgl::VertexAttribute va_texture_coord_4;
    va_texture_coord_4.index = 5;
    va_texture_coord_4.normalized = GL_FALSE;
    va_texture_coord_4.type = GL_FLOAT;
    va_texture_coord_4.size = 2; // 一个“顶点坐标”的属性由3个分量组成
    va_texture_coord_4.stride = 14 * sizeof(GLfloat); // 每个顶点的步长
    va_texture_coord_4.pointer = reinterpret_cast<GLvoid*>(
        12 * sizeof(GLfloat)); // 纹理坐标数据在字段中的起始指针处

    std::vector<kgl::VertexAttribute> vtx_attri_array;
    vtx_attri_array.push_back(va_position);
    vtx_attri_array.push_back(va_color);
    vtx_attri_array.push_back(va_texture_coord_1);
    vtx_attri_array.push_back(va_texture_coord_2);
    vtx_attri_array.push_back(va_texture_coord_3);
    vtx_attri_array.push_back(va_texture_coord_4);

    rectangle_primitive_ = new kgl::Primitive;
    rectangle_primitive_->CreateIndexed(GL_TRIANGLES, vertices,
        sizeof(vertices), GL_STATIC_DRAW, kgl::Primitive::UINT32, indices,
        sizeof(indices), GL_STATIC_DRAW, vtx_attri_array);

    heart_beat_shader_ = new kgl::GPUProgram;
    heart_beat_shader_->CreateFromFile(
        "pixel_magic_vs.glsl", "sea_fs.glsl", nullptr);
}

void __fastcall TMainForm::RenderBeatHeart()
{
    double curTime = static_cast<double>(std::clock()) / CLOCKS_PER_SEC;
    heart_beat_shader_->Use();
    heart_beat_shader_->ApplyFloat(static_cast<float>(curTime), "global_time");
    heart_beat_shader_->ApplyVector2(
        glm::value_ptr(screen_resolution_), "screen_resolution");
    heart_beat_shader_->ApplyVector2(
		glm::value_ptr(mouse_input_pos_), "mouse_position");
	rectangle_primitive_->DrawIndexed();
}

void __fastcall TMainForm::OnIdle(TObject* sender, bool &done)
{
    if (_IsGLInitialized) {
        DrawGL();
    }
}

void __fastcall TMainForm::FormCreate(TObject* Sender)
{
    Application->OnIdle = this->OnIdle;

    InitializeGL();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::_ShaderViewMouseUp(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    mouse_input_pos_.x = static_cast<float>(X);
    mouse_input_pos_.y = static_cast<float>(Y);
}
//---------------------------------------------------------------------------

