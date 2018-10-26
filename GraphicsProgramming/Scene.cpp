#include "Scene.h"

//Float Variables
float Rotation;
float RotationSpeed = 0.1;
float PillarTimer = -40.0;
float CameraAnimation = 0;;

//Bool Variables
bool PillarFlag = false;
bool MouseInitialize = false;
bool FixedCamera = false;
bool AnimatedCamera = false;
bool EnableTimer = false;
bool wireframe = false;

Scene::Scene(Input *in)
{
	// Store pointer for input class

	input = in;
	camera = new Camera;
	

	//----------------------------------------------------------------------------
	//Textures Loading
	sky = SOIL_load_OGL_texture
	(
		"gfx/Sky.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	ArenaFloor = SOIL_load_OGL_texture
	(
		"gfx/ArenaFloor.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	Pillar = SOIL_load_OGL_texture
	(
		"gfx/Pillar.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);


	//----------------------------------------------------------------------------
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glEnable(GL_STENCIL_TEST);							// Enables the Stencil Test
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //Enables the use of Blending
		//Enable Lighting and Initialize for the Starting Sky Colours
	GLfloat Light_Diffuse_Dire[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse_Dire);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//Texture Settings
	glEnable(GL_TEXTURE_2D); //Enables 2D Textures
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//Generate the base arena, once so it doesn't destroy the performance
	ShapeGeneration.GenerateHalfSphere(20, 50);
	Vegeta.load("Models/Vegeta/1.obj", "Models/Vegeta/Face.png");
	Goku.load("Models/Goku/Goku.obj", "Models/Goku/Face.png");

	//BGM
	PlaySound(TEXT("sfx/Golden.wav"), NULL, SND_ASYNC);
}

void Scene::update(float dt)
{
	//Light for SkyChanging Colours
	

	//Animation for the Pillar in the middle going up and down through the Arena.
	if (PillarTimer >= -40 && EnableTimer == true)
	{
		PillarFlag = false;
	}
	 if (PillarTimer <= -65 && EnableTimer == true)
	{
		PillarFlag = true;
	}
	if (PillarFlag == false && EnableTimer == true)
	{
		PillarTimer = PillarTimer - 0.01;
		GLfloat Light_Diffuse_Dire[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse_Dire);
	
	}
	if (PillarFlag == true && EnableTimer == true)
	{
		PillarTimer = PillarTimer + 0.01;
		GLfloat Light_Diffuse_Dire_Green[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse_Dire_Green);
	}
	//--------------ROTATION SPEED-----------
     Rotation += RotationSpeed * dt;
	//--------------INPUT-------------

	 //Button to enable the Arena Timer to start ticking
	 if (input->isKeyDown('g'))
	 {
		 EnableTimer = !EnableTimer;
		 input->SetKeyUp('g');
	 }
	// Toggles wireframe on/off
	if (input->isKeyDown('r') )
	{
		wireframe = !wireframe;
		input->SetKeyUp('r');
	}
	//Move Forward
	if (input->isKeyDown('w') && camera->getPosition().x >-8 && FixedCamera==false)
	{
		camera->moveForward(dt);
		input->SetKeyUp('w');
	}

	//Move Backwards
	if (input->isKeyDown('s') && FixedCamera == false)
	{
		camera->moveBackwards(dt);
		input->SetKeyUp('s');
	}
	//Move Right
	if (input->isKeyDown('d') && camera->getPosition().x >-8 && FixedCamera == false)
	{
		camera->moveRight(dt);
		input->SetKeyUp('d');
	}
	//Move Left
	if (input->isKeyDown('a') && camera->getPosition().x >-8 && FixedCamera == false)
	{
		camera->moveLeft(dt);
		input->SetKeyUp('a');
	}
	//Move Down
	if (input->isKeyDown('q') && camera->getPosition().x >-8 && FixedCamera == false)
	{
		camera->moveDown(dt);
		input->SetKeyUp('q');
	}
	//Move Up
	if (input->isKeyDown('e') && camera->getPosition().x >-8 && FixedCamera == false)
	{
		camera->moveUp(dt);
		input->SetKeyUp('e');
		
	}
	//Camera Reset
	if (input->isKeyDown('f'))
	{
		CameraAnimation=0;
		glutWarpPointer(700, 810);
		camera->CameraReset();
		FixedCamera = false;
		AnimatedCamera = false;
		input->SetKeyUp('f');
	}

	//First Camera - Fixed
	if (input->isKeyDown('u'))
	{
		CameraAnimation = 0;
		camera->setXrotation(-1110);
		camera->setYrotation(300);
		camera->FirstCamera();
		FixedCamera = true;
		AnimatedCamera = false;
		input->SetKeyUp('u');
	}
	//Second Camera - Fixed
	if (input->isKeyDown('i'))
	{
		CameraAnimation = 0;
		camera->setXrotation(-1165);
		camera->setYrotation(650);
		camera->SecondCamera();
		FixedCamera = true;
		AnimatedCamera = false;
		input->SetKeyUp('i');
	}
	//Second Camera - Animated Camera
	if (input->isKeyDown('o'))
	{
		CameraAnimation = 0;
		FixedCamera = false;
		AnimatedCamera = true;
		camera->setXrotation(-1050);
		
		camera->ThirdCamera();
		input->SetKeyUp('o');
	}

	//-------------INPUT OVER------------

	//Mouse Controls for Turning X/Y, no flipped controls
	if (FixedCamera==false && AnimatedCamera == false)
	{
		camera->setXrotation(-input->getMouseY() - 300);
		camera->setYrotation(input->getMouseX() - 400);
	}	//Calculates the speed for the animated camera	if (AnimatedCamera==true && FixedCamera==false)
	{
		CameraAnimation += 0.03;
	
	}
	if (AnimatedCamera==true)
	{
		camera->setYrotation(575 - CameraAnimation);
	}
	//Handling Wireframe
		if (wireframe == true) {
			glPolygonMode(GL_FRONT, GL_LINE);
		}
		if (wireframe == false) {
			glPolygonMode(GL_FRONT, GL_FILL);
		}
	
	// Calculates FPS for output
	calculateFPS();
	camera->update();
}
void Scene::renderArena() 
{
	
	//Pushing Matrix
	glPushMatrix();

	//Flipping it on the X axis
	glRotatef(180, 1.0f, 0.0f, 0.0f);

	//Rendering the HalfSphere from our Procedural Generation object
	ShapeGeneration.Render();
	//Popping Matrix
	glPopMatrix();
	//Pushing the Matrix
	glPushMatrix();

	//Texture Setup for the Arena Floor (Disc)
	glBindTexture(GL_TEXTURE_2D, ArenaFloor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	//Flipping the ArenaFloor (Disc) and Moving it downwards to match the exact position of the Half Sphere and cover it
	glTranslatef(0.0f, -1.25f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);

	//Generating the Arena Floor (Disc)
	ShapeGeneration.GenerateDisc(20, 30);

	glBindTexture(GL_TEXTURE_2D, NULL);
	//Popping the Matrix
	glPopMatrix();

	//Pushing the Matrix
	glPushMatrix();

	//Cylinder Texture
	glBindTexture(GL_TEXTURE_2D, Pillar);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	//Translating the Cylinder downwards so it pierces the Stage
	glTranslatef(0.0f, PillarTimer, 0.0f);

	//Rotates the Cylinder so it's Vertical on the Stage
	GLfloat Light_Position_SpotS[] = { -10.0f, 0.0f, 6.0f, 1.0f };

	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	
	//Function to Generate the Cylinder
	ShapeGeneration.GenerateCylinder(1, 60);
	glPopMatrix();
	
	//Vegeta Model SetUp
	glPushMatrix();
	glTranslatef(5.0f, -1.0, 0.0f);	glScalef(0.01f, 0.01f, 0.01f);		Vegeta.render();
	glPopMatrix();

	//Goku Model SetUp
	glTranslatef(8.0f, -1.0, 0.0f);	glScalef(0.05f, 0.05f, 0.05f);
	Goku.render();

	
}
void Scene::render() {

	//Initializing the starting mouse position once so the camera starts in the "Reset Position"
	if (MouseInitialize == false)	{		glutWarpPointer(700, 810);		MouseInitialize = true;	}

	// Clear Color, Depth and Stencil Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the Camera
	gluLookAt(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z, camera->getLookAt().x, camera->getLookAt().y, camera->getLookAt().z, camera->getUp().x, camera->getUp().y, camera->getUp().z);
	
	//--------------------LIGHT SOURCES START--------------------


	//SpotLight
	GLfloat Light_Ambient_Spot[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat Light_Diffuse_Spot[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position_Spot[] = { -10.0f, 0.0f, 6.0f, 1.0f };
	GLfloat spot_Direction_Spot[] = { 0.0f, -1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient_Spot);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse_Spot);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position_Spot);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 95.0f);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_Direction_Spot);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 00.0);
	
	//Directional Light (Enabled only for Skybox, illuminates the whole Sky)
	GLfloat Light_Ambient_Dire[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat Light_Diffuse_Dire[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position_Dire[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat spot_Direction_Dire[] = { 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient_Dire);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position_Dire);
	
	//--------------------LIGHT SOURCES END--------------------

	//-----------------------SKYBOX SETUP---------------------

	//SkyBox Texture Setup
	glBindTexture(GL_TEXTURE_2D, sky);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	
	//Push Matrix for Skybox
	glPushMatrix();
	
	//Move according to camera position
	glTranslatef(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);

	//Depth Test Disabling
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT1);
	//Begin Drawing the 6 faced cube
	glBegin(GL_QUADS);
	
	//FRONT FACE
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(0.5, -0.5, 0.5);

	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(0.5, 0.5, 0.5);

	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(-0.5, 0.5, 0.5);

	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-0.5, -0.5, 0.5);
	

	//BACK FACE
	
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(0.5, -0.5, -0.5);

	glTexCoord2f(1.0f, 0.25f);
	glVertex3f(0.5, 0.5, -0.5);

	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(-0.5, 0.5, -0.5);

	glTexCoord2f(0.75f, 0.5f);
	glVertex3f(-0.5, -0.5, -0.5);

	

	//LEFT FACE
	
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(0.5, -0.5, -0.5);

	glTexCoord2f(0.0f, 0.25f);
	glVertex3f(0.5, 0.5, -0.5);

	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(0.5, 0.5, 0.5);

	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(0.5, -0.5, 0.5);


	//RIGHT FACE
	
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-0.5, -0.5, 0.5);

	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(-0.5, 0.5, 0.5);

	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(-0.5, 0.5, -0.5);

	glTexCoord2f(0.75f, 0.5f);
	glVertex3f(-0.5, -0.5, -0.5);


	//TOP FACE

	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(0.5, 0.5, 0.5);

	glTexCoord2f(0.25f, 0.f);
	glVertex3f(0.5, 0.5, -0.5);

	glTexCoord2f(0.5f, 0.f);
	glVertex3f(-0.5, 0.5, -0.5);

	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(-0.5, 0.5, 0.5);


	//BOTTOM FACE

	glTexCoord2f(0.25f, 0.75f);
	glVertex3f(0.5, -0.5, -0.5);

	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(0.5, -0.5, 0.5);

	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-0.5, -0.5, 0.5);

	glTexCoord2f(0.5f, 0.75f);
	glVertex3f(-0.5, -0.5, -0.5);

	//Drawing End
	glEnd();

	//Enabling Depth Testing 
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHT1);
	//Poppping the Matrix
	glPopMatrix();
	glScalef(0.3f, 0.3f, 0.3f);
	//-------------SET UP REFLECTION-----------------
	//Turn off writing to the Frame Buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	//Enable the Stencil Test
	glEnable(GL_STENCIL_TEST);
	//Set the Stencil Function to always pass
	glStencilFunc(GL_ALWAYS, 1, 1);	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//Disables Depth Test
	glDisable(GL_DEPTH_TEST);
	//Unbinds current selected Texture
	glBindTexture(GL_TEXTURE_2D, NULL);
	//Pushes the Matrix
	glPushMatrix();
	//Decides where the wall will be built
	glTranslatef(-30, 0, 0);
	//Rotates it so it's vertical
	glRotatef(90, 0, 1, 0);
	//Begin drawing Stencil 
	glBegin(GL_QUADS);

	glVertex3f(-50, 50, 0);

	glVertex3f(-50, -50, 0);

	glVertex3f(50, -50, 0);

	glVertex3f(50, 50, 0);
	//Stops Drawing the Wall
	glEnd();
	//Pops the Matrix
	glPopMatrix();

	//Enables the Depth Test
	glEnable(GL_DEPTH_TEST);
	//Turn on rendering to the Frame Buffer
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	//Set Stencil Function to test if the value is 1
	glStencilFunc(GL_EQUAL, 1, 1);	//Set the Stencil Operation to keep all values (we don't want to change the Stencil)	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	//Pushes the Matrix
	glPushMatrix();	//Flips the Scale Horizontaly and move the spawning position of the Reflection on the X axis
	glScalef(-1.0, 1.0, 1.0);	glTranslatef(60, 0, 0);
	
	//Tilts the Reflection
	glRotatef(15, 0, 0, 1);
	//Starts Rotating the Reflection
	glRotatef(Rotation, 0, 1, 0);


	//Generate the Reflection
	renderArena();

	//Pops the Matrix
	glPopMatrix();
	//Disables the Stencil Test
	glDisable(GL_STENCIL_TEST);
	//Enables Blending
	glEnable(GL_BLEND);
	//Disables Lighting and sets the Colour for the Wall (DarkSlateBlue)
	glDisable(GL_LIGHTING);	glColor4f(0.282f, 0.239f, 0.545f, 0.1f);
	//Pushes the Matrix
	glPushMatrix();

	//Chooses where to draw the Wall
	glTranslatef(-30, 0, 0);
	//Rotates the Wall so it's Vertical
	glRotatef(90, 0, 1, 0);

	//Starts drawing the Wall
	glBegin(GL_QUADS);

	glVertex3f(-50, 50, 0);

	glVertex3f(-50, -50, 0);

	glVertex3f(50, -50, 0);

	glVertex3f(50, 50, 0);
	//Stops drawing the Wall
	glEnd();
	//Pops the Matrix
	glPopMatrix();
	
	//Enables Lighting
	glEnable(GL_LIGHTING);
	//Disables Blending
	glDisable(GL_BLEND);	//Pushes the Matrix	glPushMatrix();	//------------- END OF REFLECTION -----------------	//------------- START OF REAL ARENA ---------------	//Starts Rotating the actual Arena before it's built and tilts it 15 Degrees on the Z axis
	glRotatef(15, 0, 0, 1);	glRotatef(Rotation, 0, 1, 0);
	//Generates the Actual Arena
	renderArena();
	
	//------------- END OF REAL ARENA -----------------	
	//Disable Cursor
	glutSetCursor(GLUT_CURSOR_NONE);

	// Text Render (Last thing rendering on Screen)
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	
}

// Calculates FPS
void Scene::calculateFPS()
{

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
