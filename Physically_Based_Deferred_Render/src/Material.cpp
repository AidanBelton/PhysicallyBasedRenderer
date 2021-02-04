#include "Material.h"

MaterialManager::MaterialManager()
{

}
bool MaterialManager::Initialize(ShaderManager* SM,TextureManager* TM,CameraManager* CM)
{
    ShaderMgr = SM;
    TextureMgr = TM;
    CameraMgr = CM;
    return true;
}
MaterialManager::~MaterialManager()
{

}
Material* MaterialManager::GetMaterial(string Name)
{

}
