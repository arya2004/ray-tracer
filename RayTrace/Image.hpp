//
// Created by ziegler on 10/10/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_IMAGE_HPP
#define TRAY_RACING_COMPUTER_GRAPHICS_IMAGE_HPP

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class Image
{
    public:
    //ctor
    Image();

    //dtor
    ~Image();

    //init
    void Initialize(const int xSize, const int ySIze, SDL_Renderer *pRenderer);

    //set color
    void SetPixel(const int x, const int y, const double red, const double  blue, const double green);

    //display image
    void Display();

    //func to return dim of image
    int GetXSize();
    int GetYSize();

    private:
        Uint32 ConvertColor(const double red, const double green, const double blue);
        void InitTexture();
    private:
        //store img data
        std::vector<std::vector<double>> m_rChannel;
        std::vector<std::vector<double>> m_gChannel;
        std::vector<std::vector<double>> m_bChannel;

        //store dim
        int m_xSize, m_ySize;

        //sdl
        SDL_Renderer *m_pRenderer;
        SDL_Texture *m_pTexture;
};

#endif //TRAY_RACING_COMPUTER_GRAPHICS_IMAGE_HPP
