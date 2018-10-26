#ifndef _MODEL_H_
#define _MODEL_H_

//Includes
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
#include "Vector3.h"
#include "SOIL.h"

using namespace std;

class Model
{
	

public:
	//Public Functions
	bool load(char* modelFilename, char* textureFilename);
	void render();

	
private:

	//Private Functions
	void loadTexture(char*);
	bool loadModel(char*);

	//Private Variables
	int VertexCount;
	GLuint Texture;

	//Vector for Model Data
	vector<float> vertex, normals, texCoords;

};

#endif