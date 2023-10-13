//
// Created by ziegler on 10/13/23.
//

#include "Camera.hpp"
#include "Ray.hpp"
#include <math.h>

RT::Camera::Camera() {
    m_cameraPosition = qbVector<double> {std::vector<double> {0.0, -10.0, 0.0}};
    m_cameraLookAt = qbVector<double> {std::vector<double> {0.0, 0.0, 0.0}};
    m_cameraUp = qbVector<double> {std::vector<double> {0.0, 0.0, 1.0}};
    m_cameraLength = 1.0;
    m_cameraAspectRatio = 1.0;
    m_cameraAspectRatio = 1.0;

}

void RT::Camera::SetPosition(const qbVector<double> &newPosition) {
    m_cameraPosition = newPosition;
}

void RT::Camera::SetLookAt(const qbVector<double> &newLookAt) {
    m_cameraLookAt = newLookAt;
}
void RT::Camera::SetUp(const qbVector<double> &upVector) {
    m_cameraUp = upVector;
}

void RT::Camera::SetLength(double newLength) {
    m_cameraLength = newLength;
}

void RT::Camera::SetHorizontalSize(double newSize) {
    m_cameraHorSize = newSize;
}

void RT::Camera::SetAspect(double newAspect) {
    m_cameraAspectRatio = newAspect;
}

//return param method

qbVector<double> RT::Camera::GetPosition() {
    return m_cameraPosition;
}
qbVector<double> RT::Camera::GetLookAt(){
    return m_cameraLookAt;
}
qbVector<double> RT::Camera::GetUp(){
    return m_cameraUp;
}

qbVector<double> RT::Camera::GetU(){
    return m_projectionScreenU;
}
qbVector<double> RT::Camera::GetV(){
    return m_projectionScreenV;
}
qbVector<double> RT::Camera::GetScreenCentre(){
    return m_projectionScreenCentre;
}

double RT::Camera::GetLength(){
    return m_cameraLength;
}
double RT::Camera::GetHorizontalSize(){
    return m_cameraHorSize;
}
double RT::Camera::GEtAspect(){
    return m_cameraAspectRatio;
}

//geometry calculator
void RT::Camera::UpdateCameraGeometry() {
    //
    m_alignmentVector = m_cameraLookAt - m_cameraPosition;
    m_alignmentVector.Normalize();

    //compute U and V
    m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
    m_projectionScreenU.Normalize();
    m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
    m_projectionScreenV.Normalize();

    //calculate centre of screen
    m_projectionScreenCentre = m_cameraPosition + (m_cameraLength * m_alignmentVector);
    //vec cross product
    m_projectionScreenU = m_projectionScreenU * m_cameraHorSize;
    m_projectionScreenV = m_projectionScreenV * (m_cameraHorSize/ m_cameraAspectRatio);
}

RT::Ray RT::Camera::GenerateRay(float proScreenX, float proScreenY) {
    //conpute location of screen point in world co-ordinatie
    qbVector<double> screenWorldPart1 = m_projectionScreenCentre + (m_projectionScreenU + proScreenX);
    qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);

    //use this point along with camera to compute ray
    return RT::Ray(m_cameraPosition, screenWorldCoordinate);

}