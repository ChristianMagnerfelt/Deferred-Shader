#include "Light.h"
#include <glm/glm.hpp>

glm::vec3 Light::getPosition() const { return lightPos;}
glm::vec3 Light::getColor() const { return lightColor;}
float Light::getRadius() const { return radius;}
void Light::setPosition(const glm::vec3 pos){lightPos = pos;}
void Light::setColor(const glm::vec3 color){lightColor = color;}
void Light::setRadius(const float rad){radius = rad;}