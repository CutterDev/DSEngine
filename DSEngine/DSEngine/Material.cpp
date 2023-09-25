#include "Material.h"
void Material::Use(const GameCamera* camera, const glm::mat4 &gameObject) const
{
    if (Shader != NULL)
    {
        Shader->Use();

        Shader->SetVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        Shader->SetVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        Shader->SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
        Shader->SetFloat("material.shininess", 0.32f);
        Shader->SetMat4("model", gameObject);
        Shader->SetMat4("view", camera->View);
        Shader->SetMat4("projection", camera->Projection);
    }
}