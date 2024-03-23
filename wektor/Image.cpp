////
//// Created by Kiu on 21.03.2024.
////
//
//#include "Image.h"
//
//Image::Image(int width, int height) : width(width), height(height)  {
//
//}
//
//void setPixel(Image& img, int x, int y, Intensity pixel) {
//    int red, green, blue;
//    // konwersja na zakres 0-255
//    red = static_cast<int>(pixel.getRed() * 255);
//    green = static_cast<int>(pixel.getGreen() * 255);
//    blue = static_cast<int>(pixel.getBlue() * 255);
//    // bezpośrednie ustawienie wartości piksela
////    img.setPixel(x, y, Intensity(red, green, blue));
//    pixels[x][y] = {red, green, blue};
//}