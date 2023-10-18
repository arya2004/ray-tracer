//
// Created by ziegler on 10/13/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_OBJSPHERE_HPP
#define TRAY_RACING_COMPUTER_GRAPHICS_OBJSPHERE_HPP

#include "ObjectBase.hpp"
#include "Gtfm.hpp"

namespace RT
{
    class ObjSphere : public ObjectBase
    {
    public:
        ObjSphere();

        virtual ~ObjSphere() override;
        virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) override;

    private:


    };
}

#endif //TRAY_RACING_COMPUTER_GRAPHICS_OBJSPHERE_HPP
