cmake_minimum_required(VERSION 3.23)
project(Wektory)

set(CMAKE_CXX_STANDARD 14)

add_executable(Wektory main.cpp Vector.cpp Vector.h Sphere.cpp Sphere.h Plane.cpp Plane.h Ray.cpp Ray.h)
