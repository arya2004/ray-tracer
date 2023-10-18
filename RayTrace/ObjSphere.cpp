//
// Created by ziegler on 10/13/23.
//

#include "ObjSphere.hpp"
#include <cmath>

RT::ObjSphere::ObjSphere() {

}


RT::ObjSphere::~ObjSphere() {}


//pass the ray from cameraa, returns local intersection and local normal.
//first apply transformation
bool RT::ObjSphere::TestIntersection(const RT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                     qbVector<double> &localColor) {

    //world to local, so back
    RT::Ray bckRay = m_transformMatrix.Apply(castRay, RT::BCKTFORM);

    //meth warning
    //compute value of a,b,c
    qbVector<double> vhat = bckRay.m_lab;
    vhat.Normalize();

    /* Note that a is equal to the squared magnitude of the
		direction of the cast ray. As this will be a unit vector,
		we can conclude that the value of 'a' will always be 1. */
    //double a = 1.0;
    // ****


    double b  = 2.0 * qbVector<double>::dot(bckRay.m_point1, vhat);
    double c  = qbVector<double>::dot(bckRay.m_point1, bckRay.m_point1) - 1.0;

    double intTest = (b*b) - 4.0 *c;

    qbVector<double> PointofIntersection;

    if(intTest > 0.0){
        //if intercestion then calc where intersection
        double numSQRT = sqrtf(intTest);
        double  t1 = (-b + numSQRT) / 2.0;
        double  t2 = (-b - numSQRT) / 2.0;
        //if one negative then one part behind camera, ignore it
        if((t1 < 0.0) || (t2 < 0.0)){
            return false;
        }
        else{
            //determine closest intersection
            if(t1 < t2){
                PointofIntersection = bckRay.m_point1 + (vhat * t1);
            }else{
                PointofIntersection = bckRay.m_point1 + (vhat * t2);
            }
            //transform back to world cord
            intPoint = m_transformMatrix.Apply(PointofIntersection, RT::FWDTFORM);

            qbVector<double> objOrigin = qbVector<double>{std::vector<double>{0.0,0.0,0.0}};
            qbVector<double> newObjOrigin = m_transformMatrix.Apply(objOrigin, RT::FWDTFORM);



            //compute local normal
            localNormal = intPoint - newObjOrigin;
            localNormal.Normalized();

            localColor = m_baseColor;

        }
        return true;

    }
    else{
        return false;
    }

}