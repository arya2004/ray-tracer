//
// Created by ziegler on 10/18/23.
//

#include "Gtfm.hpp"

RT::GTform::GTform() {
    //set fwd and bkwd to identity
    m_bcktfm.SetToIdentity();
    m_fwdtfm.SetToIdentity();
}

RT::GTform::~GTform() {

}

RT::GTform::GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck) {
    //verify ip are 4x4
    if((fwd.GetNumRows() != 4) || (fwd.GetNumCols() != 4) || (bck.GetNumRows() != 4) || (bck.GetNumCols() != 4))
    {
        throw std::invalid_argument("caont maek gtform, not 4x4 inpot");
    }
    m_fwdtfm = fwd;
    m_bcktfm = bck;
}


void RT::GTform::SetTransform(const qbVector<double> &translation, const qbVector<double> &rotation,
                              const qbVector<double> &scale) {
    //define matric for each component
    qbMatrix2<double> translationMatrix {4,4};
    qbMatrix2<double> rotationMatrixX {4,4};
    qbMatrix2<double> rotationMatrixY {4,4};
    qbMatrix2<double> rotationMatrixZ {4,4};
    qbMatrix2<double> scaleMatrix {4,4};

    //seto identity
    translationMatrix.SetToIdentity();
    rotationMatrixX.SetToIdentity();
    rotationMatrixY.SetToIdentity();
    rotationMatrixZ.SetToIdentity();
    scaleMatrix.SetToIdentity();


    // Populate these with the appropriate values.
    // First the translation matrix.
    translationMatrix.SetElement(0, 3, translation.GetElement(0));
    translationMatrix.SetElement(1, 3, translation.GetElement(1));
    translationMatrix.SetElement(2, 3, translation.GetElement(2));

    // Rotation matrices.
    rotationMatrixZ.SetElement(0, 0, cos(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(0, 1, -sin(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(1, 0, sin(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(1, 1, cos(rotation.GetElement(2)));

    rotationMatrixY.SetElement(0, 0, cos(rotation.GetElement(1)));
    rotationMatrixY.SetElement(0, 2, sin(rotation.GetElement(1)));
    rotationMatrixY.SetElement(2, 0, -sin(rotation.GetElement(1)));
    rotationMatrixY.SetElement(2, 2, cos(rotation.GetElement(1)));

    rotationMatrixX.SetElement(1, 1, cos(rotation.GetElement(0)));
    rotationMatrixX.SetElement(1, 2, -sin(rotation.GetElement(0)));
    rotationMatrixX.SetElement(2, 1, sin(rotation.GetElement(0)));
    rotationMatrixX.SetElement(2, 2, cos(rotation.GetElement(0)));

    // And the scale matrix.
    scaleMatrix.SetElement(0, 0, scale.GetElement(0));
    scaleMatrix.SetElement(1, 1, scale.GetElement(1));
    scaleMatrix.SetElement(2, 2, scale.GetElement(2));

    // Combine to give the final forward transform matrix.
    m_fwdtfm =	translationMatrix *
                  scaleMatrix *
                  rotationMatrixX *
                  rotationMatrixY *
                  rotationMatrixZ;

    // Compute the backwards transform.
    m_bcktfm = m_fwdtfm;
    m_bcktfm.Inverse();

}

qbMatrix2<double> RT::GTform::GetForward() {
    return m_fwdtfm;
}

qbMatrix2<double> RT::GTform::GetBackward() {
    return m_bcktfm;
}

RT::Ray RT::GTform::Apply(const RT::Ray &inputRAy, bool DirFlag) {
    //create an op obkect
    RT::Ray outputRay;
    if(DirFlag)
    {
        outputRay.m_point1 = this->Apply(inputRAy.m_point1, RT::FWDTFORM);
        outputRay.m_point2 = this->Apply(inputRAy.m_point2, RT::FWDTFORM);
        outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
    }else{
        outputRay.m_point1 = this->Apply(inputRAy.m_point1, RT::BCKTFORM);
        outputRay.m_point2 = this->Apply(inputRAy.m_point2, RT::BCKTFORM);
        outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
    }

    return outputRay;
}

qbVector<double> RT::GTform::Apply(const qbVector<double> &inputVEctior, bool dirFlag) {
    //convert ip to 4x4
    std::vector<double> tempData{
        inputVEctior.GetElement(0),
        inputVEctior.GetElement(1),
        inputVEctior.GetElement(2),
        1.0
    };
    qbVector<double> tempVEctor { tempData};

    qbVector<double> resultVector;

    if(dirFlag)
    {
        resultVector = m_fwdtfm * tempVEctor;
    }else
    {
        resultVector = m_bcktfm * tempVEctor;
    }

    // Reform the output as a 3-element vector.
    qbVector<double> outputVector {std::vector<double> {	resultVector.GetElement(0),
                                                            resultVector.GetElement(1),
                                                            resultVector.GetElement(2) }};

    return outputVector;

}

//overload operator

namespace RT
{
    RT::GTform operator *(const RT::GTform &lhs, const RT::GTform &rhs)
    {
        //form product
        qbMatrix2<double> fwdResult = lhs.m_fwdtfm * rhs.m_fwdtfm;

        // Compute the backward transform as the inverse of the forward transform.
        qbMatrix2<double> bckResult = fwdResult;
        bckResult.Inverse();

        // Form the final result.
        RT::GTform finalResult (fwdResult, bckResult);

        return finalResult;
    }

}

RT::GTform RT::GTform::operator=(const RT::GTform &rhs) {
    //make sure not assigning to ourself
    if(this != &rhs)
    {
        m_fwdtfm = rhs.m_fwdtfm;
        m_bcktfm = rhs.m_bcktfm;
    }

    return *this;
}


// Function to print the transform matrix to STDOUT.
void RT::GTform::PrintMatrix(bool dirFlag)
{
    if (dirFlag)
    {
        Print(m_fwdtfm);
    }
    else
    {
        Print(m_bcktfm);
    }
}

void RT::GTform::Print(const qbMatrix2<double> &matrix)
{
    int nRows = matrix.GetNumRows();
    int nCols = matrix.GetNumCols();
    for (int row = 0; row<nRows; ++row)
    {
        for (int col = 0; col<nCols; ++col)
        {
            std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row, col) << " ";
        }
        std::cout << std::endl;
    }
}

// Function to print vectors.
void RT::GTform::PrintVector(const qbVector<double> &inputVector)
{
    int nRows = inputVector.GetNumDims();
    for (int row = 0; row < nRows; ++row)
    {
        std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
    }
}