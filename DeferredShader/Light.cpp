#include "Light.h"

inline Float3 & Light::getPosition(){ return lightPos;}
inline Float3 & Light::getColor(){ return lightColor;}
void Light::setPosition(Float3 & pos){lightPos = pos;}
void Light::setColor(Float3 & color){lightColor = color;}