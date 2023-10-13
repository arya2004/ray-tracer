//
// Created by ziegler on 10/10/23.
//

#include "CApp.h"
#include "./RayTrace/qbLinAlg/qbVector.h"

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

        //test camera class
        RT::Camera testCamera;
        testCamera.SetPosition(qbVector<double>(std::vector<double>{0.0,0.0,0.0}));
        testCamera.SetLookAt(qbVector<double>(std::vector<double>{0.0,2.0, 0.0}));
        testCamera.SetUp(qbVector<double>(std::vector<double>{0.0,0.0,1.0}));
        testCamera.SetLength(1.0);
        testCamera.SetHorizontalSize(1.0);
        testCamera.SetAspect(1.0);
        testCamera.UpdateCameraGeometry();

        //get screen centre an u,v vector and display
        auto screenCentre = testCamera.GetScreenCentre();
        auto screenU = testCamera.GetU();
        auto screenV = testCamera.GetV();

        //display
        std::cout << "\nCamera screen cnetre" << std::endl;
        PrintVector(screenCentre);
        std::cout << "\nCamera U vector" << std::endl;
        PrintVector(screenU);
        std::cout << "\nCamera v vec" << std::endl;
        PrintVector(screenV);

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

//private func

void CApp::PrintVector(const qbVector<double> &inputVector) {
    int nRows = inputVector.GetNumDims();
    for (int row = 0; row < nRows; ++row) {
        std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
    }
}