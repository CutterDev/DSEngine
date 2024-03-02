#include "Sprite.h"

void Sprite::Startup(const char* path, bool alpha, std::string shader)
{
    // Create new Texture was not found.
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // load image
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data)
    {
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
}

void Sprite::Initialize()
{
    m_Shader.Use();
    m_Shader.SetInt("sprite", 1);

    unsigned int VBO;
    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.f,   0.0f, 1.0f    // top left 
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

    glBindBuffer(GL_ARRAY_BUFFER, DataBuffer);

    size_t posSize = sizeof(glm::vec3) * Positions.size();
    size_t colorSize = sizeof(glm::vec3) * Colors.size();
    size_t scaleSize = sizeof(glm::vec2) * Scales.size();
    size_t rotSize = sizeof(float) * Rotations.size();
 
    glBufferData(GL_ARRAY_BUFFER, posSize + colorSize + scaleSize + rotSize, NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, posSize, &Positions[0]);
    glBufferSubData(GL_ARRAY_BUFFER, posSize, colorSize, &Colors[0]);
    glBufferSubData(GL_ARRAY_BUFFER, posSize + colorSize, scaleSize, &Scales[0]);
    glBufferSubData(GL_ARRAY_BUFFER, posSize + colorSize + scaleSize, rotSize, &Rotations[0]);

    // Position
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(2);

    // Color
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)posSize);
    glEnableVertexAttribArray(3);

    // Scale
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(posSize + colorSize));
    glEnableVertexAttribArray(4);

    // Rotation
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)(posSize + colorSize + scaleSize));
    glEnableVertexAttribArray(5);

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glBindVertexArray(0);
}

void Sprite::AddNewInstance(unsigned int entityId, glm::vec3 pos, glm::vec2 scale, glm::vec3 color, float rotation)
{
    InstanceIndex[entityId] = Amount;
    Positions.push_back(pos);
    Colors.push_back(color);
    Scales.push_back(scale);
    Rotations.push_back(rotation);
    Amount++;
}

void Sprite::UpdatePosition(unsigned int entityId, glm::vec3 pos)
{
    if (InstanceIndex.find(entityId) != InstanceIndex.end())
    {
        int index = InstanceIndex[entityId];

        Positions[index] = pos;

        glBindBuffer(GL_ARRAY_BUFFER, DataBuffer);

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * Positions.size(), &Positions[0]);
    }
}

void Sprite::Draw(glm::mat4 projection, glm::mat4 view)
{
    if (Amount > 0)
    {
        m_Shader.Use();
        glActiveTexture(GL_TEXTURE1);

        m_Texture.Bind();

        m_Shader.SetMat4("projection", projection);

        m_Shader.SetMat4("view", view);

        glBindVertexArray(VAO);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, Amount);
        glBindVertexArray(0);
    }
}

void Sprite::Destroy()
{
    
}