//
// Created by ziegler on 10/13/23.
//

#include "ObjectBase.hpp"
#include <math.h>

#define EPSILON 1e-21f;

RT::ObjectBase::ObjectBase() {

}

RT::ObjectBase::~ObjectBase() {

}
//will get overwritten
bool RT::ObjectBase::TestIntersection(const RT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                      qbVector<double> &localColor) {
    return false;
}

bool RT::ObjectBase::CloseEnough(const double f1, const float f2) {
    return fabs(f1- f2) < EPSILON;
}