#pragma once

#include <cmath>
#include "Ball.h"
#include "Vector3D.h"
#include "defines.h"

#include "AssimpSimpleModelLoader.h"

using namespace std;

class Player
{
private:
	Vector3D* lookAtEye;
	Vector3D* lookAtCenter;
	Vector3D* posLastThrow;
	bool lastThrowIn;
	Ball* myBall;
	bool canMoveX(int direction);
	bool canMoveZ(int direction);
	double calcDistance();
    int score;
	int throws;
public:
	Player(double level);
	void restart(double level);
	Vector3D* getLookAtEye();
	Vector3D* getLookAtCenter();
	void moveForwardBack(int direction);
	void moveRightLeft(int direction);
	void lookX(int direction);
	void lookY(int direction);
	void drawPlayerState(AssimpSimpleModelLoader *loader);
	void throwBall(AssimpSimpleModelLoader *loader);
	void throwBall();
	void resetBall(AssimpSimpleModelLoader *loader);
	void setPhase(int num);
	int getPhase();
	Vector3D* getBallPos();
    void setPosition(Vector3D* newPosition);
    void setScore();
    int getScore();
	int getThrows();
	char* shotStatus();
	bool ballInTheAir();
	void showTrack();
};
