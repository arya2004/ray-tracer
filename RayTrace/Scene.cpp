//
// Created by ziegler on 10/13/23.
//

#include "Scene.hpp"

RT::Scene::Scene() {
    m_camera.SetPosition(qbVector<double>{std::vector<double> {0.0,-10.0, 0.0}});
    m_camera.SetLookAt(qbVector<double>{std::vector<double>{0.0,0.0,0.0}});
    m_camera.SetUp(qbVector<double>{std::vector<double>{0.0,0.0,1.0}});
    m_camera.SetHorizontalSize(0.25);
    m_camera.SetAspect(1.0/1.0);
    m_camera.UpdateCameraGeometry();
}

bool RT::Scene::Render(Image &outputImage) {
    //core functionality
    //get o/p dimention
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    //loop over each pixel in image
    RT::Ray cameraRay;
    qbVector<double> intPoint (3);
    qbVector<double> localNormal (3);
    qbVector<double> localColor (3);
    //gives val between 1-2
    double xFactor = 1.0 / (static_cast<double>(xSize) / 2.0);
    double yFactor = 1.0 / (static_cast<double>(ySize) / 2.0);
    double minDist = 1e6;
    double maxDist = 0.0;
    for (int x = 0; x < xSize; ++x) {
        for (int y = 0; y < ySize; ++y) {
            //normalize cordinate
            double normalX = (static_cast<double>(x) * xFactor) - 1.0;
            double normalY = (static_cast<double>(y) * yFactor) - 1.0;

            //generate ray for pixel
            m_camera.GenerateRay(normalX, normalY, cameraRay);

            //test if valod intersection
            bool validInt = m_testSphere.TestIntersection(cameraRay, intPoint, localNormal, localColor);

            //if we have valid intersection, change color to red
            if(validInt){
                outputImage.SetPixel(x,y,255.0,0.0,0.0);
            }else{
                outputImage.SetPixel(x,y,0.0,0.0,0.0);
            }
        }
    }


    return true;
}