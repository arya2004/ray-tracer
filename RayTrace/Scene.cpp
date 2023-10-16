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

    //construct test spehere
    m_objectList.push_back(std::make_shared<RT::ObjSphere>(RT::ObjSphere()));

    //single lught src
    m_lightList.push_back(std::make_shared<RT::PointLight>(RT::PointLight()));
    m_lightList.at(0)->m_location = qbVector<double> {std::vector<double> {5.0, -10.0, 25.0}};
    m_lightList.at(0)->m_color = qbVector<double> {std::vector<double> {255.0,255.0,255.0}};
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

            //test for intersection with all obj;
            for (auto currentObj : m_objectList) {
                bool validInt = currentObj->TestIntersection(cameraRay, intPoint, localNormal, localColor);

                if(validInt){

                    //calc intensity of illumination
                    double intensity;
                    qbVector<double> color{3};
                    bool vallidilum = false;
                    for (auto currentLight : m_lightList) {
                        vallidilum = currentLight->ComputeIllumination(intPoint, localNormal, m_objectList, currentObj, color, intensity);
                    }

                    //conpute distance btwn camera and point of intersection
                    double dist = (intPoint - cameraRay.m_point1).norm();
                    if(dist > maxDist){
                        maxDist = dist;
                    }
                    if(dist < minDist){
                        minDist = dist;
                    }
                    //outputImage.SetPixel(x,y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0,0.0);
                    if(vallidilum)
                    {
                        outputImage.SetPixel(x,y, 255.0 * intensity, 0.0,0.0);
                    }else{
                        outputImage.SetPixel(x,y,0.0,0.0,0.0);
                    }

                    // outputImage.SetPixel(x,y,0.0,255.0,0.0);
                }else{
                    outputImage.SetPixel(x,y,0.0,0.0,0.0);
                }
            }
            
            //test if valod intersection
          //  bool validInt = m_testSphere.TestIntersection(cameraRay, intPoint, localNormal, localColor);

            //if we have valid intersection, change color to red

        }
    }
    std::cout << "mindist: " << minDist << std::endl;
    std::cout << "maxdist: " << maxDist << std::endl;

    return true;
}