#ifndef MESH_H
#define MESH_H
#include "gl/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include <iostream>
using namespace glm;
using namespace std;

class MeshData
{
    public:
        MeshData();
        virtual ~MeshData();
        void LoadGPUData();
        void LoadCPUData();
        void DeleteGPUData();
        void DeleteCPUData();
        void Draw(); //last but not least
    private:
        vec3 *V, *N;
        vec2 *T;
        GLuint VAO;
        GLuint VBO[3];
};

class MeshDataContainer
{
    public:
        MeshDataContainer();
        inline void Draw() {Data->Draw();}
    private:
        MeshData* Data;
};

class Mesh
{
    public:
        Mesh(string, MeshDataContainer*);
        vec3 GetPosition() const{return Position;}
        vec3 GetRotation() const{return Rotation;}
        vec3 GetScale() const{return Scale;}
        void Draw();
    private:
        string File;
        MeshDataContainer* Container;
        vec3 Position, Rotation, Scale;
};

#endif // MESH_H
