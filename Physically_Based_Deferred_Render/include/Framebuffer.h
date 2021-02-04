#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "TextureManager.h"

class GBuffer
{
    public:
        GBuffer(TextureManager*,int,int);
        virtual ~GBuffer();
        void BindTextures();
        void UnBindTextures();
        void DrawScreen();
        inline void BindFramebuffer() {glBindFramebuffer(GL_DRAW_FRAMEBUFFER, Framebuffer_ID);}
        inline void UnbindFramebuffer() {glBindFramebuffer(GL_FRAMEBUFFER, 0);}
    private:
        TextureManager* TextureMgr;
        int ResX,ResY;
        GLuint VAO, VBO[2];

        GLuint DepthBuffer, AlbedoTexture;
        GLuint Framebuffer_ID;
};

#endif // FRAMEBUFFER_H
