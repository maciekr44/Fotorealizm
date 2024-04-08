//
// Created by Maciek on 28.03.2024.
//
#include "Material.h"

Material::Material(Intensity color, float specular, float shineness, float reflect)
        : color(color), specular(specular), shineness(shineness), reflect(reflect){

}

Material::Material() {

}

