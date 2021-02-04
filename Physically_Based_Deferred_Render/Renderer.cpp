#include <iostream>
#include <gl/glew.h>
#include <gl/glew.c>
#include "RenderSystem.h"
#include "Camera.h"
#include "gli/gli.hpp"
#include "stdint.h"
#undef main
using namespace std;

int main()
{
    RenderSystem RendSyst("Shaders.mgr");
    if(!RendSyst.Initialize())
    {
        cout << "Initialization failed\n";
        return -1;
    }
    Camera* Cam = RendSyst.CameraMgr.GetDefaultCamera();

    bool Close;
    while(!Close)
    {
        SDL_Event Event;
        while(SDL_PollEvent(&Event))
        {
            switch(Event.type)
            {
            case SDL_KEYDOWN:
                switch(Event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    Close=true;
                    break;
                case SDLK_w:
                    Cam->SetPosition(Cam->GetPosition()-vec3(0,0,0.01));
                    break;
                case SDLK_s:
                    Cam->SetPosition(Cam->GetPosition()+vec3(0,0,0.01));
                    break;
                case SDLK_d:
                    Cam->SetPosition(Cam->GetPosition()+vec3(0.01,0,0));
                    break;
                case SDLK_a:
                    Cam->SetPosition(Cam->GetPosition()-vec3(0.01,0,0));
                    break;
                case SDLK_SPACE:
                    Cam->SetPosition(Cam->GetPosition()-vec3(0.0,0.01,0.0));
                    break;
                case SDLK_z:
                    Cam->SetPosition(Cam->GetPosition()+vec3(0.0,0.01,0.0));
                }
            }
        }
        RendSyst.RenderFrame();
    }

    return 0;
}
