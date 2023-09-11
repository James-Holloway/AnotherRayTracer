# Another Ray Tracer

Just another offline CPU ray tracer using [wxWidgets](https://www.wxwidgets.org/) following [Dylan Beattie's JavaScript ray tracer workshop](https://ursatile.github.io/jsray/). 

## The Code

* main : wxApp - Used to start the wxWidgets program
* AnotherMainWindow : wxFrame - Used to display the rendered scene
* AnotherRayTracer - Holds a Scene and output image, along with functions to render the scene
* Scene - The scene, containing a background color, a camera, the size of the render and the shapes to be drawn.
* Shape/Sphere - Basic shapes that the ray tracer will hit when tracing the scene. Each shape holds a color
* Color - The color of the shape or background. Stored in float format
* Ray - The ray, a simple struct that contains the start position and direction of the ray which makes the ray tracer possible
* Vector3D - Another important part of ART, a vector in 3D space with overloaded operators to match
* wxImagePanel - The image panel that allows wxWidgets to draw a wxBitmap/wxImage

## Building

Install dependencies using `vcpkg install` using `x64-windows` triplet:
* wxwidgets

Build from solution provided

## Credits

The icons used are from [vscode-icons](https://github.com/microsoft/vscode-icons)

The main window was initially created by [wxUIEditor](https://github.com/KeyWorksRW/wxUiEditor) but extended by myself

The wxImagePanel has been modified from the original at [wxImagePanel](https://github.com/tomay3000/wxImagePanel/)