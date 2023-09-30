#include "Material.h"
void Material::Use(const GameCamera* camera, const glm::mat4 &gameObject) const
{
    if (Shader != NULL)
    {
        Shader->Use();

        Shader->SetVec3("material.ambient", Ambient);
        Shader->SetVec3("material.diffuse", Diffuse);
        Shader->SetVec3("material.specular", Specular);
        Shader->SetFloat("material.shininess", Shininess);
        Shader->SetMat4("model", gameObject);
        Shader->SetMat4("view", camera->View);
        Shader->SetMat4("projection", camera->Projection);
    }
}