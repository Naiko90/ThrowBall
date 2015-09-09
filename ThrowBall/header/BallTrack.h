#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <gl/freeglut.h>
#include "Vector3D.h"
#include "Defines.h"
#include "Bin.h"

using namespace std;

class BallTrack {
private:
    vector<Vector3D*> route;
	vector<string> information;
    bool scored;
    int scoredLocation;
public:
    BallTrack();
    BallTrack(Vector3D* curLocation, double strength, double startingAngle, Vector3D* centerLocation, double level);
    ~BallTrack(void);
    Vector3D* getTrackPos(int pos);
	const char* getInfoPos(int pos);
    unsigned int getNumOfSteps();
    bool throwScored();
	void showTrack();
};
