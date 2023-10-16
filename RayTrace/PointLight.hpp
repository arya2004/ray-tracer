//
// Created by ziegler on 10/16/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_POINTLIGHT_HPP
#define TRAY_RACING_COMPUTER_GRAPHICS_POINTLIGHT_HPP

#include "LightBase.hpp"

namespace RT
{
    class PointLight : public  LightBase
    {
    public:
        PointLight();

        virtual ~PointLight();


        virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<RT::ObjectBase>> &objList,
                                         const std::shared_ptr<RT::ObjectBase> &currentObject, qbVector<double> &color, double &intensity) override;
    };
}

#endif //TRAY_RACING_COMPUTER_GRAPHICS_POINTLIGHT_HPP
