#include "Framebuffer.h"


//////////////////////////////////////////////////////////////////////////////////////////////////
GBuffer::GBuffer(TextureManager* TMgr,int X,int Y)
:TextureMgr(TMgr), ResX(X), ResY(Y)
{

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    GLfloat Data[]{
    float(ResX), float(ResY), -1,
    float(ResX), 0,    -1,
    0,    0,    -1,
    0,    float(ResX), -1
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(Data), Data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    GLfloat TexData[]{
    1,1,
    1,0,
    0,0,
    0,1
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexData), TexData, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 0, 0);

    glGenFramebuffers(1, &Framebuffer_ID);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &DepthBuffer);
    glBindTexture(GL_TEXTURE_2D, DepthBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, ResX, ResY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &AlbedoTexture);
    glBindTexture(GL_TEXTURE_2D, AlbedoTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, ResX, ResY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

GBuffer::~GBuffer()
{
    glDeleteTextures(1, &DepthBuffer);
    glDeleteTextures(1, &AlbedoTexture);
}

void GBuffer::BindTextures()
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthBuffer, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, AlbedoTexture, 0);
    GLenum DrawBuffers[] = { GL_NONE ,GL_COLOR_ATTACHMENT0};
    glDrawBuffers(2,DrawBuffers);
}

void GBuffer::UnBindTextures()
{
}

void GBuffer::DrawScreen()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_QUADS, 0, 4);
}

////////////////////////////////////////////////////////////////////////

