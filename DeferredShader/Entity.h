#pragma once

#include <glm/glm.hpp>

class Entity {
public:
	Entity(glm::vec3 pos, glm::vec3 scl, glm::vec4 rot) 
		: position(pos), scale(scl), rotation(rot) {}
	glm::vec3 position; 
	glm::vec3 scale;
	glm::vec4 rotation;
};