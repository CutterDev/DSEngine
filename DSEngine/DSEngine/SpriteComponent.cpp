#include "SpriteComponent.h"
void SpriteComponent::Startup(const char* path, bool alpha, std::string shader, int maxAmount)
{
    // Create new Texture was not found.
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // load image
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data)
    {
        m_Texture.Internal_Format = GL_RGBA;
        m_Texture.Image_Format = GL_RGBA;
        // now generate texture
        m_Texture.Generate(width, height, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // and finally free image data
    stbi_image_free(data);

    m_Shader.Startup((shader + ".vs").c_str(), (shader + ".fs").c_str());

    m_MaxAmount = maxAmount;
    Transforms.Data.resize(maxAmount, glm::mat4(1.f));
    Colors.Data.resize(maxAmount, glm::vec3(1.f));

}

void SpriteComponent::Initialize()
{
    m_Shader.Use();
    m_Shader.SetInt("sprite", 1);

    unsigned int VBO;
    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, -1.f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, -1.f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, -1.f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, -1.f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle 
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &DataBuffer);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Vertex 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    this->Bind();
    this->AllocateMemory();

    size_t vec4Size = sizeof(glm::vec4);
    size_t transformSize = (vec4Size * 4) * Transforms.Data.size();

    // Color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(2);

    // Transforms
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(Colors.Size()));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(Colors.Size() + (1 * vec4Size)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(Colors.Size() + (2 * vec4Size)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(Colors.Size() + (3 * vec4Size)));
    glEnableVertexAttribArray(7);

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glVertexAttribDivisor(7, 1);

    glBindVertexArray(0);
}

/// <summary>
/// Only use this before the List has been initialized
/// TODO: Make a method for adding a new instance after the Buffers have been allocated
/// </summary>
void SpriteComponent::AddNewInstance(unsigned int entityId, glm::mat4 transform, glm::vec3 color)
{
    InstanceIndex[entityId] = m_Amount;

    Transforms.Data[m_Amount] = transform;
    Colors.Data[m_Amount] = color;

    m_Amount++;
}

void SpriteComponent::UpdateTransform(unsigned int entityId, glm::mat4 transform)
{
    if (InstanceIndex.find(entityId) != InstanceIndex.end())
    {
        int index = InstanceIndex[entityId];

        Transforms.Data[index] = transform;

        Transforms.HasUpdated = true;
    }
}

void SpriteComponent::RemoveInstance(unsigned int entityId)
{
    std::map<unsigned int, int>::iterator it = InstanceIndex.find(entityId);
    if (it != InstanceIndex.end())
    {
        int index = InstanceIndex[entityId];

        Transforms.Data.erase(Transforms.Data.begin() + index);
        Colors.Data.erase(Colors.Data.begin() + index);
        InstanceIndex.erase(it);

        Transforms.Data.push_back(glm::mat4(1.0f));
        Colors.Data.push_back(glm::vec3(1.f));

        for (std::map<unsigned int, int>::iterator it = InstanceIndex.begin(); it != InstanceIndex.end(); ++it)
        {
            it->second--;
        }

        m_Amount--;
    }
}


void SpriteComponent::Draw(glm::mat4 projection, glm::mat4 view)
{
    if (m_Amount > 0)
    {
        CheckForUpdates();

        glActiveTexture(GL_TEXTURE1);
        m_Shader.Use();

        m_Texture.Bind();

        m_Shader.SetMat4("projection", projection);

        m_Shader.SetMat4("view", view);

        glBindVertexArray(VAO);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_Amount);
        glBindVertexArray(0);
    }
}

void SpriteComponent::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, DataBuffer);
}

void SpriteComponent::CheckForUpdates()
{
    this->Bind();
    if (Transforms.HasResized || Colors.HasResized)
    {
        this->AllocateMemory();
    }
    else if (Transforms.HasUpdated)
    {
        this->UpdateTransforms();
    }
    else if (Colors.HasUpdated)
    {
        this->UpdateColors();
    }
}

void SpriteComponent::AllocateMemory()
{
    size_t vec4Size = sizeof(glm::vec4);
    size_t transformSize = (vec4Size * 4) * Transforms.Data.size();
    glBufferData(GL_ARRAY_BUFFER, Colors.Size() + transformSize, NULL, GL_STATIC_DRAW);

    this->UpdateColors();

    this->UpdateTransforms();
}

void SpriteComponent::UpdateColors()
{
    glBufferSubData(GL_ARRAY_BUFFER, 0, Colors.Size(), &Colors.Data[0]);
    Colors.ResetFlags();
}

void SpriteComponent::UpdateTransforms()
{
    size_t vec4Size = sizeof(glm::vec4);
    size_t transformSize = (vec4Size * 4) * Transforms.Data.size();

    glBufferSubData(GL_ARRAY_BUFFER, Colors.Size(), transformSize, &Transforms.Data[0]);
    Transforms.ResetFlags();
}

void SpriteComponent::Destroy()
{
    
}