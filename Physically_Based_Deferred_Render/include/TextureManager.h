#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "gl/glew.h"
#include "stdint.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct TexInfo
{
    TexInfo() {};
    TexInfo(GLint L, GLint IF, GLsizei X, GLsizei Y, GLenum Form, GLenum Ty)
    :Level(L),InternalFormat(IF), Width(X), Height(Y), Format(Form), Type(Ty)
    {};
    GLenum Target = GL_TEXTURE_2D;
    GLint Level, InternalFormat;
    GLsizei Width, Height, Depth = 0;
    GLint Border = 0;
    GLenum Format;
    GLenum Type;
    const GLvoid* Data = NULL;
};

class Texture
{
    public:
        Texture(TexInfo, GLuint);
        virtual ~Texture();
        virtual GLenum GetActiveSlot() const{return 0;}
        virtual int GetActiveNumber() const{return 0;}

        //Getters
        TexInfo GetTextureInfo() const{return Info;}
        GLenum GetTarget() const{return Info.Target;}
        GLint GetLevel() const{return Info.Level;}
        GLint GetInternalFormat() const{return Info.InternalFormat;}
        GLint GetWidth() const{return Info.Width;}
        GLint GetHeight() const{return Info.Height;}
        bool IsSquare() const{return (Info.Width==Info.Height) ? true:false;}
        GLint GetBorder() const{return Info.Border;}
        GLenum GetFormat() const{return Info.Format;}
        GLenum GetType() const{return Info.Type;}
        GLuint GetTexture_ID() const{return Texture_ID;}
        //
    private:
        TexInfo Info;
        GLuint Texture_ID;
};

class ActiveTexture: public Texture
{
    public:
        ActiveTexture(TexInfo, GLuint, GLenum);
        GLenum GetActiveSlot() const{return ActiveSlot;}
        int GetActiveNumber() const{return ActiveNumber;}
    private:
        GLenum ActiveSlot;
        int ActiveNumber;
};

class  TextureArray: public Texture
{
    public:
        TextureArray(TexInfo);
    private:
};

class TextureManager
{
    public:
        TextureManager();
        virtual ~TextureManager();
        bool Initalize();
        ActiveTexture* CreateActiveTexture2d(TexInfo);
    private:
        GLint MaxTextureUnits, MaxTextureLayers;
        queue<GLenum> FreeActiveTexSlots;
        vector<Texture*> Textures;
};

#endif // TEXTUREMANAGER_H
