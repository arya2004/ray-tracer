//
// Created by ziegler on 10/13/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_CAMERA_HPP
#define TRAY_RACING_COMPUTER_GRAPHICS_CAMERA_HPP

#include "./qbLinAlg/qbVector.h"
#include "Ray.hpp"

namespace RT
{
    class Camera
    {
        public:
        Camera();
        //set camera param
        void SetPosition(const qbVector<double> &newPosition);
        void SetLookAt(const qbVector<double> &newLookAt);
        void SetUp (const qbVector<double> &upVector);
        void SetLength(double newLength); //virtual pin from camera
        void SetHorizontalSize(double newSize);
        void SetAspect(double newAspect);

        //func to return param;
        qbVector<double> GetPosition();
        qbVector<double> GetLookAt();
        qbVector<double> GetUp();
        qbVector<double> GetU();
        qbVector<double> GetV();
        qbVector<double> GetScreenCentre();
        double GetLength();
        double GetHorizontalSize();
        double GEtAspect();

        //func to generate ray
        Ray GenerateRay(float proScreenX, float proScreenY);
        //pos on screen we wanna generate ray from pinhole;
        //update camera geomerty
        void UpdateCameraGeometry();

        private:
        qbVector<double> m_cameraPosition {3};
        qbVector<double> m_cameraLookAt {3};
        qbVector<double> m_cameraUp {3};
        double m_cameraLength;
        double m_cameraHorSize;
        double m_cameraAspectRatio;

        qbVector<double> m_alignmentVector {3};
        qbVector<double> m_projectionScreenU {3};
        qbVector<double> m_projectionScreenV {3};
        qbVector<double> m_projectionScreenCentre {3};

    };
}


#endif //TRAY_RACING_COMPUTER_GRAPHICS_CAMERA_HPP
