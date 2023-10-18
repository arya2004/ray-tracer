//
// Created by ziegler on 10/13/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_SCENE_HPP
#define TRAY_RACING_COMPUTER_GRAPHICS_SCENE_HPP

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "Image.hpp"
#include "Camera.hpp"
#include "ObjSphere.hpp"
#include "PointLight.hpp"
#include "ObjPlane.hpp"


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
        RT::Camera m_camera;

        //List of objects
        std::vector<std::shared_ptr<RT::ObjectBase>> m_objectList;
        //RT::ObjSphere m_testSphere;

        //list of lights in scene
        std::vector<std::shared_ptr<RT::LightBase>> m_lightList;
    };
}


#endif //TRAY_RACING_COMPUTER_GRAPHICS_SCENE_HPP
