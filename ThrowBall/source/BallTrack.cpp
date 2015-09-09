#include "BallTrack.h"
#include "Bin.h"

BallTrack::BallTrack(Vector3D* curLoc, double strength, double shootAngle, Vector3D* centerLoc, double level) {

	//strength *= 0.8;
    scoredLocation = -1;
    scored = false;
    int collideNextPoint = 0;
    double step = (strength / 900);
    double xChange = centerLoc->getValueAt(X) - curLoc->getValueAt(X), zChange = centerLoc->getValueAt(Z) - curLoc->getValueAt(Z);
    double d = sqrt(pow(zChange, 2) + pow(xChange, 2));
    double zStep = (step * zChange / d) * cos(shootAngle * PI / 180),
            xStep = (step * xChange / d) * cos(shootAngle * PI / 180), yStep = (step) / cos(shootAngle * PI / 180);
    Vector3D curPos(curLoc);
    Vector3D accelVector(0.0, -0.002, 0.0);
    Vector3D speedVector(xStep, yStep, zStep);
    double ballDiameter = 0.27;
    Bin tempBin(0.6, level, 100); // A bin used just for calculation
    while (scored == false && (route.size() < 350)) {
        route.push_back(new Vector3D(curPos));
        string infoString;
        infoString = "";
        speedVector.add(accelVector);
        curPos.add(speedVector);
        if (curPos.getValueAt(X) >= 8 - ballDiameter || curPos.getValueAt(X) <= -8 + ballDiameter) { // Wall collision
            (curPos.getValueAt(X) < 0) ? curPos.setValueAt(X, -8 + ballDiameter) : curPos.setValueAt(X, 8 - ballDiameter);
            speedVector.changeDirection(X);
            speedVector.setValueAt(X, 0.9 * speedVector.getValueAt(X));
			// Debug
            // infoString = "Wall Hit";
        }
		if (curPos.getValueAt(Y) <= -1.7 || curPos.getValueAt(Y) >= 6) {							// Floor collision
            curPos.getValueAt(Y) < 0 ? curPos.setValueAt(Y, -1.7) : curPos.setValueAt(Y, 6);
            speedVector.changeDirection(Y);
            speedVector.setValueAt(Y, 0.7 * speedVector.getValueAt(Y)); 
			// Debug
            // infoString = "Floor Hit";
        }
        if (curPos.getValueAt(Z) <= 0.5 || curPos.getValueAt(Z) >= 16) {							// Front wall collision
            curPos.getValueAt(Z) <= 0.5 ? curPos.setValueAt(Z, 0.5) : curPos.setValueAt(Z, 16);
            speedVector.changeDirection(Z);
			// Debug
            // infoString = "Wall Hit";
        }

		// Collision with the bin
        if (collideNextPoint == 0) {
            if (curPos.getValueAt(Y) < 0.0 && curPos.getValueAt(Y) > -1.9 && curPos.getValueAt(X) < 1.3 && curPos.getValueAt(X) > -1.3 && curPos.getValueAt(Z) > 1.4 && curPos.getValueAt(Z) < 3.5) { // Bin area
                Vector3D binLoc(0.0, -1, 2.3);
                double closestLength = ballDiameter;
                int closestLocation = -1;
                for (int i = 0; i < tempBin.getfaces(); i++) {
                    Vector3D tempVector = tempBin.getVertexAt(i);
                    tempVector.add(binLoc);
                    double test = curPos.distance(tempVector);
                    if (test < closestLength) {
                        closestLocation = i;
                        closestLength = test;
                    }
                }
                if (closestLocation > 0) {
                    double mag = speedVector.getLength();
                    speedVector.normalize();
                    Vector3D normalVec = tempBin.getNormalAt(closestLocation);
                    double dotProd = -2 * (speedVector.dot(normalVec));
                    normalVec.setValueAt(X, normalVec.getValueAt(X) * dotProd);
                    normalVec.setValueAt(Y, normalVec.getValueAt(Y) * dotProd);
                    normalVec.setValueAt(Z, normalVec.getValueAt(Z) * dotProd);
                    normalVec.add(speedVector);
                    normalVec.setValueAt(X, normalVec.getValueAt(X) * mag * 0.8); 
                    normalVec.setValueAt(Y, normalVec.getValueAt(Y) * mag * 0.8);
                    normalVec.setValueAt(Z, normalVec.getValueAt(Z) * mag * 0.8);
                    speedVector = normalVec;
                    if (curPos.getValueAt(Y) < 1.4) collideNextPoint = 10;
                    else collideNextPoint = 3;
					// Debug
                    // infoString = "Bin hit";
                }
            }
        } else {
            collideNextPoint--;
        }

        //Scored?
        if (((curPos.getValueAt(Y) < -1.05 && curPos.getValueAt(Y) > -1.5))//-1.3
                && (((curPos.getValueAt(Z) > 1.9 && curPos.getValueAt(Z) < 2.6) && (curPos.getValueAt(X) < 0.4 && curPos.getValueAt(X)> -0.4) && speedVector.getValueAt(Y) < 0))) {
            // Debug
			// infoString = "Scores!!!";
            scored = true;
            if (scoredLocation < 0) scoredLocation = route.size();
        }
        if (infoString == "" && information.size() != 0) infoString = information[information.size() - 1];
        information.push_back(infoString);
    }
}

BallTrack::~BallTrack(void) {
    for (unsigned i = 0; i < route.size(); i++) {
        Vector3D* temp = route[i];
        delete temp;
    }
    route.clear();
}

Vector3D* BallTrack::getTrackPos(int pos) {
    return route[pos];
}

unsigned int BallTrack::getNumOfSteps() {
    return route.size();
}

bool BallTrack::throwScored() {
    return scored;
}

const char* BallTrack::getInfoPos(int pos) {
    return information[pos].c_str();
}

void BallTrack::showTrack() {
    for (unsigned i = 0; i <this->getNumOfSteps(); i++) {
        glPushMatrix();
        glTranslated(route[i]->getValueAt(X), route[i]->getValueAt(Y), route[i]->getValueAt(Z));
        glutWireSphere(0.02, 10, 10);
        glPopMatrix();
    }
}
