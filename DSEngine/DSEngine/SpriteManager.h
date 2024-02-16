#pragma 
#include "ResourceManager.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "Shader.h"
#include "DSCore.h"
#include <map>
#include <memory>
#include <string>

struct Sprite {
    Texture2D* Texture;
    std::vector<std::shared_ptr<SpriteComponent>> Comps;
    std::vector<glm::mat4> Positions;
    unsigned int Amount;
    unsigned int VAO;
};

class SpriteManager
{
private:
    unsigned int VBO, EBO;
    Shader* m_Shader;

    std::map<std::string, Sprite> m_Sprites;

public:
    unsigned int VAO;

    SpriteManager() {}
    SpriteManager(Shader* shader);
    void Initialize();
    std::shared_ptr<SpriteComponent> CreateSprite(Entity* entity, std::string texture, bool alpha);
    void Draw();
    void Destroy();
};

