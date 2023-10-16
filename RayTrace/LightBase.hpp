//
// Created by ziegler on 10/16/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_LIGHTBASE_HPP
#define TRAY_RACING_COMPUTER_GRAPHICS_LIGHTBASE_HPP

#include <memory>
#include "./qbLinAlg/qbVector.h"
#include "Ray.hpp"
#include "ObjectBase.hpp"

namespace RT
{
    class LightBase
    {
        public:
        LightBase();
        virtual ~LightBase();

        virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<RT::ObjectBase>> &objList,
        const std::shared_ptr<RT::ObjectBase> &currentObject, qbVector<double> &color, double &intensity);

    public:
        qbVector<double> m_color {3};
        qbVector<double> m_location {3};
        double m_intensity;
    };
}

#endif //TRAY_RACING_COMPUTER_GRAPHICS_LIGHTBASE_HPP
