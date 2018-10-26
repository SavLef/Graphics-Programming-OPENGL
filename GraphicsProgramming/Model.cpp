#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

//Includes
#include "model.h"


bool Model::load(char* modelFilename, char* textureFilename)
{
	//Bool variable for Model Data
	bool result;
	//Loads the Data of the Model into the result variable
	result = loadModel(modelFilename);
	//Display Error Message if the Model fails to load
	if (!result)
	{
		MessageBox(NULL, "Model failed to load", "Error", MB_OK);
		return false;
	}

	//Loads the Model Texture
	loadTexture(textureFilename);

	return true;
}

void Model::render()
{
	//Enable Arrays for Model Data
	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_NORMAL_ARRAY); 
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	//Binds the loaded in Texture
	glBindTexture(GL_TEXTURE_2D, Texture);

	//Specify which arrays will be used to Render the Model
	glVertexPointer(3, GL_FLOAT, 0, vertex.data()); 
	glNormalPointer(GL_FLOAT, 0, normals.data()); 
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data());
	
	//Function used to Draw the Shape
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);

	//Disable Arrays for Model Data
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY); 
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//Remove Texture Data from being binded
	glBindTexture(GL_TEXTURE_2D, NULL);

}


// Modified from a mulit-threaded version by Mark Ropper.
bool Model::loadModel(char* filename)
{
	//Vectors to Store Data of the Model
	vector<Vector3> verts;
	vector<Vector3> norms;
	vector<Vector3> texCs;
	vector<unsigned int> faces;
	
	//Opens the File containing the Model Data
	FILE* file = fopen(filename, "r");
	//If the file fails to load, return false
	if (file == NULL)
	{
		return false;
	}
	while (true)
	{
		char lineHeader[128];

		// Read first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // Break the Loop
		}
		else 
		// Parse
		{
			//If the letter v is first
			if (strcmp(lineHeader, "v") == 0) 
			{
				//Load data into Vertex Vector
				Vector3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				verts.push_back(vertex);
			}
			//Else If the letters vt are first
			else if (strcmp(lineHeader, "vt") == 0) // Tex Coord
			{
				//Load data into UV Vector
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				texCs.push_back(uv);
			}
			//Else If the letters vn are first
			else if (strcmp(lineHeader, "vn") == 0) // Normal
			{
				//Load data into the Normal Vector
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				norms.push_back(normal);
			}
			//Else If the letter f is first
			else if (strcmp(lineHeader, "f") == 0) // Face
			{
				//Create an int Array of 9 elements
				unsigned int face[9];

				//Load the Data in to the Array
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face[0], &face[1], &face[2], &face[3], &face[4], &face[5],&face[6], &face[7], &face[8]);

				//Check if faces found are unequal to 9
				if (matches != 9)
				{
					// Parser error, or not triangle faces
					return false;
				}
				//If it actually passes, load all data into the faces Vector
				for (int i = 0; i < 9; i++)
				{
					faces.push_back(face[i]);
					
				}


			}
		}
	}

	//Loop to fill in the rest of the Vertex/ Normals/ TexCoords Vectors
	for (int i = 0; i < faces.size() ; i = i + 3)
	
	{
		//Vertex
		vertex.push_back(verts.at(faces.at(i) - 1).x);
		vertex.push_back(verts.at(faces.at(i) - 1).y);
		vertex.push_back(verts.at(faces.at(i) - 1).z);

		//Normals
		normals.push_back(norms.at(faces.at(i + 2) - 1).x);
		normals.push_back(norms.at(faces.at(i + 2) - 1).y);
		normals.push_back(norms.at(faces.at(i + 2) - 1).z);

		//Texture Coordinates
		texCoords.push_back(texCs.at(faces.at(i + 1) - 1).x);
		texCoords.push_back(texCs.at(faces.at(i + 1) - 1).y);


	}

	//Calculate Vertex Count
	VertexCount = vertex.size() / 3;

	// Once data has been sorted clear read data (which has been copied and are not longer needed).
	verts.clear();
	norms.clear();
	texCs.clear();
	faces.clear();

	return true;
}

void Model::loadTexture(char* filename)
{
	//Loads the Texture Data
	GLuint texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y
	);

	//Checks if Texture could not be loaded and displays an error message
	if (texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
	Texture = texture;
}



