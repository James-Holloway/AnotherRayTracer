#include <iostream>
#include <wx/wx.h>
#include "anothermainwindow.h"

class AnotherApp : public wxApp
{
public:
    bool OnInit() override;
    virtual bool OnExceptionInMainLoop() override;
};

wxIMPLEMENT_APP(AnotherApp);

bool AnotherApp::OnInit()
{
    AnotherMainWindow* mainWindow = new AnotherMainWindow(nullptr, -1, "Another Ray Tracer", wxDefaultPosition, wxSize(1600 + 16 + 200 + 4, 900 + 108));
    mainWindow->Show();

    return true;
}

bool AnotherApp::OnExceptionInMainLoop()
{
    try { throw; }
    catch (std::exception& e)
    {
        int action = MessageBoxA(NULL, (std::string("Exception: ") + e.what() + std::string("\r\nOK to continue, CANCEL to halt program")).c_str(), "C++ Exception Caught", MB_OKCANCEL);
        if (action == IDCANCEL)
            return false;
        if (action == IDOK)
            return true;
    }
    return true;   // continue on. Return false to abort program
}