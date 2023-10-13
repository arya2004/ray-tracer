//
// Created by ziegler on 10/13/23.
//

#include "ObjSphere.hpp"
#include <cmath>

RT::ObjSphere::ObjSphere() {

}


RT::ObjSphere::~ObjSphere() {}

bool RT::ObjSphere::TestIntersection(const RT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                     qbVector<double> &localColor) {
    //meth warning
    //compute value of a,b,c
    qbVector<double> vhat = castRay.m_lab;
    vhat.Normalize();

    /* Note that a is equal to the squared magnitude of the
		direction of the cast ray. As this will be a unit vector,
		we can conclude that the value of 'a' will always be 1. */
    //double a = 1.0;
    // ****


    double b  = 2.0 * qbVector<double>::dot(castRay.m_point1, vhat);
    double c  = qbVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

    double intTest = (b*b) - 4.0 *c;
    if(intTest > 0.0){
        return true;
    }
    else{
        return false;
    }

}