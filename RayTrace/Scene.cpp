//
// Created by ziegler on 10/13/23.
//

#include "Scene.hpp"

RT::Scene::Scene() {

}

bool RT::Scene::Render(Image &outputImage) {
    //core functionality
    //get o/p dimention
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    //color var
    for (int i = 0; i < xSize; ++i) {
        for (int j = 0; j < ySize; ++j) {
            double red = (static_cast<double>(i)/ 1000.0) * 255.0;
            double green = (static_cast<double>(j)/ 1000.0) * 255.0;
            outputImage.SetPixel(i, j, red, green,0.0);
        }
    }
    return true;
}