// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <windows.h>
#include "kgl_string_convertor.h"
#include "kgl_error.h"
#include <exception>
#include <string>
// ---------------------------------------------------------------------------
USEFORM("main_form.cpp", MainForm);

// ---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
    try {
	Application->Initialize();
	Application->MainFormOnTaskBar = true;
	Application->CreateForm(__classid(TMainForm), &MainForm);
	Application->Run();
    }
    catch (Exception &exception) {
	Application->ShowException(&exception);
    }
    catch (kgl::Error e) {
	e.Notify();
    }
    catch (std::exception e) {
	std::wstring excepiton_desc;
	kgl::StringConvertor::ANSItoUTF16LE(e.what(), excepiton_desc);
#ifdef WIN32
	MessageBox(NULL, excepiton_desc.c_str(),
	    L"Unhandled Exception, aborting", MB_OK | MB_ICONERROR);
#endif
    }
    catch (...) {
	try {
	    throw Exception("");
	}
	catch (Exception &exception) {
	    Application->ShowException(&exception);
	}
    }
    return 0;
}
// ---------------------------------------------------------------------------
