#include "ObjectManager.h"

ObjectManager::ObjectManager()
{}

ObjectManager::~ObjectManager()
{

}
bool ObjectManager::Intitialize(CameraManager* CM,MaterialManager* MM)
{
    CamMgr = CM;
    MatMgr = MM;
    NewMesh();
    return true;
}

void ObjectManager::NewMesh()
{
    MeshDataContainer Container;

    MeshContainers.push_back(Container);
}

Mesh* ObjectManager::CreateMesh()
{
    MeshObjects.push_back(new Mesh("Cube",&MeshContainers.front()));
    return MeshObjects.front();
}

void ObjectManager::Draw()
{
    MeshObjects.front()->Draw();
}
