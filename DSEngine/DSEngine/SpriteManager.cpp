#include "SpriteManager.h"

//// prepare transformations


SpriteManager::SpriteManager(Shader* shader)
{
    m_Shader = shader;

    m_Shader->Use();
    m_Shader->SetInt("sprite", 0);
}

void SpriteManager::Initialize()
{
    float vertices[] = {
     0.5f,  0.5f,  1.0f, 1.0f,// top right
     0.5f, -0.5f,  1.0f, 0.0f,// bottom right
    -0.5f, -0.5f,  0.0f, 0.0f,// bottom left
    -0.5f,  0.5f,   0.0f, 1.0f// top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    for (std::map<std::string, Sprite>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
    {
        for (unsigned int i = 0; i < it->second.Comps.size(); i++)
        {
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glBindVertexArray(0);

            it->second.Positions[i] = it->second.Comps[i]->Model;
        }

        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER,
            it->second.Comps.size() * sizeof(glm::mat4),
            &it->second.Positions[0],
            GL_STATIC_DRAW);

        for (unsigned int i = 0; i < it->second.Comps.size(); i++)
        {
            glBindVertexArray(VAO);
            // vertex attributes
            std::size_t vec4Size = sizeof(glm::vec4);
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

            glVertexAttribDivisor(2, 1);
            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);

            glBindVertexArray(0);
        }

        it->second.Amount = it->second.Comps.size();
    }

}

std::shared_ptr<SpriteComponent> SpriteManager::CreateSprite(Entity* entity, std::string texture, bool alpha)
{
    if (m_Sprites.find(texture) == m_Sprites.end())
    {
        Texture2D* spriteTex = ResourceManager::GetInstance().GetTexture(texture, alpha);

        Sprite sprite = {
            spriteTex
        };


        sprite.Comps.push_back(std::shared_ptr< SpriteComponent>(new SpriteComponent(entity)));

        m_Sprites[texture] = sprite;
    }
    else
    {
        m_Sprites[texture].Comps.push_back(std::shared_ptr<SpriteComponent>(new SpriteComponent(entity)));
    }

    m_Sprites[texture].Positions.push_back(glm::mat4());
    m_Sprites[texture].Comps.back()->SpriteShader = m_Shader;
    return m_Sprites[texture].Comps.back();
}

void SpriteManager::Draw()
{

    glBindVertexArray(VAO);
    for (const auto& sprite : m_Sprites)
    {
        for (int i = 0; i < 100000; i++)
        {
            glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(0), 100000);
            glBindVertexArray(0);
        }
    }
}

void SpriteManager::Destroy()
{
    for (const auto& sprite : m_Sprites)
    {
        for (std::shared_ptr<SpriteComponent> comp : sprite.second.Comps)
        {
            glDeleteVertexArrays(1, &comp->VAO);
        }
    }
}
