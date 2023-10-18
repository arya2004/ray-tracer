//
// Created by ziegler on 10/18/23.
//

#ifndef TRAY_RACING_COMPUTER_GRAPHICS_GTFM_HPP
#define TRAY_RACING_COMPUTER_GRAPHICS_GTFM_HPP

#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbMatrix.h"
#include "Ray.hpp"

namespace RT
{
    //flag for fwd or bkwd
    constexpr bool FWDTFORM = true;
    constexpr bool BCKTFORM = false;

    class GTform
    {
    public:
        GTform();
        ~GTform();


        GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);

        void SetTransform(const qbVector<double> &translation,
                          const qbVector<double> &rotation,
                          const qbVector<double> &scale);

        //getter
        qbMatrix2<double> GetForward();
        qbMatrix2<double> GetBackward();

        RT::Ray Apply(const RT::Ray &inputRAy, bool DirFlag);
        qbVector<double> Apply(const qbVector<double> &inputVEctior, bool dirFlag);


        //operator overload
        //not member of class, but hass access of provate member
        friend GTform operator*(const RT::GTform &lhs, const RT::GTform &rhs);

        //
        GTform operator= (const GTform &rhs);

        void PrintMatrix(bool DirFlag);

        //static for debug
        static void PrintVector(const qbVector<double> &vector);

    private:
        void Print(const qbMatrix2<double> &matrix);

    private:
        qbMatrix2<double> m_fwdtfm {4,4};
        qbMatrix2<double> m_bcktfm {4,4};





    };
}


#endif //TRAY_RACING_COMPUTER_GRAPHICS_GTFM_HPP
