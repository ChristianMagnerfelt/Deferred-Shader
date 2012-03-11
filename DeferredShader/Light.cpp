#include "Light.h"
#include <glm/glm.hpp>

inline glm::vec3 & Light::getPosition(){ return lightPos;}
inline glm::vec3 & Light::getColor(){ return lightColor;}
void Light::setPosition(glm::vec3 & pos){lightPos = pos;}
void Light::setColor(glm::vec3 & color){lightColor = color;}