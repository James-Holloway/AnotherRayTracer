#include "anothermainwindow.h"
#include <wx/mstream.h>  // memory stream classes
#include <wx/zstream.h>  // zlib stream classes
#include <wx/wfstream.h> // File stream classes
#include <memory>

// Convert compressed SVG string into a wxBitmapBundle
inline wxBitmapBundle wxueBundleSVG(const unsigned char* data,
    size_t size_data, size_t size_svg, wxSize def_size)
{
    auto str = std::make_unique<char[]>(size_svg);
    wxMemoryInputStream streain(data, size_data);
    wxZlibInputStream zlib_strm(streain);
    zlib_strm.Read(str.get(), size_svg);
    return wxBitmapBundle::FromSVG(str.get(), def_size);
};

bool AnotherMainWindow::Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString &name)
{
    if (!wxFrame::Create(parent, id, title, pos, size, style, name))
        return false;

    // Toolbar
    {
        toolBar = CreateToolBar();

        // Scene operations
        toolNew = toolBar->AddTool(wxID_NEW, wxEmptyString, wxueBundleSVG(wxue_img::new_file_svg, 273, 486, wxSize(16, 16)), "New Scene");

        toolLoad = toolBar->AddTool(ID_LOAD, wxEmptyString, wxueBundleSVG(wxue_img::file_code_svg, 262, 483, wxSize(16, 16)), "Load Scene...");

        toolSave = toolBar->AddTool(wxID_SAVE, wxEmptyString, wxueBundleSVG(wxue_img::save_svg, 178, 288, wxSize(16, 16)), "Save Scene");

        toolSaveAs = toolBar->AddTool(wxID_SAVEAS, wxEmptyString, wxueBundleSVG(wxue_img::save_as_svg, 332, 673, wxSize(16, 16)), "Save Scene As...");

        toolValidate = toolBar->AddTool(ID_VALIDATE, wxEmptyString, wxueBundleSVG(wxue_img::check_svg, 149, 205, wxSize(16, 16)), "Validate");

        toolBar->AddSeparator();

        // Render operations
        toolRun = toolBar->AddTool(ID_RENDER_START, wxEmptyString, wxueBundleSVG(wxue_img::debug_start_svg, 104, 130, wxSize(16, 16)), "Run Render");

        // toolPause = toolBar->AddTool(ID_RENDER_PAUSE, wxEmptyString, wxueBundleSVG(wxue_img::debug_pause_svg, 96, 153, wxSize(16, 16)), "Pause Render");

        toolStop = toolBar->AddTool(ID_RENDER_STOP, wxEmptyString, wxueBundleSVG(wxue_img::debug_stop_svg, 95, 113, wxSize(16, 16)), "Clear Render");

        // toolRestart = toolRestart = toolBar->AddTool(ID_RENDER_RESTART, wxEmptyString, wxueBundleSVG(wxue_img::debug_restart_svg, 291, 557, wxSize(16, 16)), "Restart Render");

        toolRenderSave = toolBar->AddTool(ID_RENDER_SAVE, wxEmptyString, wxueBundleSVG(wxue_img::save_blue_svg, 342, 592, wxSize(16, 16)), "Save Render As...");

        toolBar->Realize();
    }

    // Menu bar
    {
        menuBar = new wxMenuBar();

        wxMenu* menuFile = new wxMenu();
        menuFile->Append(wxID_NEW, "&New Scene");
        menuFile->Append(ID_LOAD, "&Load Scene...");
        menuFile->Append(wxID_SAVE, "&Save Scene");
        menuFile->Append(wxID_SAVEAS, "Save Scene &As...");
        menuFile->Append(ID_VALIDATE, "&Validate");
        menuFile->AppendSeparator();
        menuFile->Append(wxID_EXIT, "E&xit");
        menuBar->Append(menuFile, "&File");

        wxMenu* menuRender = new wxMenu();
        menuRender->Append(ID_RENDER_START, "&Run Render");
        // menuRender->Append(ID_RENDER_PAUSE, "&Pause Render");
        menuRender->Append(ID_RENDER_STOP, "&Clear Render");
        // menuRender->Append(ID_RENDER_RESTART, "R&estart Render");
        menuRender->Append(ID_RENDER_SAVE, "&Save Render As...");
        menuBar->Append(menuRender, "&Render");

        SetMenuBar(menuBar);
    }

    // Status bar
    statusBar = CreateStatusBar();

    splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH);
    splitter->SetSashGravity(0.0);
    splitter->SetMinimumPaneSize(150);

    // Text side
    {
        splitterText = new wxSplitterWindow(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH);
        splitterText->SetSashGravity(1.0);
        splitterText->SetMinimumPaneSize(150);

        sceneTextBox = new wxTextCtrl(splitterText, ID_SCENETEXTBOX, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
        sceneErrors = new wxTextCtrl(splitterText, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
        sceneErrors->Disable();

        splitterText->SplitHorizontally(sceneTextBox, sceneErrors, 400);
    }
    // Image
    {
        imagePanel = new wxImagePanel(splitter, wxID_ANY);
        imagePanel->ShrinkOnly();
    }

    splitter->SplitVertically(splitterText, imagePanel, 200);

    Centre(wxBOTH);
    
    // Event binding
    {
        Bind(wxEVT_MENU, &AnotherMainWindow::OnExit, this, wxID_EXIT);
        Bind(wxEVT_MENU, &AnotherMainWindow::OnNewScene, this, wxID_NEW);
        Bind(wxEVT_MENU, &AnotherMainWindow::OnLoadScene, this, ID_LOAD);
        Bind(wxEVT_MENU, &AnotherMainWindow::OnSaveScene, this, wxID_SAVE);
        Bind(wxEVT_MENU, &AnotherMainWindow::OnSaveSceneAs, this, wxID_SAVEAS);
        Bind(wxEVT_MENU, &AnotherMainWindow::OnValidate, this, ID_VALIDATE);
        Bind(wxEVT_MENU, &AnotherMainWindow::OnRunRender, this, ID_RENDER_START);
        Bind(wxEVT_MENU, &AnotherMainWindow::OnPauseRender, this, ID_RENDER_PAUSE);
        Bind(wxEVT_MENU, &AnotherMainWindow::OnStopRender, this, ID_RENDER_STOP);
        Bind(wxEVT_MENU, &AnotherMainWindow::OnRestartRender, this, ID_RENDER_RESTART);
        Bind(wxEVT_MENU, &AnotherMainWindow::OnSaveRenderAs, this, ID_RENDER_SAVE);

        sceneTextBox->Bind(wxEVT_TEXT_ENTER, &AnotherMainWindow::OnSceneTextChanged, this, ID_SCENETEXTBOX);
        sceneTextBox->Bind(wxEVT_TEXT_PASTE, &AnotherMainWindow::OnSceneTextChanged, this, ID_SCENETEXTBOX);
        sceneTextBox->Bind(wxEVT_TEXT_CUT, &AnotherMainWindow::OnSceneTextChanged, this, ID_SCENETEXTBOX);
        sceneTextBox->Bind(wxEVT_KEY_DOWN, &AnotherMainWindow::OnSceneTextKeyDown, this, ID_SCENETEXTBOX);
    }

    wxImage::AddHandler(new wxPNGHandler);

    anotherRayTracer = std::make_shared<AnotherRayTracer>();
    anotherRayTracer->PopulateExample();

    return true;
}

void AnotherMainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void AnotherMainWindow::OnNewScene(wxCommandEvent& event)
{
    SetStatusText("Created New Scene");
    sceneTextBox->SetValue(wxString(AnotherRayTracer::NewScene));
    sceneErrors->SetValue("New Scene created. Press Validate or Run to check for errors");
    fileSaved = false;
    filePath = "";
}

void AnotherMainWindow::OnLoadScene(wxCommandEvent& event)
{
    if (!fileSaved)
    {
        if (wxMessageBox("File has not been saved. Do you wish to proceed anyway?", "ART file not saved", wxICON_QUESTION | wxYES_NO, this) == wxNO)
        {
            return;
        }
    }

    SetStatusText("Loading Scene");
    wxFileDialog openFileDialog(this, "Open ART file", "", "", "ART files (*.art)|*.art", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
        SetStatusText("Cancelled Loading Scene");
        return;
    }
    std::string tempPath = std::string(openFileDialog.GetPath());

    if (!std::filesystem::exists(tempPath))
    {
        SetStatusText("Could not open file '" + tempPath + "' - File does not exist");
        return;
    }


    wxFileInputStream stream(tempPath);

    if (!stream.IsOk())
    {
        SetStatusText("Could not open file '" + tempPath + "'");
        return;
    }

    wxString content;
    char* buffer = new char[1024];
    do
    {
        stream.Read(buffer, 1024 * sizeof(char));
        content.Append(buffer, 1024);
    } while (stream.LastRead() > 0);

    delete[] buffer;

    sceneTextBox->SetValue(content);
    sceneErrors->SetValue("New Scene loaded. Press Validate or Run to check for errors");

    prevFileContents = content;
    filePath = tempPath;
    fileSaved = true;

}

void AnotherMainWindow::OnSaveScene(wxCommandEvent& event)
{
    if (filePath == "")
    {
        OnSaveSceneAs(event);
        return;
    }

    SetStatusText("Saving Scene");

    SaveScene();
}

void AnotherMainWindow::OnSaveSceneAs(wxCommandEvent& event)
{
    SetStatusText("Scene Saved As");
    SaveSceneAs();
}

void AnotherMainWindow::OnValidate(wxCommandEvent& event)
{
    SetStatusText("Validating");
    ParseART();
}

void AnotherMainWindow::OnRunRender(wxCommandEvent& event)
{
    SetStatusText("Render Running");
    RunRender();
    SetStatusText("Render Rendered");
}

void AnotherMainWindow::OnPauseRender(wxCommandEvent& event)
{
    SetStatusText("Render Paused");
}

void AnotherMainWindow::OnStopRender(wxCommandEvent& event)
{
    SetStatusText("Render Cleared");
    imagePanel->SetImage(nullptr);
    imagePanel->PaintNow();
    imagePanel->Refresh();
    imagePanel->Update();
}

void AnotherMainWindow::OnRestartRender(wxCommandEvent& event)
{
    SetStatusText("Render Restarted");
}

void AnotherMainWindow::OnSaveRenderAs(wxCommandEvent& event)
{
    SetStatusText("Saving Render As...");
    SaveRenderAs();
}

void AnotherMainWindow::OnSceneTextChanged(wxCommandEvent& event)
{
    std::string tempFileContents = std::string(sceneTextBox->GetValue());
    if (prevFileContents != tempFileContents)
    {
        fileSaved = false;
    }

    prevFileContents = tempFileContents;
    event.Skip();
}

void AnotherMainWindow::OnSceneTextKeyDown(wxKeyEvent& event)
{
    if (event.ControlDown() && (event.GetKeyCode() == (int)'s' || event.GetKeyCode() == (int)'S'))
    {
        if (filePath == "" || event.ShiftDown())
        {
            SaveSceneAs();
            return;
        }
        SetStatusText("Saving Scene");
        SaveScene();
        return;
    }
    event.Skip();
}

void AnotherMainWindow::SaveScene()
{
    wxFileOutputStream stream(filePath);

    if (!stream.IsOk())
    {
        SetStatusText("Could not open file '" + filePath + "' for saving");
        return;
    }

    wxString content = sceneTextBox->GetValue();
    const char* contentChar = content.c_str().AsChar();
    stream.WriteAll(contentChar, content.size());
    stream.Close();

    fileSaved = true;
}

void AnotherMainWindow::SaveSceneAs()
{
    wxFileDialog saveFileDialog(this, "Save ART file", "", "", "ART files (*.art)|*.art", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        SetStatusText("Cancelled Saving Scene As");
        return;
    }

    filePath = saveFileDialog.GetPath();

    SetStatusText("Saving Scene");

    SaveScene();
}

void AnotherMainWindow::SaveRenderAs()
{
    if (imagePanel->IsImageNull())
    {
        SetStatusText("Nothing has been rendered, cannot save render as");
        return;
    }

    wxImage image = imagePanel->GetImage();
    if (!image.IsOk())
    {
        SetStatusText("Cannot save render - image is not OK");
        return;
    }

    wxFileDialog saveFileDialog(this, "Save Render", "", "", "PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        SetStatusText("Cancelled Saving Render As");
        return;
    }

    std::string renderPath = std::string(saveFileDialog.GetPath());

    SetStatusText("Saving Render");

    wxBitmap bitmap = wxBitmap(image);
    bitmap.SaveFile(renderPath, wxBITMAP_TYPE_PNG);

    SetStatusText("Saved Render");
}

void AnotherMainWindow::ParseART()
{
    std::string errors = anotherRayTracer->Parse(sceneTextBox->GetValue().ToStdString());
    sceneErrors->SetValue(wxString(errors));
}

void AnotherMainWindow::RunRender()
{
    wxSize size = imagePanel->GetSize();
    anotherRayTracer->Resize(size.x, size.y);
    ParseART();
    anotherRayTracer->Render();

    imagePanel->SetImage(nullptr);
    wxImage image = wxImage(anotherRayTracer->GetWidth(), anotherRayTracer->GetHeight(), anotherRayTracer->image.data(), true);
    imagePanel->SetImage(image);
}


#pragma region Embedded SVG Images
namespace wxue_img
{
    // check.svg
    const unsigned char check_svg[149]{
        120,218,93,143,75,14,194,48,12,68,57,138,21,214,184,216,73,99,71,106,122,130,112,1,118,136,22,168,20,65,197,167,231,39,97,129,
        4,242,234,89,51,154,153,238,177,156,251,110,62,60,47,112,154,114,222,220,95,121,140,102,92,198,235,109,24,12,28,243,52,255,255,
        134,104,118,228,208,89,82,176,104,217,114,106,49,120,146,22,232,203,36,180,117,149,89,197,37,66,229,202,138,45,21,100,244,54,216,
        0,130,193,177,215,34,47,110,102,32,70,82,150,84,108,222,171,64,209,137,87,77,191,105,123,243,169,26,205,218,113,61,211,244,93,
        83,103,172,222,60,102,50,103
    };
    // debug-pause.svg
    const unsigned char debug_pause_svg[96]{
        120,218,179,41,46,75,183,179,41,72,44,201,80,72,177,85,242,53,209,51,53,48,48,50,81,48,210,179,180,180,180,176,240,49,211,51,64,
        230,135,25,130,25,150,30,80,117,97,80,241,40,95,67,67,176,8,134,66,67,3,176,9,48,133,62,104,234,162,148,20,210,50,115,114,108,
        149,148,13,12,204,29,157,157,149,244,237,108,244,65,78,98,0,0,182,251,35,21
    };
    // debug-restart.svg
    const unsigned char debug_restart_svg[291]{
        120,218,93,82,203,78,3,49,12,228,83,162,229,140,27,199,143,56,82,91,9,237,133,67,185,238,129,27,162,5,42,173,160,226,209,239,199,
        217,23,208,83,52,30,123,108,143,179,254,60,191,108,215,167,199,175,215,240,124,236,251,155,143,239,254,176,105,14,231,195,219,
        251,126,223,132,167,254,120,186,140,237,55,205,61,38,200,18,83,200,80,74,49,107,103,140,17,216,100,120,51,137,4,143,179,103,4,
        131,228,52,207,184,85,96,180,180,208,12,230,88,3,34,112,20,116,140,84,114,14,5,140,56,242,206,213,185,68,173,178,84,172,180,4,
        154,57,99,173,23,52,9,2,217,10,91,64,170,243,252,105,55,226,214,117,69,169,44,60,242,144,80,251,17,146,46,120,89,103,194,12,106,
        138,57,44,245,35,255,171,63,229,171,203,100,92,176,215,73,201,162,33,65,65,246,185,9,36,214,124,6,34,210,220,13,107,155,221,37,
        136,53,222,233,136,119,163,139,236,115,36,174,188,142,125,58,169,251,59,246,122,73,73,91,113,127,34,145,235,185,59,238,163,130,
        24,215,54,252,111,188,9,183,243,53,102,126,190,150,184,123,94,118,113,204,135,102,248,10,155,230,154,204,110,137,155,213,118,189,
        170,223,228,234,7,208,78,119,222
    };
    // debug-start.svg
    const unsigned char debug_start_svg[104]{
        120,218,179,41,46,75,183,179,41,72,44,201,80,72,177,85,242,53,209,51,48,48,48,50,81,48,10,51,52,214,179,48,180,180,244,1,210,32,
        33,5,115,61,11,11,31,184,116,148,175,169,158,41,152,105,2,86,102,234,99,104,160,103,108,104,96,12,81,7,147,52,52,12,131,202,71,
        41,41,164,101,230,228,216,42,41,27,91,88,56,26,155,40,233,219,217,232,131,236,102,0,0,185,92,29,150
    };
    // debug-stop.svg
    const unsigned char debug_stop_svg[95]{
        120,218,179,41,46,75,183,179,41,72,44,201,80,72,177,85,242,53,210,51,48,48,48,50,81,48,10,51,52,241,48,52,1,243,194,140,60,160,
        194,81,190,134,70,122,230,166,6,70,10,96,218,195,88,207,8,200,49,9,3,209,30,80,169,48,48,29,165,164,144,150,153,147,99,171,164,
        236,104,104,100,102,224,162,164,111,103,163,15,178,138,1,0,12,45,26,134
    };
    // file-code.svg
    const unsigned char file_code_svg[262]{
        120,218,93,145,79,79,195,48,12,197,249,40,85,56,227,37,78,156,56,82,187,115,15,233,181,135,222,16,29,108,82,5,19,127,246,249,177,
        163,12,24,202,37,207,126,254,61,71,233,63,46,47,251,254,252,248,121,236,158,79,219,246,240,254,181,29,6,115,184,28,94,223,214,
        213,116,79,219,233,252,191,182,14,102,114,22,40,89,236,28,184,80,156,7,38,17,1,130,136,0,214,86,193,179,220,73,187,164,5,71,35,
        214,91,40,88,45,161,211,254,236,196,211,26,157,27,5,140,104,177,252,13,88,52,174,66,105,20,154,222,202,181,130,51,45,147,111,60,
        148,196,171,99,142,99,110,113,185,181,73,210,112,108,230,101,34,176,17,165,44,54,239,75,4,78,89,84,130,100,73,148,75,58,146,74,
        104,195,89,42,121,206,192,28,107,215,233,186,242,144,88,39,89,149,3,79,190,220,96,151,137,129,235,188,112,157,174,66,77,89,73,
        145,137,200,25,149,205,21,157,127,12,21,141,133,33,101,250,101,203,171,35,70,108,43,223,160,23,83,63,112,48,247,1,245,152,221,
        190,223,233,231,222,125,3,20,184,107,123
    };
    // new-file.svg
    const unsigned char new_file_svg[273]{
        120,218,93,145,205,142,131,32,20,133,231,81,8,221,180,139,42,32,212,154,168,107,22,54,153,21,139,238,154,138,74,66,127,162,180,
        125,253,1,174,154,73,227,230,112,206,149,115,243,81,78,239,190,46,123,116,181,230,185,127,94,220,80,225,215,104,183,155,112,38,
        59,92,151,193,67,157,177,118,63,190,172,174,176,126,235,251,163,109,49,252,241,229,181,21,62,241,132,16,194,56,202,101,6,74,113,
        73,64,113,202,169,202,86,159,200,121,214,123,249,58,187,120,249,249,68,73,34,188,70,52,33,69,81,28,27,154,37,5,33,25,226,137,128,
        51,204,34,161,124,34,66,12,227,92,130,226,205,92,133,66,164,142,235,221,52,147,20,34,117,144,197,108,50,41,150,88,250,102,230,
        101,243,181,65,92,41,86,50,37,36,101,113,157,102,245,206,56,146,170,240,134,179,240,225,180,46,83,143,183,213,221,84,151,1,216,
        111,160,105,60,166,200,215,227,29,245,213,161,143,105,3,120,122,192,104,208,166,31,28,104,184,235,51,24,167,49,114,227,229,62,
        117,143,241,86,225,40,237,197,233,237,63,174,187,88,182,116,120,9,165,105,120,223,159,63,63,187,126,226
    };
    // save-as.svg
    const unsigned char save_as_svg[332]{
        120,218,93,146,203,78,3,49,12,69,249,148,104,88,19,108,199,121,88,106,187,158,69,186,157,69,119,136,22,168,52,130,138,71,191,31,
        59,205,240,168,186,152,28,231,218,247,38,205,234,227,252,188,89,157,30,62,95,220,211,113,158,239,222,191,230,195,122,56,156,15,
        175,111,251,253,224,30,231,227,233,186,182,95,15,91,68,15,12,193,161,15,36,146,42,146,207,8,228,66,197,224,1,108,229,51,232,206,
        196,38,4,30,85,17,181,110,202,182,207,62,90,125,234,186,138,224,67,208,58,45,122,104,186,41,117,230,134,60,45,251,212,217,230,
        241,24,47,84,185,153,176,179,20,63,154,138,151,175,107,218,101,66,165,165,250,235,104,9,234,213,217,118,219,220,133,113,148,37,
        196,216,107,83,220,109,213,203,76,93,172,120,137,225,146,215,53,123,41,186,206,30,139,8,87,241,172,72,150,33,105,65,57,196,206,
        5,1,107,105,114,178,228,88,26,23,229,104,76,185,198,133,216,103,35,210,203,70,35,172,169,221,188,2,54,40,26,64,20,170,26,231,182,
        4,159,130,18,9,80,49,138,237,223,18,61,97,28,123,118,59,35,169,65,182,56,122,97,58,51,45,230,172,189,125,168,182,165,250,79,105,
        141,146,187,61,89,234,222,72,246,16,4,213,68,35,177,72,49,70,106,151,3,9,192,230,252,105,220,13,237,249,173,135,91,38,251,13,247,
        155,213,189,61,205,155,111,43,174,145,18
    };
    // save.svg
    const unsigned char save_svg[178]{
        120,218,93,80,189,14,194,32,16,246,81,8,206,82,238,128,138,73,219,153,129,174,12,221,140,173,218,132,104,227,79,159,95,174,52,
        38,26,22,190,223,59,168,158,243,165,169,166,227,235,202,206,99,140,187,199,59,14,53,31,230,225,118,239,123,206,78,113,156,254,
        185,190,230,45,40,161,140,66,6,2,116,233,65,11,75,8,69,73,200,8,41,37,50,21,18,111,72,52,4,193,56,88,110,218,195,98,208,140,164,
        0,228,201,2,3,151,138,73,243,63,3,186,22,215,4,166,78,151,98,132,130,18,40,173,7,20,251,3,13,119,144,123,67,233,178,65,7,116,107,
        176,107,237,183,33,237,33,179,17,221,202,118,124,121,125,205,183,26,233,240,162,169,10,250,153,205,7,46,112,68,11
    };
    // save-blue.svg
    const unsigned char save_blue_svg[342]{
        120,218,93,82,77,115,130,48,16,237,79,201,224,85,99,54,31,124,41,158,57,224,149,3,55,10,177,166,165,192,72,180,245,223,55,11,168,
        85,24,102,118,223,190,221,236,123,100,59,92,62,118,219,90,31,6,98,234,196,195,32,244,214,187,109,95,218,35,57,152,166,89,157,206,
        141,78,60,125,209,109,87,215,30,169,26,211,191,98,174,113,15,130,10,37,56,1,10,210,207,64,210,16,51,78,125,204,20,101,140,113,
        34,114,135,43,44,42,76,65,165,48,70,50,131,145,32,9,150,114,64,206,84,32,144,186,193,88,203,158,14,40,246,124,238,224,110,102,
        234,218,48,203,5,229,44,204,128,211,32,194,195,83,152,230,230,126,58,17,100,206,211,185,177,216,135,247,9,110,15,54,17,121,58,
        163,133,55,170,79,188,133,228,248,122,163,61,232,138,11,7,123,69,253,72,136,23,162,140,64,171,205,232,85,215,151,149,177,215,24,
        238,22,62,81,101,168,149,40,95,168,155,193,158,186,47,29,183,93,171,231,120,245,99,106,123,140,157,7,146,7,162,255,189,193,141,
        105,117,85,246,241,251,217,218,255,216,103,103,218,248,219,88,125,186,161,143,69,198,159,67,20,245,149,140,66,33,150,1,5,197,34,
        46,35,146,19,52,42,80,44,144,36,35,206,1,33,21,131,96,25,209,200,249,236,135,138,20,15,213,2,132,112,194,187,218,244,238,115,203,
        214,218,94,123,61,36,94,229,30,148,187,198,155,244,246,7,90,228,164,87
    };
}
#pragma endregion
