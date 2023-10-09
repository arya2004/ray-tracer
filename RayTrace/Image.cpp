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