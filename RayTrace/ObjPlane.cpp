//
// Created by ziegler on 10/19/23.
//

#include "ObjPlane.hpp"
#include <cmath>

RT::ObjPlane::ObjPlane() {

}

RT::ObjPlane::~ObjPlane() {

}

bool RT::ObjPlane::TestIntersection(const RT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                    qbVector<double> &localColor) {

    //cpy ray and bcktrans, cause local cord
    RT::Ray bckRay = m_transformMatrix.Apply(castRay, RT::BCKTFORM);
    qbVector<double> k = bckRay.m_lab;
    k.Normalize();

    // check if intersection , if castRay aint parallel
    //else div by 0, number go brrrrr
    if(!CloseEnough(k.GetElement(2), 0.0))
    {
        //intersection
        double t = bckRay.m_point1.GetElement(2) / -k.GetElement(2);

        //if t -ve , point behind camera, ignore it
        if(t > 0.0)
        {
            double u = bckRay.m_point1.GetElement(0) + (k.GetElement(0) * t);
            double v = bckRay.m_point1.GetElement(1) + (k.GetElement(1) * t);

            //if both <=1 then in plane
            if((abs(u) < 1.0) && (abs(v) < 1.0))
            {
                //compute PoI
                qbVector<double> poi = bckRay.m_point1 + t*k;
                intPoint = m_transformMatrix.Apply(poi, RT::FWDTFORM);

                // Compute the local normal.
                qbVector<double> localOrigin {std::vector<double> {0.0, 0.0, 0.0}};
                qbVector<double> normalVector {std::vector<double> {0.0, 0.0, -1.0}};
                //gives global orighn
                qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, RT::FWDTFORM);
                localNormal = m_transformMatrix.Apply(normalVector, RT::FWDTFORM) - globalOrigin;
                localNormal.Normalize();

                // Return the base color.
                localColor = m_baseColor;

                return true;
            }
            else{
                return false;
            }
        } else{
            return false;
        }
    } else{
        return false;
    }
    return false;
}