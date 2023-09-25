#include "MeshNode.h"
void MeshNode::Update(GameCamera* camera)
{
    Material->Use(camera, GameObject->GetTransform());
    MeshFilter->Draw();
}
