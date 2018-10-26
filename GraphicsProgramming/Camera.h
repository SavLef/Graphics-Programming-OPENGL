#pragma once
#include "Vector3.h"
class Camera
{
public:
	Camera();
	~Camera();

	void  update();

	//Setter Functions
	void setPosition(Vector3 NewPosition);
	void setOrientation(Vector3 NewOrientation);
	void setLookAt(Vector3 NewLookAt);
	void setUp(Vector3 NewUp);
	void setForward(Vector3 NewForward);
	void setRight(Vector3 NewRight);

	void setXrotation(float x);
	void setYrotation(float y);
	void setZrotation(float z);

	//Movement Functions
	void moveForward(float dt);
	void moveBackwards(float dt);
	void moveRight(float dt);
	void moveLeft(float dt);
	void moveUp(float dt);
	void moveDown(float dt);

	//Different Camera Functions
	void CameraReset();
	void FirstCamera();
	void SecondCamera();
	void ThirdCamera();

	//Getter Functions
	Vector3 getPosition();
	Vector3 getOrientation();
	Vector3 getLookAt();
	Vector3 getUp();
	Vector3 getForward();
	Vector3 getRight();


	//Vector Variables
	Vector3 Orientation, Position, LookAt, Up, Forward, Right;
	
	//Float Variables
	float Speed = 5;
};

