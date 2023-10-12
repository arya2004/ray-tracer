//
// Created by ziegler on 10/10/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_CAPP_H
#define TRAY_RACING_COMPUTER_GRAPHICS_CAPP_H

#include <SDL2/SDL.h>
#include "./RayTrace/Image.hpp"
#include "./RayTrace/Scene.hpp"
class CApp
{
    public:
        CApp();
        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event *event);
        void OnLoop();
        void OnRender();
        void OnExit();

    private:
        //an instance of Image class to store image
        Image m_image;
        //an instance of schene class to store image
        RT::Scene m_Scene;
        //sdl things
        bool isRunning;
        SDL_Window *pWindow;
        SDL_Renderer *pRenderer;


};

#endif //TRAY_RACING_COMPUTER_GRAPHICS_CAPP_H
