/**
* @Author: Christian Magnerfelt
* @date: 2012.03.03
*
**/
#pragma once

#include <glm/glm.hpp>
#include <string>

class Material
{
public:
	typedef std::string materialId;
	bool operator<(const Material & mat) const { return matId < mat.matId;}
	bool operator==(const Material::materialId & id) const { return matId == id; }
	Material();

	materialId getID() const;
	glm::vec3 getDiffuseColor() const;
	glm::vec3 getSpecularColor() const;
	glm::vec3 getEmissiveColor() const;
	glm::vec3 getAmbientColor() const;
	glm::vec3 getTransperentColor() const;
	float getShinyness() const;
	float getOpacity() const;	

	void setID(materialId id);
	void setDiffuseColor(glm::vec3 color);
	void setSpecularColor(glm::vec3 color);
	void setEmissiveColor(glm::vec3 color);
	void setAmbientColor(glm::vec3 color);
	void setTransperentColor(glm::vec3 color);
	void setShinyness(float value);
	void setOpacity(float value);

private:
	materialId matId;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	glm::vec3 emissiveColor;
	glm::vec3 ambientColor;
	glm::vec3 transperentColor;
	float shinyness;
	float opacity;
};