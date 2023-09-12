#pragma once
#include <wx/panel.h>
#include <wx/dcbuffer.h>
#include <wx/stream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

// https://github.com/tomay3000/wxImagePanel/

class wxImagePanel : public wxPanel
{
protected:
    void Init();
public:
    wxImagePanel();
    wxImagePanel(wxWindow* parent, wxWindowID winID = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER | wxCLIP_CHILDREN, const wxString& name = _T("ImagePanel"));

    virtual ~wxImagePanel();

    void PaintEvent(wxPaintEvent& event);
    void PaintNow();
    void Render(wxDC& dc);
    void OnSize(wxSizeEvent& event);

    inline wxImage GetImage() const
    {
        return image;
    }
    inline void SetImage(wxImage& _image)
    {
        imageNull = false;
        image = _image;
        Refresh();
    }
    inline void SetImage(nullptr_t)
    {
        SetImage(wxNullImage);
        imageNull = true;
    }

    inline bool GetStretch() const
    {
        return stretch;
    }
    inline void SetStretch(bool _stretch)
    {
        stretch = _stretch;
        Refresh();
    }
    inline void StretchImage()
    {
        SetStretch(true);
    }

    inline bool GetCenterImage() const
    {
        return centerImage;
    }
    inline void SetCenterImage(bool _centerImage)
    {
        centerImage = _centerImage;
        Refresh();
    }
    inline void CenterImage()
    {
        return SetCenterImage(true);
    }

    inline bool GetShrinkOnly() const
    {
        return shrinkOnly;
    }
    inline void SetShrinkOnly(bool _shrinkOnly)
    {
        shrinkOnly = _shrinkOnly;
    }
    inline void ShrinkOnly()
    {
        SetShrinkOnly(true);
    }

    inline bool IsImageNull() const
    {
        return imageNull;
    }

protected:
    wxImage image;
    bool stretch;
    bool centerImage;
    bool shrinkOnly;
    bool imageNull = true;
};

