#include "Camera.h"


//Constructor
Camera::Camera()
{
	//Initialize Values for the Camera in the Constructor
	setPosition(Vector3(10.0f, 5.0f, 5.0f));
	setLookAt(Vector3(0.0f, 0.0f, 0.0f));
	setUp(Vector3(0.0f, 1.0f, 0.0f));
	setForward(Vector3(0.0f, 0.0f, 0.0f));
	setRight(Vector3(0.0f, 0.0f, 0.0f));
	setUp(Vector3(0.0f, 0.0f, 0.0f));
	setOrientation(Vector3(0.0f, 0.0f, 0.0f));

}


Camera::~Camera()
{
}

void Camera::update() {
		
		//Float Variables
		float cosR, cosP, cosY; 
		float sinR, sinP, sinY;
		
		//Variables used for Maths
		cosY = cosf(Orientation.y*3.1415/180); 
		cosP = cosf(Orientation.x*3.1415/180); 
		cosR = cosf(Orientation.z*3.1415/180); 
		sinY = sinf(Orientation.y*3.1415/180);
		sinP = sinf(Orientation.x*3.1415/180);
		sinR = sinf(Orientation.z*3.1415/180);

		//Calculating the Forward X/Y/Z values
		Forward.x = sinY * cosP; 
		Forward.y = sinP;
		Forward.z = cosP * -cosY;

		//Look at Calculation
		LookAt = Forward + Position;
		
		//Calculating the Up X/Y/Z values
		Up.x = -cosY * sinR - sinY * sinP * cosR;
		Up.y = cosP * cosR;
		Up.z = -sinY * sinR - sinP * cosR * -cosY;

		//Right of Camera
		Right = Forward.cross(Up); //This is the cross product of Forward and Up
}

//-----------------Position--------------------
void Camera::setPosition(Vector3 NewPosition)
{
	Position = NewPosition;
}

Vector3 Camera::getPosition()
{
	return Position;
}


//-----------------Orientation--------------------
void Camera::setOrientation(Vector3 NewOrientation)
{
	Orientation = NewOrientation;
}

Vector3 Camera::getOrientation()
{
	return Orientation;
}
//-----------------LookAt--------------------
void Camera::setLookAt(Vector3 NewLookAt)
{
	LookAt = NewLookAt;
}

Vector3 Camera::getLookAt()
{
	return LookAt;
}
//-----------------Up--------------------
void Camera::setUp(Vector3 NewUp)
{
	Up = NewUp;
}

Vector3 Camera::getUp()
{
	return Up;
}
//-----------------Forward--------------------
void Camera::setForward(Vector3 NewForward)
{
	Forward = NewForward;
}

Vector3 Camera::getForward()
{
	return Forward;
}
//-----------------Right--------------------
void Camera::setRight(Vector3 NewRight)
{
	Right = NewRight;
}

Vector3 Camera::getRight()
{
	return Right;
}
//----------------X Rotation----------------
void Camera::setXrotation(float xRotation)
{
	Orientation.x=xRotation;
}
//----------------Y Rotation----------------
void Camera::setYrotation(float yRotation)
{
	Orientation.y = yRotation;
}
//----------------Z Rotation----------------
void Camera::setZrotation(float zRotation)
{
	Orientation.z = zRotation;
}

//-------------Movement Forward-------------
void Camera::moveForward(float dt)
{
	Position.x += Forward.x*Speed*dt;
	Position.y += Forward.y*Speed*dt;
	Position.z += Forward.z*Speed*dt;
}
//-------------Movement Up-----------------
void Camera::moveUp(float dt)
{
	
	Position.y += Up.y*Speed*dt;

}
//-------------Movement Backwards----------
void Camera::moveBackwards(float dt)
{
	Position.x -= Forward.x*Speed*dt;
	Position.y -= Forward.y*Speed*dt;
	Position.z -= Forward.z*Speed*dt;
}
//-------------Movement Right--------------
void Camera::moveRight(float dt)
{
	Position.x += Right.x*Speed*dt;
	Position.y += Right.y*Speed*dt;
	Position.z += Right.z*Speed*dt;
}
//-------------Movement Left---------------
void Camera::moveLeft(float dt)
{
	Position.x -= Right.x*Speed*dt;
	Position.y -= Right.y*Speed*dt;
	Position.z -= Right.z*Speed*dt;
}
//-------------Movement Down---------------
void Camera::moveDown(float dt)
{	
	Position.y -= Up.y*Speed*dt;
}

//--------------Camera Reset---------------
void Camera::CameraReset()
{
setPosition(Vector3(10.0f, 5.0f, 5.0f));
setLookAt(Vector3(0.0f, 0.0f, 0.0f));
setUp(Vector3(0.0f, 1.0f, 0.0f));
}
//----------First Camera Function----------
void Camera::FirstCamera()
{
	setPosition(Vector3(50.0f, 38.0f, 55.0f));
	setLookAt(Vector3(5.0f, 10.0f, 30.0f));
	setUp(Vector3(0.0f, 1.0f, 0.0f));
}
//----------Second Camera Function----------
void Camera::SecondCamera()
{
	setPosition(Vector3(5.0f, 90.0f, 9.0f));
	setLookAt(Vector3(0.0f, 0.0f, 0.0f));
	setUp(Vector3(0.0f, 10.0f, 0.0f));
}
//----------Third Camera Function----------
void Camera::ThirdCamera()
{
	setPosition(Vector3(35.0f, -50.0f, -60.0f));
	setLookAt(Vector3(0.0f, 0.0f, 0.0f));
	setUp(Vector3(0.0f, 1.0f, 0.0f));
}