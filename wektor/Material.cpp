//
// Created by Maciek on 28.03.2024.
//
#include "Material.h"

Material::Material(Intensity diffuse_colour, float specular_amount, float specular_coeff, float reflect_fraction)
: diffuse_colour(diffuse_colour), specular_amount(specular_amount), specular_coeff(specular_coeff), reflect_fraction(reflect_fraction){

}

Material::Material() {

}

