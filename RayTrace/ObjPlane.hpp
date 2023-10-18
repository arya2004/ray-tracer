//
// Created by ziegler on 10/19/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_OBJPLANE_HPP
#define TRAY_RACING_COMPUTER_GRAPHICS_OBJPLANE_HPP

#include "ObjectBase.hpp"
#include "Gtfm.hpp"

namespace RT
{
    class ObjPlane : public ObjectBase
    {
    public:
        ObjPlane();

        //override dtor
        virtual ~ObjPlane() override;

        virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

    private:

    };
}

#endif //TRAY_RACING_COMPUTER_GRAPHICS_OBJPLANE_HPP
