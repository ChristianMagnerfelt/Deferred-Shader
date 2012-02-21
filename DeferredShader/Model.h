/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"
#include "ShaderManager.h"
#include <vector>


struct Entity {
	Entity(Float3 pos, Float3 scl, Float4 rot) 
		: position(pos), scale(scl), rotation(rot) {}
	Float3 position; 
	Float3 scale;
	Float4 rotation;
};

typedef vector<Entity> EntityVector;

class Model {
	public:
		virtual ~Model(){}
		virtual void draw(ShaderManager & shaderManager) = 0;
		unsigned int getDiffuseTexID();
		unsigned int getNormalMapID();
		void setDiffuseTexID(unsigned int & id);
		void setNormalMapID(unsigned int & id);
		void addEntity(Entity & entity);
		EntityVector & getAllEntities();
	protected:
		unsigned int diffuseTexID;
		unsigned int normalMapID;
		EntityVector entityVector;		
};