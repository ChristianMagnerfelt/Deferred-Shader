
//glm
#include <glm/glm.hpp>

// Assimp
#include <assimp.hpp>
#include <aiScene.h>
#include <aiMesh.h>
#include <aiPostProcess.h>

// STL
#include <iostream>
#include <string>

// Other
#include "ModelLoader.h"
#include "Model.h"

bool ModelLoader::loadAssimpScene(std::string file, Model & model)
{
	Assimp::Importer importer;
	std::cout << "Reading file: " << file << std::endl;
	const aiScene* scene = importer.ReadFile( file, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_OptimizeGraph);
  
	// If the import failed, report it
	if(!scene)
	{
		std::cout << importer.GetErrorString() << std::endl;
		return false;
	}
	if(scene->HasMeshes())
	{
		std::cout << "Number of meshes : " << scene->mNumMeshes << std::endl;
		// Load root
		std::cout << "loading root" << std::endl;
		std::cout << "Num of meshes in Root : " << scene->mRootNode->mNumMeshes << std::endl;
		const struct aiMesh * mesh = 0;
		if(scene->mNumMeshes > 0)
		{
			for(unsigned int n = 0; n < scene->mNumMeshes; ++n)
			{
				mesh = scene->mMeshes[n];
				std::cout << "---- Mesh ----" << std::endl;
				std::cout << "Name : " << mesh->mName.data << std::endl;
				std::cout << "Vertices : " << mesh->mNumVertices << std::endl;
				std::cout << "Faces : " << mesh->mNumFaces << std::endl;
				break;
			}
		}
		else
		{
			std::cout << "No meshes" << std::endl;
			// TODO : Extract mesh from childs
		}
		if(mesh == 0)
		{
			std::cout << "No meshes in scene" << std::endl;
			return false;
		}
		if(mesh->HasPositions())
		{
			// Variables
			unsigned int numVertices = mesh->mNumVertices;
			unsigned int size = numVertices * 3;
			unsigned int buffer;
			
			float * positions = new float[size * 4];
			float * normals = (positions + size);
			float * biTangents = (positions + (size * 2));
			float * texCoords = (positions + (size * 3));

			std::cout << "Size in floats : " << size << std::endl;
			std::cout << "Size in bytes: " << size * 4 << std::endl;

			AssimpSceneToArray(positions,mesh->mVertices,mesh->mNumVertices);
			AssimpSceneToArray(normals,mesh->mNormals,mesh->mNumVertices);
			AssimpSceneToArray(biTangents,mesh->mBitangents,mesh->mNumVertices);
			AssimpSceneToArray(texCoords,mesh->mTextureCoords[0],mesh->mNumVertices);

			
			glGenBuffersARB(1, &buffer);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, buffer);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, size * 4 * sizeof(float), positions, GL_STATIC_DRAW_ARB);
			std::cout << "Vertex buffer ID: " << buffer << std::endl;

			model.setVertexBufferID(buffer);
			model.setNumVertices(numVertices);

			std::cout << "-- Positions";
			for(unsigned int i = 0; i < size * 4; ++i)
			{
				if( i % 3 == 0) std::cout << std::endl;
				if( i == size) std::cout << "-- Normals" << std::endl;
				if( i == (size * 2)) std::cout << "-- BiTangents" << std::endl;
				if( i == (size * 3)) std::cout << "-- TexCoords" << std::endl;
				std::cout << positions[i] << " ";
			}
			std::cout << std::endl;
			delete [] positions;
		}
		else
		{
			std::cout << "No vertices in mesh" << std::endl;
			return false;
		}
		if(scene->HasMaterials())
		{
			std::cout << "---- Materials ----" << std::endl;
			std::cout << "Number of materials : " << scene->mNumMaterials << std::endl;
			aiMaterial * mat;
			for(unsigned int n = 0; n < scene->mNumMaterials; ++n)
			{
				std::cout << "-- Material " << n << std::endl;
				mat = scene->mMaterials[n];
				aiString name;
				aiColor3D diffuse;
				aiColor3D specular;
				Material newMaterial;
				if(AI_SUCCESS == mat->Get(AI_MATKEY_NAME,name))
				{
					std::cout << "Name : " << name.data << std::endl;
					newMaterial.setID(Material::materialId(name.data));
				}
				if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_DIFFUSE,diffuse))
				{
					std::cout << "Diffuse color : " << diffuse.r << " " << diffuse.g << " " << diffuse.b << std::endl;
					newMaterial.setDiffuseColor(glm::vec3(diffuse.r, diffuse.g, diffuse.b));
				}
				if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_SPECULAR,specular))
				{
					std::cout << "Specular color : " << specular.r << " " << specular.g << " " << specular.b << std::endl; 
					newMaterial.setSpecularColor(glm::vec3(specular.r, specular.g, specular.b));
				}
				model.addMaterial(newMaterial);
			}
		}
	}
	std::cout << file << " loaded successfully" << std::endl;
	return true;
}

void ModelLoader::AssimpSceneToArray(float * dest, aiVector3D * src, unsigned int n)
{
	  for(unsigned int i = 0; i < n; ++i)
	  {
		  dest[(i * 3)] = src[i].x;
		  dest[(i * 3) + 1] = src[i].y;
		  dest[(i * 3) + 2] = src[i].z;
	  }
}

/**
RTGFile * ModelLoader::loadRTG(const char * fileName,bool printRTGData)
{
	
	return RTG_Parse(fileName, printRTGData);
}**/

