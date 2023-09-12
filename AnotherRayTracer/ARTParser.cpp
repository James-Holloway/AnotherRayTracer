#include "ARTParser.h"

using namespace ARTParser;

std::string ARTParser::LeftTrim(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }));
    return s;
}

std::string ARTParser::RightTrim(std::string s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }).base(), s.end());
    return s;
}

std::string ARTParser::Trim(std::string s)
{
    s = RightTrim(s);
    s = LeftTrim(s);
    return s;
}

std::vector<std::string> ARTParser::SplitText(std::string str, std::string delimiter)
{
    std::vector<std::string> strings;

    size_t last = 0, next = 0;
    while ((next = str.find(delimiter, last)) != std::string::npos)
    {
        strings.push_back(str.substr(last, next - last));
        last = next + 1;
    }
    strings.push_back(str.substr(last));

    return strings;
}

std::string ARTParser::ToLower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return s;
}

void ARTParser::ParsedData::CreateError(std::string error)
{
    errors.push_back(std::string("Error on line ") + std::to_string(lineNumber) + std::string(": ") + error);
}

void ARTParser::ParsedData::CreateError(const char* error)
{
    errors.push_back(std::string("Error on line ") + std::to_string(lineNumber) + std::string(": ") + std::string(error));
}


// camera x y z lx ly lz
void ARTParser::ParseCamera(std::vector<std::string> line, Scene& scene, ParsedData& data)
{
    if (line.size() < 7)
    {
        data.CreateError("Camera did not have enough values");
        return;
    }

    double x = 0, y = 0, z = 0;
    double lx = 0, ly = 0, lz = 0;

    try
    {
        x = std::stod(line[1]);
        y = std::stod(line[2]);
        z = std::stod(line[3]);
    }
    catch (std::exception& e)
    {
        std::string err = std::string("Error while parsing camera's position: ") + e.what();
        data.CreateError(err);
        return;
    }

    try
    {
        lx = std::stod(line[4]);
        ly = std::stod(line[5]);
        lz = std::stod(line[6]);
    }
    catch (std::exception& e)
    {
        std::string err = std::string("Error while parsing camera's look at: ") + e.what();
        data.CreateError(err);
        return;
    }

    scene.camera.LookAt(Vector3D(x, y, z), Vector3D(lx, ly, lz));
}

// color name r g b
void ARTParser::ParseColor(std::vector<std::string> line, Scene& scene, ParsedData& data)
{
    if (line.size() < 5)
    {
        data.CreateError("Color did not have enough values");
        return;
    }

    std::string name = line[1];

    double r, g, b;
    try
    {
        r = std::stod(line[2]);
        g = std::stod(line[3]);
        b = std::stod(line[4]);
    }
    catch (std::exception& e)
    {
        std::string err = std::string("Error while parsing color's RGB: ") + e.what();
        data.CreateError(err);
        return;
    }

    if (r > 1.0)
        r /= 255;
    if (g > 1.0)
        g /= 255;
    if (b > 1.0)
        b /= 255;

    data.colors[name] = Color(r, g, b);
}

// material name color [diffuse] [specular] [reflective]
void ARTParser::ParseMaterial(std::vector<std::string> line, Scene& scene, ParsedData& data)
{
    if (line.size() < 3)
    {
        data.CreateError("Material did not have enough values");
        return;
    }

    std::string name = line[1];
    std::string colorName = line[2];

    double diffuse = 0.5, specular = 0.5, reflective = 0.0;

    if (line.size() > 3)
    {
        try
        {
            diffuse = std::stod(line[3]);
        }
        catch (std::exception& e)
        {
            std::string err = std::string("Error while parsing color's diffuse: ") + e.what();
            data.CreateError(err);
            return;
        }

        if (line.size() > 4)
        {
            try
            {
                specular = std::stod(line[4]);
            }
            catch (std::exception& e)
            {
                std::string err = std::string("Error while parsing material's specular: ") + e.what();
                data.CreateError(err);
                return;
            }

            if (line.size() > 5)
            {
                try
                {
                    reflective = std::stod(line[5]);
                }
                catch (std::exception& e)
                {
                    std::string err = std::string("Error while parsing material's reflective: ") + e.what();
                    data.CreateError(err);
                    return;
                }
            }
        }
    }

    auto colorIter = data.colors.find(colorName);
    if (colorIter != data.colors.end())
    {
        data.materials[name] = Material(colorIter->second, diffuse, specular, reflective);
    }
    else
    {
        std::string err = std::string("Could not find existing color of name: ") + colorName;
        data.CreateError(err);
    }
}

// background color
void ARTParser::ParseBackground(std::vector<std::string> line, Scene& scene, ParsedData& data)
{
    if (line.size() < 2)
    {
        data.CreateError("Background did not have enough values");
        return;
    }

    std::string colorName = line[1];

    auto colorIter = data.colors.find(colorName);
    if (colorIter != data.colors.end())
    {
        scene.background = colorIter->second;
    }
    else
    {
        std::string err = std::string("Could not find existing color of name: ") + colorName;
        data.CreateError(err);
    }
}

// sphere x y z r material
void ARTParser::ParseSphere(std::vector<std::string> line, Scene& scene, ParsedData& data)
{
    if (line.size() < 6)
    {
        data.CreateError("Sphere did not have enough values");
        return;
    }

    double x = 0, y = 0, z = 0, r = 0;

    try
    {
        x = std::stod(line[1]);
        y = std::stod(line[2]);
        z = std::stod(line[3]);
    }
    catch (std::exception& e)
    {
        std::string err = std::string("Error while parsing sphere's position: ") + e.what();
        data.CreateError(err);
        return;
    }

    try
    {
        r = std::stod(line[4]);
    }
    catch (std::exception& e)
    {
        std::string err = std::string("Error while parsing sphere's radius: ") + e.what();
        data.CreateError(err);
        return;
    }

    std::string matName = line[5];

    auto matIter = data.materials.find(matName);
    if (matIter != data.materials.end())
    {
        scene.shapes.push_back(std::make_shared<Sphere>(Vector3D(x, y, z), r, matIter->second));
    }
    else
    {
        std::string err = std::string("Could not find existing material of name: ") + matName;
        data.CreateError(err);
    }
}

// light x y z color
void ARTParser::ParseLight(std::vector<std::string> line, Scene& scene, ParsedData& data)
{
    if (line.size() < 5)
    {
        data.CreateError("Sphere did not have enough values");
        return;
    }

    double x = 0, y = 0, z = 0, r = 0;

    try
    {
        x = std::stod(line[1]);
        y = std::stod(line[2]);
        z = std::stod(line[3]);
    }
    catch (std::exception& e)
    {
        std::string err = std::string("Error while parsing sphere's position: ") + e.what();
        data.CreateError(err);
        return;
    }

    std::string colorName = line[4];

    auto colorIter = data.colors.find(colorName);
    if (colorIter != data.colors.end())
    {
        scene.lights.push_back(std::make_shared<Light>(Vector3D(x,y,z), colorIter->second));
    }
    else
    {
        std::string err = std::string("Could not find existing color of name: ") + colorName;
        data.CreateError(err);
    }
}

// plane nx ny nz distance color
void ARTParser::ParsePlane(std::vector<std::string> line, Scene& scene, ParsedData& data)
{
    if (line.size() < 6)
    {
        data.CreateError("Plane did not have enough values");
        return;
    }

    double nx = 0, ny = 0, nz = 0, distance = 0;

    try
    {
        nx = std::stod(line[1]);
        ny = std::stod(line[2]);
        nz = std::stod(line[3]);
    }
    catch (std::exception& e)
    {
        std::string err = std::string("Error while parsing plane's normal: ") + e.what();
        data.CreateError(err);
        return;
    }

    try
    {
        distance = std::stod(line[4]);
    }
    catch (std::exception& e)
    {
        std::string err = std::string("Error while parsing plane's distance: ") + e.what();
        data.CreateError(err);
        return;
    }

    std::string matName = line[5];

    auto matIter = data.materials.find(matName);
    if (matIter != data.materials.end())
    {
        scene.shapes.push_back(std::make_shared<Plane>(Vector3D(nx, ny, nz), distance, matIter->second));
    }
    else
    {
        std::string err = std::string("Could not find existing material of name: ") + matName;
        data.CreateError(err);
    }
}

void ARTParser::ParseBounces(std::vector<std::string> line, Scene& scene, ParsedData& data)
{
    int bounces = 3;
    try
    {
       bounces = std::stoi(line[1]);
    }
    catch (std::exception& e)
    {
        std::string err = std::string("Error while parsing bounce's bounces: ") + e.what();
        data.CreateError(err);
        return;
    }
    scene.maxBounces = std::clamp(bounces, 0, 100);
}

void ARTParser::ParseSize(std::vector<std::string> line, Scene& scene, ParsedData& data)
{
    int width = scene.width, height = scene.height;
    try
    {
        width = std::stoi(line[1]);
        height = std::stoi(line[2]);
    }
    catch (std::exception& e)
    {
        std::string err = std::string("Error while parsing size's size: ") + e.what();
        data.CreateError(err);
        return;
    }

    scene.width = std::max(width, 1);
    scene.height = std::max(height, 1);
}

void ARTParser::ParseLine(std::string line, Scene& scene, ParsedData& data)
{
    if (line.length() == 0)
        return;

    std::vector<std::string> split = SplitText(line, " ");
    if (split.size() == 0)
        return;

    // Comment
    if (split[0].length() > 0 && split[0][0] == '#')
        return;

    auto iter = ParseFunctions.find(ToLower(split[0]));
    if (iter != ParseFunctions.end())
    {
        iter->second(split, scene, data);
    }
    else
    {
        std::string err = std::string("Unknown function: ") + split[0];
        data.CreateError(err);
    }
}

ParsedData ARTParser::ParseScene(std::string str, Scene& scene)
{
    scene.Reset();

    ParsedData data{};

    std::vector<std::string> lines = SplitText(str, "\n");

    unsigned int l = 1;
    for (std::string line : lines)
    {
        data.lineNumber = l++;
        ParseLine(Trim(line), scene, data);
    }

    return data;
}
