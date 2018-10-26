#pragma once

//Includes
#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "Vector3.h"
#include "SOIL.h"

using namespace std;

class ProceduralGeneration
{
public:

	//Constructor
	ProceduralGeneration();

	//Deconstructor
	~ProceduralGeneration();

	//Public Functions
	void GenerateHalfSphere(int r, int seg);
	void GenerateCylinder(int r, int seg);
	void GenerateDisc(int r, int seg);
	void Render();

private:

	//Float Variables 
	float x, y, z, Radius, Theta, Delta;
	
	//Int Variables
	int Segments;
	int m_VertexCount;

	//Vector for Shape Data
	vector <float> Vertex, Normals, TexCoords;
	
	//Data for Texture Loading
	GLuint ArenaBase;
};

