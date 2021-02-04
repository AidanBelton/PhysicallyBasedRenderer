#include "Camera.h"
Camera::~Camera()
{
    //dtor
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CameraManager::CameraManager()
:DefaultCamera(1)
{
}

void CameraManager::Initialize(float N,float F,int X,int Y)
{
    ResX = float(X);
    ResY = float(Y);
    AspectRatio = ResX/ResY;
    Near = N;
    Far = F;
    DefaultCamera.SetPosition((vec3(0,0,3)));
    CurrentCamera = &DefaultCamera;
}

void CameraManager::SetCurrentCamera(Camera* Cam)
{
    CurrentCamera=Cam;
}

void CameraManager::SetResolution(int X, int Y)
{
    ResX = float(X);
    ResY = float(Y);
    AspectRatio = ResX/ResY;
}

void CameraManager::Update()
{
    ViewPos = CurrentCamera->GetPosition();
    ViewMatrix = translate(mat4(1), ViewPos * vec3(-1,-1,-1));
    PerspectiveMatrix = perspective(CurrentCamera->GetFOV(),AspectRatio,Near,Far);
}
