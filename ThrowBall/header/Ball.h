#pragma once

#include <cmath>
#include <gl/freeglut.h>
#include "Vector3D.h"
#include "BallTrack.h"
#include "defines.h"
#include "AssimpSimpleModelLoader.h"

using namespace std;

class Ball {
private:
	Vector3D* ballPos;
    BallTrack* myBallTrack;
    bool ballThrow;
    int inThrow;
    int phase;
    double chosenAngle;
    double chosenStrength;
    bool strengthUp;
    bool angleUp;
	bool _showTrack;
	double _level;
	bool _scored;
public:
    Ball(Vector3D* pos, double level);
    Vector3D* getBallPos();
    Vector3D* getBallColor();
    void setBallPos(Vector3D* newPos);
    void setBallPos(double newx, double newy, double newz);
    void throwBall(Vector3D* cenLoc);
	void drawBall(Vector3D* playerLocation, Vector3D* eyeInfo, AssimpSimpleModelLoader *loader);
    bool ballInTheAir();
    int getPhase();
    void setPhase(int phaseNr);
    void resetBall();
    void setInThrow(int progress);
    int getInThrow();
    void displayInformation(double angle);
	void displayProgress(int pos);
	void showTrack();
	bool getScored();
};
