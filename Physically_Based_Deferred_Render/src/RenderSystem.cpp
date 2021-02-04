#include "RenderSystem.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RenderSystem::RenderSystem(const char* SF)
:ShaderMgr(SF)
{
}

RenderSystem::~RenderSystem()
{
    SDL_GL_DeleteContext(Context);
}

bool RenderSystem::Initialize()
{
    ResX = 1366; ResY = 768;
    Window = SDL_CreateWindow("DeadEnd",0,0,ResX,ResY,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_FULLSCREEN);
    Context = SDL_GL_CreateContext(Window);

    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        cout << err << endl;
        return false;
    }

    if(!TextureMgr.Initalize())
        return false;

    if(!ShaderMgr.Initialize())
        return false;

    if(!MaterialMgr.Initialize(&ShaderMgr,&TextureMgr,&CameraMgr))
        return false;

    if(!ObjectMgr.Intitialize(&CameraMgr, &MaterialMgr))
        return false;

    GeometryBuffer = new GBuffer(&TextureMgr,ResX,ResY);

    CameraMgr.Initialize(0.001,10,ResX,ResY);
    Ortho = CameraMgr.GetOrthoMatrix();
    Test = ObjectMgr.CreateMesh();

    return true;
}

void RenderSystem::GeometryPass()
{
    Shader* S = ShaderMgr.GetShader("Basic");
    mat4 P = CameraMgr.GetPerspectiveMatrix() * CameraMgr.GetViewMatrix();

    GeometryBuffer->BindFramebuffer();
    GeometryBuffer->BindTextures();

    glViewport(0,0,ResX,ResY);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    S->Uniform("MVP",P);
    S->UseProgram();
    ObjectMgr.Draw();
}

void RenderSystem::LightingPass()
{
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    GeometryBuffer->UnbindFramebuffer();
    GeometryBuffer->UnBindTextures();

    Shader* S = ShaderMgr.GetShader("Display");
    mat4 P = CameraMgr.GetOrthoMatrix();
    S->Uniform("MVP", P);
    int I = 0;
    S->Uniform("Albedo", I);
    S->UseProgram();
    GeometryBuffer->DrawScreen();
}

bool RenderSystem::RenderFrame()
{
    cout << "Updating Camera\n";
    CameraMgr.Update();
    cout << "Geometry Pass\n";
    GeometryPass();
    cout << "Lighting Pass\n";
    LightingPass();
    SDL_GL_SwapWindow(Window);
    cout << "Display Frame\n";
    return true;
}
