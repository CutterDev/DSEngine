#pragma once

#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include "Texture2D.h"

#include "stb_image.h"


/// <summary>
/// Handles the Textures and any resource retrieving.
/// </summary>
class ResourceManager
{
private:
    ResourceManager() {}                    // Constructor? (the {} brackets) are needed here.
    std::map<std::string, Texture2D> m_Textures;
public:
    static ResourceManager& GetInstance()
    {
        static ResourceManager instance;
        return instance;
    }
    ResourceManager(ResourceManager const&) = delete;
    void operator=(ResourceManager const&) = delete;

    Texture2D* GetTexture(std::string filepath, bool alpha);
};

