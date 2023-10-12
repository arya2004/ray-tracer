//
// Created by ziegler on 10/10/23.
//

#include "Image.hpp"

Image::Image() {
    m_xSize = 0;
    m_ySize = 0;
    m_pTexture = NULL;

}
Image::~Image() {
    if(m_pTexture != NULL){
        SDL_DestroyTexture(m_pTexture);
    }

}

void Image::Initialize(const int xSize, const int ySIze, SDL_Renderer *pRenderer) {
    //resize img arr
    m_rChannel.resize(xSize, std::vector<double>(ySIze,0.0));
    m_gChannel.resize(xSize, std::vector<double>(ySIze,0.0));
    m_bChannel.resize(xSize, std::vector<double>(ySIze,0.0));

    //store dimention
    m_xSize = xSize;
    m_ySize = ySIze;

    //store renderer

    m_pRenderer = pRenderer;

    //init texture
    InitTexture();

}

void Image::SetPixel(const int x, const int y, const double red, const double blue, const double green) {
    m_rChannel.at(x).at(y) = red;
    m_gChannel.at(x).at(y) = green;
    m_bChannel.at(x).at(y) = blue;
}


int Image::GetXSize(){
    return m_xSize;
}

int Image::GetYSize(){
    return m_ySize;
}


//display image to renderer

void Image::Display() {
    //alloc memory for pixel buffer
    Uint32 * tempPixel = new Uint32[m_xSize * m_ySize];

    //Clear buffer
    memset(tempPixel, 0, m_xSize * m_ySize * sizeof(Uint32));
    for (int i = 0; i < m_xSize; ++i) {
        for (int j = 0; j < m_ySize; ++j) {
            tempPixel[(j * m_xSize) + i] = ConvertColor(m_rChannel.at(i).at(j), m_gChannel.at(i).at(j), m_bChannel.at(i).at(j));
        }
    }

    //update texture with pixel buffer
    SDL_UpdateTexture(m_pTexture, NULL, tempPixel, m_xSize * sizeof(Uint32));

    //delete buffer
    delete[] tempPixel;

    //copy texture to renderer
    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_xSize;
    srcRect.h = m_ySize;
    bounds = srcRect;
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);

}

void Image::InitTexture() {
    //init texture
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    //delete any prev texture
    if(m_pTexture != NULL){
        SDL_DestroyTexture(m_pTexture);
    }

    SDL_Surface * tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
      
}

//
Uint32 Image::ConvertColor(const double red, const double green, const double blue) {
    unsigned char r = static_cast<unsigned char>(red);
    unsigned char g = static_cast<unsigned char>(green);
    unsigned char b = static_cast<unsigned char>(blue);

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
    #else
        Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
    #endif
        return pixelColor;
}