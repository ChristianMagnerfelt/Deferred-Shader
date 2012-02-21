#include "RTGModel.h"

RTGModel::~RTGModel()
{
	if(file != 0) RTG_Free(file);
}
void RTGModel::draw(ShaderManager & shader)
{
	shader.bindCGTexture(diffuseTexID,MODEL_TEXTURE);
	//shader.bindCGTexture(normalMapID,MODEL_NORMAL_MAP);
	shader.bindCGMaterial(Float4(mat->spc[0],mat->spc[0],mat->spc[0],mat->shn),SPECULAR);
	for(unsigned int i = 0; i < file->nnodes; ++i)
	{
		drawNode(file->nodes[i]);
	}
}
void RTGModel::drawNode(RTGNode *node)
{
		if (node->obj) 
		{
			drawObject(node->obj);
		}
		for (unsigned int i = 0; i < node->nchildren; i++) {
			drawNode(node->children[i]);
		}
}
void RTGModel::drawObject(RTGObject *obj)
{
	RTGVertex *v;
	RTGVec3 *n;
	RTGVec3 *p;
	RTGVec2 *t;
	//setMaterial(file->mat[obj->mat]);
	
	for (unsigned int i = 0; i < obj->npoly; ++i) {
		glBegin(GL_POLYGON);
		
		for (unsigned int j = 0; j < obj->poly[i]->nvert; ++j)
		{
			v = &obj->poly[i]->v[j];
			n = &obj->norm[v->n];
			t = &obj->tex[v->t];
			p = &obj->pos[v->p];
			
			glNormal3f(n->x, n->y, n->z);
			glTexCoord2f(t->x, -(t->y));
			glVertex3f(p->x, p->y, p->z);
		}
		glEnd();
	}
}