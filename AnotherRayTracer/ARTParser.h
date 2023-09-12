#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include "Scene.h"

namespace ARTParser
{
    std::string LeftTrim(std::string s);
    std::string RightTrim(std::string s);
    std::string Trim(std::string s);
    std::vector<std::string> SplitText(std::string str, std::string delimiter = "\n");
    std::string ToLower(std::string s);

    struct ParsedData
    {
        std::map<std::string, Color> colors;
        std::map<std::string, Material> materials;
        unsigned int lineNumber = 0;
        std::vector<std::string> errors;

        void CreateError(std::string error = "Unknown Error");
        void CreateError(const char* error = "Unknown Error");
    };

    typedef void ParseFunction(std::vector<std::string> line, Scene& scene, ParsedData& data);

    void ParseCamera(std::vector<std::string> line, Scene& scene, ParsedData& data);
    void ParseColor(std::vector<std::string> line, Scene& scene, ParsedData& data);
    void ParseMaterial(std::vector<std::string> line, Scene& scene, ParsedData& data);
    void ParseBackground(std::vector<std::string> line, Scene& scene, ParsedData& data);
    void ParseSphere(std::vector<std::string> line, Scene& scene, ParsedData& data);
    void ParseLight(std::vector<std::string> line, Scene& scene, ParsedData& data);
    void ParsePlane(std::vector<std::string> line, Scene& scene, ParsedData& data);

    const inline std::map<std::string, ParseFunction*> ParseFunctions
    {
        {"camera", &ParseCamera},
        {"color", &ParseColor},
        {"material", &ParseMaterial},
        {"background", &ParseBackground},
        {"sphere", &ParseSphere},
        {"light", &ParseLight},
        {"plane", &ParsePlane},
    };

    void ParseLine(std::string line, Scene& scene, ParsedData& data);
    ParsedData ParseScene(std::string str, Scene& scene);
};
