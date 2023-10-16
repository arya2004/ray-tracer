//
// Created by ziegler on 10/16/23.
//

#include "LightBase.hpp"

RT::LightBase::LightBase() {

}

RT::LightBase::~LightBase() {}

bool RT::LightBase::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                        const std::vector<std::shared_ptr<RT::ObjectBase>> &objList,
                                        const std::shared_ptr<RT::ObjectBase> &currentObject, qbVector<double> &color,
                                        double &intensity) {
    return false;
}