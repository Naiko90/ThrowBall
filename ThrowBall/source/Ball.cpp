#include "Ball.h"

using namespace std;

Ball::Ball(Vector3D* pos, double level) {
    this->ballPos = pos;
    this->ballThrow = false;
    this->inThrow = 0;
    this->chosenStrength = 30;
    this->chosenAngle = 30;
    this->phase = 0;
    this->strengthUp = true;
    this->angleUp = true;
	this->myBallTrack = NULL;
	this->_level = level;
	this->_showTrack = false;
	this->_scored = false;
}

void Ball::resetBall() {
    this->ballThrow = false;
}

Vector3D* Ball::getBallPos() {
    return this->ballPos;
}

void Ball::setBallPos(Vector3D *newPos) {
    this->ballPos = newPos;
}

void Ball::drawBall(Vector3D* playerLocation, Vector3D* eyeInfo, AssimpSimpleModelLoader *loader) {
    if (this->ballThrow) {
		if (this->inThrow <= 1) {
            this->ballThrow = false;
        }
		if(_showTrack) myBallTrack->showTrack();
		// Debug
		// displayProgress(myBallTrack->getNumOfSteps() - this->inThrow);
    } else {
        double changeX = eyeInfo->getValueAt(X) - playerLocation->getValueAt(X);
        double changeZ = eyeInfo->getValueAt(Z) - playerLocation->getValueAt(Z);
        double dist = sqrt(pow(changeX, 2) + pow(changeZ, 2));
        double newX = 2 * changeX / dist + playerLocation->getValueAt(X);
        double newZ = 2 * changeZ / dist + playerLocation->getValueAt(Z);
        this->ballPos->setValueAt(X, newX);
        this->ballPos->setValueAt(Y, 0);
        this->ballPos->setValueAt(Z, newZ);
    }
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslated(ballPos->getValueAt(X), ballPos->getValueAt(Y), ballPos->getValueAt(Z));
	glDisable(GL_TEXTURE_2D);
	loader->recursive_render(loader->getScene(),loader->getScene()->mRootNode->FindNode("Palla"));
	glEnable(GL_COLOR_MATERIAL);
    
	// Cone used to allow the user to select the strength and the angle 
    if (phase != 0) {
        if (phase == 1) {
            if (angleUp) chosenAngle += 0.5;
            else chosenAngle -= 0.5;

            if (chosenAngle >= 80) angleUp = false;
            else if (chosenAngle <= 30) angleUp = true;
        } else {
            if (strengthUp) chosenStrength += 0.6;
            else chosenStrength -= 0.6;

            if (chosenStrength >= 80) strengthUp = false;
            else if (chosenStrength <= 1) strengthUp = true;
        }
        double xInfo = (playerLocation->getValueAt(X) - eyeInfo->getValueAt(X));
        double zInfo = playerLocation->getValueAt(Z) - eyeInfo->getValueAt(Z);
        double distance = sqrt(pow(xInfo, 2) + pow(zInfo, 2));
        double sinA = sin(xInfo / distance);
        double angle = asin(sinA)*(180 / PI);
		// Debug
        // displayInformation(angle);
        glRotated(angle, 0, 1, 0);
        glRotated(180 + chosenAngle, 1, 0, 0);
        glColor3d(1, 0, 0);
        glutSolidCone(0.25, chosenStrength / 10, 10, 30);
    }
	glPopMatrix();
    glDisable(GL_CULL_FACE);
    
	// Simple shadow
    glPushMatrix();
    glTranslated(ballPos->getValueAt(0), -1.9, ballPos->getValueAt(2));
    glRotated(90, 0, 1, 0);
    glRotated(90, 1, 0, 0);
    glColor3d(0.0, 0.0, 0.0);
    glutSolidCone(0.3, 0.1, 10, 10);
    glPopMatrix();
    glEnable(GL_CULL_FACE);
}

void Ball::throwBall(Vector3D* cenLoc) {
    //if(myBallTrack!=NULL) delete myBallTrack;
    myBallTrack = NULL;
	myBallTrack = new BallTrack(this->ballPos, chosenStrength, chosenAngle, cenLoc, this->_level);
    this->ballThrow = true;
    this->inThrow = myBallTrack->getNumOfSteps();
	//Score
	if(myBallTrack->throwScored()) _scored = true;
}

bool Ball::ballInTheAir() {
    return this->ballThrow;
}

int Ball::getPhase() {
    return this->phase;
}

void Ball::setPhase(int phaseNr) {
    this->phase = phaseNr;
    if (phaseNr == 0) {
        this->chosenStrength = 30;
        this->chosenAngle = 30;
    }
}

void Ball::setInThrow(int progress) {
    if (!((unsigned) (this->inThrow - progress) > myBallTrack->getNumOfSteps()))
        this->inThrow -= progress;
    if (this->inThrow > 1) setBallPos(myBallTrack->getTrackPos((myBallTrack->getNumOfSteps()) - this->inThrow));
    else this->inThrow = 1;
}

int Ball::getInThrow() {
    return this->inThrow;
}

bool Ball::getScored() {
	bool temp = _scored;
	_scored = false;
	return temp;
}

void Ball::displayInformation(double angle) {
    char* string = new char[100];
    char *c;
    sprintf_s(string, 100, "Angolazione: %.3f, Forza: %.3f", chosenAngle, chosenStrength);
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glDisable(GL_LIGHTING);
    glScalef(0.001, 0.001, 1);
    glLineWidth(3.0);
    //glTranslated(-1000.0, 300.0, 1);
	glTranslated(-1000.0 + ballPos->getValueAt(X), 300.0 + ballPos->getValueAt(Y), 1);
	glRotated(angle, 0, 0, 1);
    for (c = string; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Ball::displayProgress(int pos) {
    glPushMatrix();
    glColor3d(1.0,0.8,0.8);
    glDisable(GL_LIGHTING);
    glScalef(0.004, 0.004, 1);
    glLineWidth(2.0);
    glTranslated(-1000.0, 500.0, 0.5);
	const char *c;
    for (c = myBallTrack->getInfoPos(pos); *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Ball::showTrack() {
	this->_showTrack = !_showTrack;
}
