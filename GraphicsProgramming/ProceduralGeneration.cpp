#include "ProceduralGeneration.h"


//Constructor
ProceduralGeneration::ProceduralGeneration()
{
	//Loads the Texture for the Base of the Arena (Half Sphere)
	ArenaBase = SOIL_load_OGL_texture
	(
		"gfx/Arena.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);
}

//Deconstructor
ProceduralGeneration::~ProceduralGeneration()
{
}


//Render Function
void ProceduralGeneration::Render()
{
	//Enabling the Use of Arrays to read from them.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Binds the loaded in Texture (The base for the Arena)
	glBindTexture(GL_TEXTURE_2D, ArenaBase);

	//Specify which arrays will be used to Render the Model
	glVertexPointer(3, GL_FLOAT, 0, Vertex.data());
	glNormalPointer(GL_FLOAT, 0, Normals.data());
	glTexCoordPointer(2, GL_FLOAT, 0, TexCoords.data());

	//Function used to Draw the Shape
	glDrawArrays(GL_QUADS, 0, m_VertexCount);

	//Disable the Use of Arrays to read from them.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//Remove Texture Data from being binded
	glBindTexture(GL_TEXTURE_2D, NULL);
}

//Generate Arena Function
void ProceduralGeneration::GenerateHalfSphere(int r, int seg)
{
	//Variable Setup
	Segments = seg;
	Radius = r;
	Theta =  (2 * M_PI) / Segments;
	Delta = M_PI / Segments;
	
	//Float Variables
	float angle_long = 0.0f;
	float angle_lati = 0.0f;
	float next_long = 0.0f;
	float next_lati = 0.0f;

	//Initial Colour for the HalfSphere
	glColor3f(0.0f, 1.0f, 0.0f);

	//Outer For Loop, which increases Longitude
	for (int longitude = 0; longitude < (Segments + 1)/2; longitude++)
	{
		//Inner For Loop, increases Latitude
		for (int latitude = 0; latitude < (Segments + 1); latitude++)
		{
			//Calculates Next Latitude
			next_lati = angle_lati + Theta;

			//-------------------------First---------------------------

			//Vertex
			Vertex.push_back(Radius * cos(angle_lati) * sin(next_long)); 
			Vertex.push_back(Radius * cos(next_long));
			Vertex.push_back(Radius * sin(angle_lati) * sin(next_long));

			//Normals
			Normals.push_back(Radius * cos(angle_lati) * sin(next_long));
			Normals.push_back(Radius * cos(next_long));
			Normals.push_back(Radius * sin(angle_lati) * sin(next_long));

			//Texture Coordinates
			TexCoords.push_back(0.0f); 
			TexCoords.push_back(1.0f);

			//-------------------------Second---------------------------

			//Vertex
			Vertex.push_back(Radius * cos(angle_lati) * sin(angle_long));
			Vertex.push_back(Radius * cos(angle_long)); 
			Vertex.push_back(Radius * sin(angle_lati) * sin(angle_long));

			//Normals
			Normals.push_back(Radius * cos(angle_lati) * sin(angle_long)); 
			Normals.push_back(Radius * cos(angle_long));
			Normals.push_back(Radius * sin(angle_lati) * sin(angle_long));

			//Texture Coordinates
			TexCoords.push_back(0.0f);
			TexCoords.push_back(0.0f);
			
			//-------------------------Third---------------------------
			
			//Vertex
			Vertex.push_back(Radius * cos(next_lati) * sin(angle_long)); 
			Vertex.push_back(Radius * cos(angle_long)); 
			Vertex.push_back(Radius * sin(next_lati) * sin(angle_long));

			//Normals
			Normals.push_back(Radius * cos(next_lati) * sin(angle_long)); 
			Normals.push_back(Radius * cos(angle_long));
			Normals.push_back(Radius * sin(next_lati) * sin(angle_long));

			//Texture Coordinates
			TexCoords.push_back(1.0f);
			TexCoords.push_back(0.0f);
			
			//-------------------------Fourth---------------------------

			//Vertex
			Vertex.push_back(Radius * cos(next_lati) * sin(next_long)); 
			Vertex.push_back(Radius * cos(next_long));
			Vertex.push_back(Radius * sin(next_lati) * sin(next_long));

			//Normals
			Normals.push_back(Radius * cos(next_lati) * sin(next_long)); 
			Normals.push_back(Radius * cos(next_long));
			Normals.push_back(Radius * sin(next_lati) * sin(next_long));

			//Texture Coordinates
			TexCoords.push_back(1.0f); 
			TexCoords.push_back(1.0f);

			//Sets the Latitude as the next one
			angle_lati = next_lati;

		}
		//Calculates the next Longitude
		angle_long = next_long;
		next_long = angle_long + Delta;
	}

	//Calculates VertexCount
	m_VertexCount = Vertex.size() / 3;

	}




void ProceduralGeneration::GenerateDisc(int r, int seg)
{
	//Variable Initialization
	Theta = 0;
	Radius = r;
	Segments = seg;
	
	//Float Variables
	float interval = (2 * M_PI) / Segments;

	//For Loop for Face Calculation
	for (int i = 0; i < Segments; i++)
	{

		//Initial Colour of the Shape
		glColor3f(0.0f, 1.0f, 0.0f);
		
		//Begin Drawing the Triange Faces
		glBegin(GL_TRIANGLES);
		
		//First Face
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0, 0, 0);

		//Calculating x/y for coordinates
		x = Radius * cos(Theta);
		y = Radius * sin(Theta);

		//Second Face

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x, y, z);

		//Calculating x/y for coordinates
		x = Radius * cos(Theta + interval);
		y = Radius * sin(Theta + interval);

		//Third Face
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x, y, z);
		
		//End Drawing
		glEnd();

		//Add to Theta for next loop
		Theta += interval;
		
	}
}

void ProceduralGeneration::GenerateCylinder(int r, int seg)
{
	//Variable Initialization
	Radius = r;
	Segments = seg;

	//Float Variables
	float x = 0, y = 0, Angle = 0, Angle_StepSize = 0.1;

	//Draws the Tube
	glBegin(GL_QUAD_STRIP);

	//Angle initialization
	Angle = 0.0;

	//Set TexCoordinates
	glTexCoord2f(0.0f, 1.0f);

	//Loop for coordinates calculation
	while (Angle < 2 * M_PI)
	{
		//Calculates x/y coordinates for Vertex data
		x = Radius * cos(Angle);
		y = Radius * sin(Angle);
		
		
		//---------FIRST FACE----------
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x, y, Segments);

		//---------SECOND FACE---------
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x, y, 0.0);

		//Calculates the next Angle 
		Angle = Angle + Angle_StepSize;
	}

	//---------THIRD FACE----------
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(Radius, 0.0, Segments);

	//---------FOURTH FACE----------
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(Radius, 0.0, 0.0);

	glEnd();

}


	

