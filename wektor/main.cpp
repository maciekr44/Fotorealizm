#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Intensity.h"
#include "Ray.h"
#include "Sphere.h"
#include "OrtogonalCamera.h"
#include "Image.h"

int main() {
    // Create two spheres
    Vector sphere1Center(0, 0, 0);
    Vector sphere2Center(50, 0, 0);
    Intensity red(1, 0, 0);
    Intensity blue(0, 0, 1);
    Sphere sphere1(sphere1Center, 15, red);
    Sphere sphere2(sphere2Center, 10, blue);

    // Create an image with given width and height
    int imageWidth = 600;
    int imageHeight = 600;
    Image image(imageWidth, imageHeight);

    // Define the parameters for the orthogonal camera
    Vector cameraPosition(0, 0, -200);
    Vector lookAt(0, 0, 0);
    Vector up(0, 1, 0);
    float left = -100.0f;
    float right = 100.0f;
    float bottom = -100.0f;
    float top = 100.0f;

    // Create an orthogonal camera
    OrtogonalCamera camera(cameraPosition, lookAt, up, left, right, bottom, top, imageWidth, imageHeight);

    // Iterate over each pixel in the image
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            // Cast a ray from the camera through the pixel
            Ray ray = camera.castRay(x, y);

            // Check for intersections with the spheres
            IntersectionResult intersection1 = sphere1.Hit(ray, 0, 1000); //min to nearplanea max to farplane
            IntersectionResult intersection2 = sphere2.Hit(ray, 0, 1000);

            // Set the pixel color based on the intersection result
            if (intersection1.type == HIT && intersection2.type != HIT) {
                image.setPixel(x, y, intersection1.color);
            } else if (intersection2.type == HIT && intersection1.type != HIT) {
                image.setPixel(x, y, intersection2.color);
            } else if (intersection1.type == HIT && intersection2.type == HIT) {
                // Choose the closest intersection
                if (intersection1.distance < intersection2.distance) {
                    image.setPixel(x, y, intersection1.color);
                } else {
                    image.setPixel(x, y, intersection2.color);
                }
            } else {
                // Set background color
                Intensity bgColor(0, 1, 1);
                image.setPixel(x, y, bgColor);
            }
        }
    }

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(image.width, image.height), "SFML Image Test");

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear window
        window.clear();

        // Draw the image
        window.draw(image);

        // Display window
        window.display();
    }

}