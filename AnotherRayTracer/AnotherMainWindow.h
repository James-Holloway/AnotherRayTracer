#pragma once

#include <wx/bitmap.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/menu.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/toolbar.h>
#include "wxImagePanel.h"
#include "AnotherRayTracer.h"

class AnotherMainWindow : public wxFrame
{
public:
    AnotherMainWindow() {}
    AnotherMainWindow(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = "Another Ray Tracer", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1600, 900), long style = wxDEFAULT_FRAME_STYLE|wxCLOSE_BOX, const wxString &name = wxFrameNameStr)
    {
        Create(parent, id, title, pos, size, style, name);
    }

    bool Create(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = "Another Ray Tracer", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1600, 900), long style = wxDEFAULT_FRAME_STYLE|wxCLOSE_BOX, const wxString &name = wxFrameNameStr);

protected:
    // Class member variables
    wxMenuBar* menuBar;
    wxStatusBar* statusBar;
    wxToolBar* toolBar;
    wxToolBarToolBase* toolLoad;
    wxToolBarToolBase* toolNew;
    wxToolBarToolBase* toolPause;
    wxToolBarToolBase* toolRestart;
    wxToolBarToolBase* toolValidate;
    wxToolBarToolBase* toolRun;
    wxToolBarToolBase* toolSave;
    wxToolBarToolBase* toolSaveAs;
    wxToolBarToolBase* toolStop;
    wxSplitterWindow* splitter;
    wxSplitterWindow* splitterText;
    wxTextCtrl* sceneTextBox;
    wxTextCtrl* sceneErrors;
    wxImagePanel* imagePanel;

protected:
    void OnExit(wxCommandEvent& event);
    void OnNewScene(wxCommandEvent& event);
    void OnLoadScene(wxCommandEvent& event);
    void OnSaveScene(wxCommandEvent& event);
    void OnSaveSceneAs(wxCommandEvent& event);
    void OnValidate(wxCommandEvent& event);
    void OnRunRender(wxCommandEvent& event);
    void OnPauseRender(wxCommandEvent& event);
    void OnStopRender(wxCommandEvent& event);
    void OnRestartRender(wxCommandEvent& event);

    void ParseART();
    void RunRender();

protected:
    std::shared_ptr<AnotherRayTracer> anotherRayTracer;
};

enum {
    ID_LOAD,
    ID_VALIDATE,
    ID_RENDER_START,
    ID_RENDER_PAUSE,
    ID_RENDER_STOP,
    ID_RENDER_RESTART,
};

namespace wxue_img
{
    // Images declared in this class module:

    // check.svg
    extern const unsigned char check_svg[149];
    // debug-pause.svg
    extern const unsigned char debug_pause_svg[96];
    // debug-restart.svg
    extern const unsigned char debug_restart_svg[291];
    // debug-start.svg
    extern const unsigned char debug_start_svg[104];
    // debug-stop.svg
    extern const unsigned char debug_stop_svg[95];
    // file-code.svg
    extern const unsigned char file_code_svg[262];
    // new-file.svg
    extern const unsigned char new_file_svg[273];
    // save-as.svg
    extern const unsigned char save_as_svg[332];
    // save.png
    extern const unsigned char save_svg[178];
}