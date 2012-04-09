/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "ShaderManager.h"
#include "Entity.h"
#include "Material.h"

//STL
#include <vector>
#include <set>



class Model {
	public:
		typedef std::vector<Entity> EntityVector;
		typedef std::set<Material> MaterialSet;

		Model();
		virtual ~Model();

		virtual void draw(ShaderManager & shaderManager);

		bool hasDiffuseTexture() const;
		bool hasNormalTexture() const;
		bool hasVertexBuffer() const;	

		unsigned int getDiffuseTexID() const;
		unsigned int getNormalTexID() const;
		unsigned int getVertexBufferID() const;
		unsigned int getNumVertices() const;

		void setDiffuseTexID(unsigned int & id);
		void setNormalTexID(unsigned int & id);
		void setVertexBufferID(unsigned int & id);		
		void setNumVertices(unsigned int & id);
		
		void addMaterial(Material mat);
		void removeMaterial(Material::materialId mat);
		Material getMaterial(Material::materialId mat);
		const Material::materialId & getCurrentMaterial() const;
		void setCurrentMaterial(Material::materialId mat);
		void updateMaterial(Material & mat);

		void addEntity(Entity & entity);
		EntityVector & getAllEntities();

		bool isTransperent() const;

	private:
		bool hasDiffuseTex;
		bool hasNormalTex;
		bool hasVertexBuf;

		unsigned int diffuseTexID;
		unsigned int normalTexID;
		unsigned int vertexBufferID;

		Material::materialId currentMaterial;

		EntityVector entityVector;
		MaterialSet materials;

		unsigned int numVertices;
};