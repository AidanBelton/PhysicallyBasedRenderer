#ifndef CAMERA_H
#define CAMERA_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
using namespace std;
using namespace glm;

class Camera
{
    public:
        Camera(float F):FOV(F) {};
        virtual ~Camera();
        inline void SetPosition(vec3 P) {Pos = P;}
        inline void SetRotation(vec3 R) {Rot = R;}
        inline void SetFOV(float F) {FOV = F;}
        vec3 GetPosition() const{return Pos;}
        vec3 GetRotation() const{return Rot;}
        float GetFOV() const{return FOV;}
    private:
        vec3 Pos = vec3(0,0,0),Rot = vec3(0,0,0);
        float FOV;
};

class CameraManager
{
    public:
        CameraManager();
        void Initialize(float,float,int,int);
        void SetCurrentCamera(Camera*);
        Camera* GetCurrentCamera() const{return CurrentCamera;}
        Camera* GetDefaultCamera() {return &DefaultCamera;}
        void Update();
        void SetResolution(int,int);
        mat4 GetViewMatrix() const{return ViewMatrix;}
        mat4 GetPerspectiveMatrix() const{return PerspectiveMatrix;}
        mat4 GetOrthoMatrix() const{return ortho(0.0f,ResX,0.0f,ResY,Near,Far);}
    private:
        float Near, Far;
        float ResX, ResY, AspectRatio;
        mat4 ViewMatrix, PerspectiveMatrix;
        vec3 ViewPos;
        Camera* CurrentCamera;
        Camera DefaultCamera;
};
#endif // CAMERA_H
