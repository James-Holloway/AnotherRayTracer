#include "wxImagePanel.h"


void wxImagePanel::Init()
{
    image = wxNullImage;
    stretch = false;
    centerImage = false;

    Bind(wxEVT_PAINT, &wxImagePanel::PaintEvent, this);
    Bind(wxEVT_SIZE, &wxImagePanel::OnSize, this);

    // Flicker-free drawing requires this
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

wxImagePanel::wxImagePanel() : wxPanel()
{
    Init();
}

wxImagePanel::wxImagePanel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
    Init();
}

wxImagePanel::~wxImagePanel()
{
    Unbind(wxEVT_PAINT, &wxImagePanel::PaintEvent, this);
    Unbind(wxEVT_SIZE, &wxImagePanel::OnSize, this);
}

/* Called by the system of wxWidgets when the panel needs
   to be redrawn. You can also trigger this call by calling Refresh()/Update(). */
void wxImagePanel::PaintEvent(wxPaintEvent& WXUNUSED(event))
{
    // Depending on your system you may need to look at double-buffered dcs
    wxBufferedPaintDC bpdc(this);
    Render(bpdc);
}

/* Alternatively, you can use a clientDC to paint on the panel at any time.
   Using this generally does not free you from catching paint events,
   since it is possible that e.g. the window manager throws away your drawing
   when the window comes to the background, and expects you will redraw it
   when the window comes back (by sending a paint event). */
void wxImagePanel::PaintNow()
{
    // Depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    wxBufferedDC bdc(&dc);
    Render(bdc);
}

/* Here we do the actual rendering. I put it in a separate method so that it
   can work no matter what type of DC (e.g. wxPaintDC or wxClientDC) is used. */
void wxImagePanel::Render(wxDC& dc)
{
    // Fill the dc with the background colour
    dc.SetBackground(GetBackgroundColour());
    dc.Clear();

    if (!image.IsOk())
        return;

    int panelWidth, panelHeight;
    GetClientSize(&panelWidth, &panelHeight);
    wxPoint pos;
    wxImage img = image;
    wxBitmap bitmap;

    // Should we stretch the image?
    if (shrinkOnly)
    {
        if (panelWidth < 1)
            panelWidth = 1;
        if (panelHeight < 1)
            panelHeight = 1;

        if (img.GetWidth() < panelWidth)
            panelWidth = img.GetWidth();
        if (img.GetHeight() < panelHeight)
            panelHeight = img.GetHeight();

        if (img.IsOk())
            img.Rescale(panelWidth, panelHeight);
    }
    else if (stretch)
    {
        // Make sure we do not attempt to create a bitmap
        // with invalid size (width and/or height < 1)
        if (panelWidth < 1)
            panelWidth = 1;

        if (panelHeight < 1)
            panelHeight = 1;

        if (img.IsOk())
            img.Rescale(panelWidth, panelHeight);
    }
    // Should we center the image?
    else if (centerImage)
    {
        pos.x = (panelWidth - img.GetWidth()) / 2;
        pos.y = (panelHeight - img.GetHeight()) / 2;
    }

    if (img.IsOk())
    {
        bitmap = wxBitmap(img);
        dc.DrawBitmap(bitmap, pos.x, pos.y, false);
    }
}

/* Here we call refresh to tell the panel to draw itself again.
   So when the user resizes the image panel the image should be resized too. */
void wxImagePanel::OnSize(wxSizeEvent& event)
{
    Refresh();

    //skip the event.
    event.Skip();
}