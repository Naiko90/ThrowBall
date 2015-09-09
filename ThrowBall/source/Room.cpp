#include "Room.h"

Room::Room(double level) {

	// Load all the textures
	floorTexture = loadImage((resourceDir + "/" + floorTextureName).c_str(), true);
	leftTexture = loadImage((resourceDir + "/" + leftTextureName).c_str(), true);
	rightTexture = loadImage((resourceDir + "/" + rightTextureName).c_str(), false);
	frontTexture = loadImage((resourceDir + "/" + frontTextureName).c_str(), true);
	roofTexture = loadImage((resourceDir + "/" + roofTextureName).c_str(), true);

}

Room::~Room(void) {
}

void Room::drawWall(double x, double y, int parts, bool withTexture, GLuint texture,
        double textureFactor, bool inverseTexture,Vector3D normal) {

    double textureChange = 0;
	double xChange = x / parts;
    double yChange = y / parts;

    if (withTexture) {
        textureChange = textureFactor / parts;
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    glPushMatrix();
    {
        glNormal3d(normal.getValueAt(X),normal.getValueAt(Y),normal.getValueAt(Z));
        glBegin(GL_QUADS);
        {
            for (int j = 0; j < parts; j++) {
                for (int i = 0; i < parts; i++) {
                    if (withTexture) {
                        if (inverseTexture) glTexCoord2f((j) * textureChange, i * textureChange);
                        else glTexCoord2f((i) * textureChange, j * textureChange);
                    }
                    glVertex3f((i) * xChange, 0.0, j * yChange);
                    if (withTexture) {
                        if (inverseTexture) glTexCoord2f((j + 1) * textureChange, (i) * textureChange);
                        else glTexCoord2f((i) * textureChange, (j + 1) * textureChange);
                    }
                    glVertex3f((i) * xChange, 0.0, (j + 1) * yChange);
                    if (withTexture) {
                        if (inverseTexture) glTexCoord2f((j + 1) * textureChange, (i + 1) * textureChange);
                        else glTexCoord2f((i + 1) * textureChange, (j + 1) * textureChange);
                    }
                    glVertex3f((i + 1) * xChange, 0.0, (j + 1) * yChange);
                    if (withTexture) {
                        if (inverseTexture) glTexCoord2f((j) * textureChange, (i + 1) * textureChange);
                        else glTexCoord2f((i + 1) * textureChange, (j) * textureChange);
                    }
                    glVertex3f((i + 1) * xChange, 0.0, (j) * yChange);
                }
            }
        }
        glEnd();
    }
    glPopMatrix();

    if (withTexture) glDisable(GL_TEXTURE_2D);
}

void Room::drawRoom() {

    Vector3D normal(0.0,1.0,0.0);
    
	// Floor
    glPushMatrix();
    glTranslated(-8.0, -2.0, 0.0);
    drawWall(22, 22, 100, true, floorTexture, 1, true, normal);
    glPopMatrix();

    // Roof
    glPushMatrix();
    glTranslated(8.0, 6.0, 0.0);
    glRotated(180.0, 0, 0, 1);
    drawWall(22, 22, 100, true, roofTexture, 2, false, normal);
    glPopMatrix();

    // Left
    glPushMatrix();
    glTranslated(-8.0, 6.0, 0.0);
    glRotated(-90.0, 0, 0, 1);
    drawWall(17, 30, 100, true, leftTexture, 2, true, normal);
    glPopMatrix();

    // Right
    glPushMatrix();
    glTranslated(8.0, -2.65, 0.0);
    glRotated(90.0, 0, 0, 1);
    drawWall(21, 30, 100, true, rightTexture, 2, true, normal);
    glPopMatrix();

    // Front
    glPushMatrix();
    glTranslated(-8.0, 6.0, 0.0);
    glRotated(90.0, 1, 0, 0);
    drawWall(32, 17, 100, true, frontTexture, 2, false, normal);
    glPopMatrix();

}
