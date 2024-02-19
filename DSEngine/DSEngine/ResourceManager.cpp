#include "ResourceManager.h"
Texture2D ResourceManager::GetTexture(std::string filepath, bool alpha)
{
    if (m_Textures.find(filepath) == m_Textures.end())
    {
        // Create new Texture was not found.
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        // load image
        int width, height, nrChannels;
        unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

        if (data)
        {
            Texture2D tex = Texture2D();

            if (alpha)
            {
                tex.Internal_Format = GL_RGBA;
                tex.Image_Format = GL_RGBA;
            }

            // now generate texture
            tex.Generate(width, height, data);

            m_Textures[filepath] = tex;
            return m_Textures[filepath];
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        // and finally free image data
        stbi_image_free(data);

    }
    else
    {
        return m_Textures[filepath];
    }
}

ResourceManager::~ResourceManager()
{
    for (const auto texture : m_Textures)
    {
        glDeleteTextures(1, &texture.second.ID);
    }
}
