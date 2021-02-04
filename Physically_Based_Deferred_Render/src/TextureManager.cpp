#include "TextureManager.h"

Texture::Texture(TexInfo I, GLuint ID)
:Info(I), Texture_ID(ID)
{

}

Texture::~Texture()
{
    glDeleteTextures(1, &Texture_ID);
}

////////////////////////////////////////////////////////////////////////////////

ActiveTexture::ActiveTexture(TexInfo I, GLuint ID, GLenum Act)
:Texture(I, ID), ActiveSlot(Act)
{
    ActiveNumber = static_cast<int>(ActiveSlot-GL_TEXTURE0);
    cout << "ActiveNumber:" << ActiveNumber << endl;
}

////////////////////////////////////////////////////////////////////////////////

TextureManager::TextureManager()
{}

TextureManager::~TextureManager()
{
    for(unsigned int i = 0; i < Textures.size(); ++i)
    {
        delete Textures[i];
    }
}

bool TextureManager::Initalize()
{
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MaxTextureUnits);
    glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &MaxTextureLayers);

    cout << "Max array texture layers is " << MaxTextureLayers << endl;

    if(MaxTextureUnits == 0 || MaxTextureLayers == 0)
        return false;

    for(int i = 0; i < MaxTextureUnits; ++i)
    {
        FreeActiveTexSlots.push(GL_TEXTURE0+i);
    }

    return true;
}

ActiveTexture* TextureManager::CreateActiveTexture2d(TexInfo In)
{
    GLuint ID;
    glGenTextures(1, &ID);
    cout << "Texture ID::" << ID << endl;
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(In.Target, In.Level, In.InternalFormat, In.Width, In.Height, In.Border, In.Format, In.Type, In.Data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //define filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //define filters
    ActiveTexture* Tex = new ActiveTexture(In,ID,FreeActiveTexSlots.front());
    FreeActiveTexSlots.pop();
    Textures.push_back(Tex);
    return Tex;
}

