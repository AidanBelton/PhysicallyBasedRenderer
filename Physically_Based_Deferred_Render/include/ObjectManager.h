#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include <iostream>
using namespace std;

class ObjectManager
{
    public:
        ObjectManager();
        ~ObjectManager();
        bool Intitialize(CameraManager*,MaterialManager*);
        Mesh* CreateMesh();
        void Draw();
        void NewMesh();
    private:
        CameraManager* CamMgr;
        MaterialManager* MatMgr;
        vector<MeshDataContainer> MeshContainers;
        vector<Mesh*> MeshObjects;
};

#endif // OBJECTMANAGER_H
