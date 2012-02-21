/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"

class Light {
public:
	Light(){}
	Light(Float3 pos, Float3 color) : lightPos(pos), lightColor(color) {}
	inline Float3 & getPosition();
	inline Float3 & getColor();
	void setPosition(Float3 & value);
	void setColor(Float3 & value);
	Float3 lightPos;
	Float3 lightColor;
};