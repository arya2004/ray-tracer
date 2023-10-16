//
// Created by ziegler on 10/16/23.
//

#include "PointLight.hpp"


RT::PointLight::PointLight()
{
    m_color = qbVector<double> {std::vector<double> {1.0,1.0,1.0}};
    m_intensity = 1.0;
}

RT::PointLight::~PointLight()
{

}
bool RT::PointLight::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                         const std::vector<std::shared_ptr<RT::ObjectBase>> &objList,
                                         const std::shared_ptr<RT::ObjectBase> &currentObject, qbVector<double> &color,

                                         double &intensity) {
    //point from intersection point ot light
    qbVector<double> lightDir = (m_location - intPoint).Normalized();

    //starting point
    qbVector<double> startPoint = intPoint;

    //compute angle btwn local normal and light rays
    double angle = acos(qbVector<double>::dot(localNormal, lightDir));

    //if angle is pointing away, then no light
    if(angle > 1.5708){
        //no illu
        color = m_color;
        intensity = 0.0;
        return false;
    }else{
        color = m_color;
        intensity = m_intensity * (1.0 - (angle/ 1.5708));
        return true;
    }

}