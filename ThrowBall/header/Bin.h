#ifndef _BIN_H
#define	_BIN_H
#include <cmath>
#include <gl/freeglut.h>
#include "Vector3D.h"
#include "Defines.h"
#include "AssimpSimpleModelLoader.h"

class Bin {
public:
    Bin(double bigR, double smallR, int faces);
	void drawBin(AssimpSimpleModelLoader* loader);
    int getfaces();
    Vector3D getVertexAt(int pos);
    Vector3D getNormalAt(int pos);
private:
    Vector3D* _vertaxList;
    Vector3D* _normalList;
    int** faceLocation;
    int _faces;
};

#endif	/* _BIN_H */

