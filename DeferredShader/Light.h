/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"
#include <glm/glm.hpp>

class Light {
public:
	Light(){}
	Light(glm::vec3 pos, glm::vec3 color) : lightPos(pos), lightColor(color) {}

	inline glm::vec3 & getPosition();
	inline glm::vec3 & getColor();

	void setPosition(glm::vec3 & value);
	void setColor(glm::vec3 & value);
private:
	glm::vec3 lightPos;
	glm::vec3 lightColor;
};