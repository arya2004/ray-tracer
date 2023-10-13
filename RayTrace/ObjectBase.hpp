//
// Created by ziegler on 10/13/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_OBJECTBASE_HPP
#define TRAY_RACING_COMPUTER_GRAPHICS_OBJECTBASE_HPP

#include "./qbLinAlg/qbVector.h"
#include "Ray.hpp"

namespace RT
{
    class ObjectBase
    {
        public:
        ObjectBase();
        virtual ~ObjectBase();

        //test intersection
        virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

        //test whether two floating point are closely equal
        bool CloseEnough(const double f1, const float f2);

    public:
        qbVector<double> m_baseColor {3};
    };
}

#endif //TRAY_RACING_COMPUTER_GRAPHICS_OBJECTBASE_HPP
