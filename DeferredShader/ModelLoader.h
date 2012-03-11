/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "Util.h"
#include "Model.h"
//#include "RTGLib.h"

#include <aiVector3D.h>
#include <string>


class ModelLoader
{
	public:
		//RTGFile * loadRTG(const char * fileName, bool printModelInfo);
		bool loadAssimpScene(std::string file, Model & model);
		void AssimpSceneToArray(float * dest, aiVector3D * src, unsigned int n);
	private:
};


