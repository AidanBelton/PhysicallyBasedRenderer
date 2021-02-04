#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#include <gl/glew.h>
#include <SDL2/SDL.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Material.h"
#include "ObjectManager.h"
#include "Framebuffer.h"
#include "stdint.h"
using namespace std;

class RenderSystem
{
    public:
        RenderSystem(const char* SF);
        virtual ~RenderSystem();
        bool Initialize();
        bool RenderFrame();

        CameraManager* GetCameraManager() {return &CameraMgr;}

        void GeometryPass();
        void LightingPass();
        TextureManager TextureMgr;
        ShaderManager ShaderMgr;
        CameraManager CameraMgr;
        MaterialManager MaterialMgr;
        ObjectManager ObjectMgr;
        SDL_GLContext Context;
        SDL_Window* Window;
        int ResX, ResY;
        mat4 Ortho;
        GBuffer* GeometryBuffer;
        Mesh* Test;
};
#endif // RENDERSYSTEM_H
