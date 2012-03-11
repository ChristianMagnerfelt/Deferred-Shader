#include "Material.h"

Material::Material() : diffuseColor(0.0f), specularColor(0.0f),
	emissiveColor(0.0f), ambientColor(0.0f), transperentColor(0.0f), 
	shinyness(0.0f), opacity(1.0f), matId("default"){}
Material::materialId Material::getID() const
{
	return matId;
}
void Material::setID(Material::materialId id)
{
	matId = id;
}
glm::vec3 Material::getDiffuseColor() const
{
	return diffuseColor;
}
glm::vec3 Material::getSpecularColor() const
{
	return specularColor;
}
glm::vec3 Material::getEmissiveColor() const
{
	return emissiveColor;
}
glm::vec3 Material::getAmbientColor() const
{
	return ambientColor;
}
glm::vec3 Material::getTransperentColor() const
{
	return transperentColor;
}
float Material::getShinyness() const
{
	return shinyness;
}
float Material::getOpacity() const
{
	return opacity;
}
void Material::setDiffuseColor(glm::vec3 color)
{
	diffuseColor = color;
}
void Material::setSpecularColor(glm::vec3 color)
{
	specularColor = color;
}
void Material::setEmissiveColor(glm::vec3 color)
{
	emissiveColor = color;
}
void Material::setAmbientColor(glm::vec3 color)
{
	ambientColor = color;
}
void Material::setTransperentColor(glm::vec3 color)
{
	transperentColor = color;
}
void Material::setShinyness(float value)
{
	shinyness = value;
}
void Material::setOpacity(float value)
{
	opacity = value;
}