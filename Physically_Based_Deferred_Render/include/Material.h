#ifndef MATERIAL_H
#define MATERIAL_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include "Shader.h"
#include "TextureManager.h"
#include "Camera.h"

class Material
{
    public:
        Material(CameraManager*,Shader*,string);
        virtual ~Material();
        void ApplyAttributes(mat4);
    private:
        CameraManager* CamMgr;
        Shader* Sha;
        string Name;
};

class MaterialManager
{
    public:
        MaterialManager();
        bool Initialize(ShaderManager*,TextureManager*,CameraManager*);
        ~MaterialManager();
        Material* GetMaterial(string);
    private:
        TextureManager* TextureMgr;
        ShaderManager* ShaderMgr;
        CameraManager* CameraMgr;
        vector<Material> Mat;
};

#endif // MATERIAL_H
