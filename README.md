# Another Ray Tracer

Just another offline CPU ray tracer using [wxWidgets](https://www.wxwidgets.org/) following [Dylan Beattie's JavaScript ray tracer workshop](https://ursatile.github.io/jsray/). Uses ART functions to describe what to render

![Example Cornell Box](./Images/cornell%20box.png)

## ART Functions

* `#`
  * Comments and leading/trailing whitespace are ignored
  * Comments must be on their own line
  * Example: `# This is a Comment`
* `color <name> <R> <G> <B>`
  * Creates a color that can be used by other functions, can only be used after declaration
  * R, G, B can be 0.0-1.0 or 0-255
  * Example: `color cornflowerblue 100 149 237`
* `material <color> [diffuse] [specular] [reflective]`
  * `<color>` is the color name
  * `[diffuse]`, `[specular]` and `[reflective]` are optional parameters that control the shine and reflectiveness of the material. They default to 0.5, 0.5 & 0.0 respectively
  * Example: `material myMaterial cornflowerblue 0.75 0.25 0.0` for a slightly specular cornflower blue
* `background <color>`
  * Sets the background color of the scene
  * Example: `background cornflowerblue`
* `camera <x> <y> <z> <lx> <ly> <lz>`
  * Sets the camera to the x y z position and looks at lx ly lz position
  * Example: `camera 0 5 -8.5 0 0 0` is up and back slightly, looking at the scene origin
* `sphere <x> <y> <z> <radius> <material>`
  * Places a sphere at the x y z position with the specified radius and set material. Note this is a material, not a color. You need to create a material with the specified color
  * Example: `sphere -2 0 2 1.0 myMaterial`
* `plane <nx> <ny> <nz> <distance> <material>`
  * Creates a plane with the normal nx ny nz and places it distance away
  * Example: `plane 0 1 0 -1 myMaterial` creates a plane facing upwards at 0,-1,0
* `light <x> <y> <z> <color>`
  * Creates a light at the x y z position with the specified color
  * If no lights are in the scene, then the scene becomes unlit/fullbright
  * Note this takes a color, not a material
  * Example: `light 5 10 -5 white`
* `bounces <bounces>`
  * Number of light bounces a reflective material will do. Internally clamped between 0 and 100, defaulting to 3
  * Example: `bounces 5`
* `size <width> <height>`
  * Sets the output size of the render
  * If no size is set, the size defaults to the size of the window's image panel
  * Images larger than the window's image panel get clamped to fit, which may cause stretching
  * The default size of the image panel is 1600x900
  * Example: `size 1920 1080`

## The Code

* main : wxApp - Used to start the wxWidgets program
* AnotherMainWindow : wxFrame - Used to display the rendered scene
* AnotherRayTracer - Holds a Scene and output image, along with functions to render the scene
* Scene - The scene, containing a background color, a camera, the size of the render and the shapes to be drawn
* Shape/Sphere/Plane - Basic shapes that the ray tracer will hit when tracing the scene. Has functions that can be overridden in derived Shapes and a material
* Material - Each shape has a material which contains a color, diffuse and specular
* Color - The color of the shape or background. Stored in double format
* Ray - The ray, a simple struct that contains the start position and direction of the ray which makes the ray tracer possible
* Vector3D - Another important part of ART, a vector in 3D space with overloaded operators to match
* wxImagePanel - The image panel that allows wxWidgets to draw a wxBitmap/wxImage

## Building

Install dependencies using `vcpkg install` using `x64-windows` triplet:
* wxwidgets

Build from solution provided

## Credits

The icons used are from [vscode-icons](https://github.com/microsoft/vscode-icons) ([CC-BY-4.0](https://github.com/microsoft/vscode-icons/blob/main/LICENSE))

The main window was initially created by [wxUIEditor](https://github.com/KeyWorksRW/wxUiEditor) ([Apache License 2.0](https://github.com/KeyWorksRW/wxUiEditor/blob/main/LICENSE)) but extended by myself

The wxImagePanel has been modified from the original at [wxImagePanel](https://github.com/tomay3000/wxImagePanel/) ([wxWidgets license](https://github.com/wxWidgets/wxWidgets/blob/master/docs/licence.txt))