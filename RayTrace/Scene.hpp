//
// Created by ziegler on 10/13/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_SCENE_HPP
#define TRAY_RACING_COMPUTER_GRAPHICS_SCENE_HPP

#include <vector>
#include <SDL2/SDL.h>
#include "Image.hpp"

namespace RT
{
    class Scene
    {
        public:

        Scene();

        //func for rendering
        bool Render(Image &outputImage);

        private:

        private:

    };
}


#endif //TRAY_RACING_COMPUTER_GRAPHICS_SCENE_HPP
