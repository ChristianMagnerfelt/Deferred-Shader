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
	Light(glm::vec3 pos, glm::vec3 color, float rad) : lightPos(pos), lightColor(color), radius(rad) {}

	glm::vec3 getPosition() const;
	glm::vec3 getColor() const;
	float getRadius() const;

	void setPosition(const glm::vec3 value);
	void setColor(const glm::vec3 value);
	void setRadius(const float value);
private:
	glm::vec3 lightPos;
	glm::vec3 lightColor;
	float radius;
};