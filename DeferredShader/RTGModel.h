#pragma once

#include "Util.h"
/**
@author: Christian Magnerfelt
@version: 2012.01.17
**/

#pragma once

#include "RTGLib.h"
#include "Model.h"
#include "ShaderManager.h"

/**
 * A container with cpp functionality added to RTGfile
 *
 */
class RTGModel : public Model
{
	public:
		RTGModel() : file(0) {}
		RTGModel(RTGFile * newFile) : file(newFile) {if(file!=0) mat = file->mat[0];}
		~RTGModel();

		void draw(ShaderManager & shaderManager);
		void drawNode(RTGNode * node);
		void drawObject(RTGObject * obj);

	private:
		RTGMaterial * mat;
		RTGFile * file;
};