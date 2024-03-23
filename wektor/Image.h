//
// Created by Kiu on 21.03.2024.
//

#ifndef WEKTORY_IMAGE_H
#define WEKTORY_IMAGE_H

#include <vector>
#include "Intensity.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stdexcept>

class Image : public sf::Drawable {

public:
    // Constructor to initialize the image with given width and height
    Image(int _width, int _height) : width(_width), height(_height) {
        vertices.resize(width * height);
        for (int i = 0; i < width * height; ++i) {
            vertices[i].position = sf::Vector2f(i % width, i / width);
            vertices[i].color = sf::Color::Black; // Initialize all pixels to black
        }
    }

    // Function to set color of a pixel at position (x, y)
    void setPixel(int x, int y, Intensity color) {
        sf::Color sfcolor = color.intensityToSFMLColor();
        if (x >= 0 && x < width && y >= 0 && y < height) {
            vertices[y * width + x].color = sfcolor;
        }
    }

    int height;
    int width;
    std::vector<sf::Vertex> vertices;

private:
    // Overridden draw function to make the Image drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(vertices.data(), vertices.size(), sf::Points, states);
    }
};

#endif //WEKTORY_IMAGE_H
