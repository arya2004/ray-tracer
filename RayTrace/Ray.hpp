//
// Created by ziegler on 10/13/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_RAY_HPP
#define TRAY_RACING_COMPUTER_GRAPHICS_RAY_HPP

#include "./qbLinAlg/qbVector.h"

namespace RT
{
    class Ray
    {
        public:
        Ray(const qbVector<double> &point1, const qbVector<double> &point2);

        qbVector<double> GetPoint1() const;
        qbVector<double> GetPoint2() const;

        public:
        qbVector<double> m_point1 ;
        qbVector<double> m_point2 ;
        qbVector<double> m_lab ;
       // qbVector<double> m_point1 (3);
       // qbVector<double> m_point2 (3);
       // qbVector<double> m_lab (3);
        //lab is vec from a to b
    };
}

#endif //TRAY_RACING_COMPUTER_GRAPHICS_RAY_HPP
