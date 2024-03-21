//
// Created by Kiu on 21.03.2024.
//

#ifndef WEKTORY_IMAGE_H
#define WEKTORY_IMAGE_H

#include "Intensity.h"

class Image {
public:
    Image (int width, int height);
    int width = 1000;
    int height = 1000;

    void setPixel(int x, int y, Intensity pixel);
//    void createImage [][];
};


#endif //WEKTORY_IMAGE_H
