#pragma once

#include <gl/freeglut.h>
#include "Vector3D.h"
#include "Defines.h"
#include "ImageLoader.h"

using namespace std;

static GLuint floorTexture;
static GLuint leftTexture;
static GLuint rightTexture;
static GLuint frontTexture;
static GLuint roofTexture;

static const std::string floorTextureName = "floor.jpg";
static const std::string leftTextureName = "left.jpg";
static const std::string rightTextureName = "right.jpg";
static const std::string frontTextureName = "front.jpg";
static const std::string roofTextureName = "roof.jpg";

class Room{
private:
    int score[2];
public:
	Room(double level);
	~Room(void);
	void drawRoom();
	void drawWall(double x, double y, int parts, bool withTexture, GLuint texture, double textureFactor, bool inverseTexture,Vector3D normal);
};
