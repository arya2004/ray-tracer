//
// Created by ziegler on 10/10/23.
//

#include "CApp.h"

CApp::CApp() {
    isRunning = true;
    pWindow = NULL;
    pRenderer = NULL;
}
//ctor only dtor handled elsewhere

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }
    pWindow = SDL_CreateWindow("Ziegler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);
    if(pWindow != NULL)
    {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
        //init Image instance
        m_image.Initialize(1000,1000, pRenderer);


    }
    else
    {
        return false;
    }
    return true;

}

int CApp::OnExecute()
{
    SDL_Event event;
    if(OnInit() == false)
    {
        return -1;
    }
    while(isRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }
}

void CApp::OnEvent(SDL_Event *event) {
    if(event->type == SDL_QUIT)
    {
        isRunning = false;
    }
}


void CApp::OnLoop() {

}

void CApp::OnRender() {
    //set background color
    SDL_SetRenderDrawColor(pRenderer, 255, 255,255,255);
    SDL_RenderClear(pRenderer);

    //render scene
    m_Scene.Render(m_image);

    //display image
    m_image.Display();

    //display result
    SDL_RenderPresent(pRenderer);
}

void CApp::OnExit()
{
    //dtor
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    SDL_Quit();
}