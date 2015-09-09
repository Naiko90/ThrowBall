#include "Bin.h"

Bin::Bin(double bigR, double smallR, int faces) {
    double uAngle = 0.0, vAngle = 0.0;
    double angleChange = (double) 360 / (double) faces;
    this->_faces = faces*faces;

    this->_vertaxList = new Vector3D [faces * faces];
    this->_normalList = new Vector3D [faces * faces];
    for (int i = 0; i < faces; i++) {
        for (int j = 0; j < faces; j++) {
            _vertaxList[j + i * faces].setValueAt(X, (bigR + smallR * cos(vAngle * PI / 180)) * cos(uAngle * PI / 180));
            _vertaxList[j + i * faces].setValueAt(Z, (bigR + smallR * cos(vAngle * PI / 180)) * sin(uAngle * PI / 180));
            _vertaxList[j + i * faces].setValueAt(Y, 0.7 * sin(vAngle * PI / 180));
            vAngle += angleChange;
        }
        vAngle = 0;
        uAngle += angleChange;
    }

    faceLocation = new int* [_faces];
    for (int i = 0; i < _faces; i++) faceLocation[i] = new int[4];

    for (int i = 0; i < faces; i++) {
        for (int j = 0; j < faces; j++) {
            faceLocation[j + i * faces][0] = (j + i * faces) % (_faces);
            faceLocation[j + i * faces][1] = ((j + 1) % faces + i * faces) % (_faces);
            faceLocation[j + i * faces][2] = ((j + 1) % faces + faces + i * faces) % (_faces);
            faceLocation[j + i * faces][3] = (j + faces + i * faces) % (_faces);
        }
    }

    // Normalize
    for (int i = 0; i < faces * faces; i++) {
        Vector3D vec1(_vertaxList[faceLocation[i][0]].getValueAt(X) - _vertaxList[faceLocation[i][1]].getValueAt(X),
                      _vertaxList[faceLocation[i][0]].getValueAt(Y) - _vertaxList[faceLocation[i][1]].getValueAt(Y),
                      _vertaxList[faceLocation[i][0]].getValueAt(Z) - _vertaxList[faceLocation[i][1]].getValueAt(Z));
        Vector3D vec2(_vertaxList[faceLocation[i][0]].getValueAt(X) - _vertaxList[faceLocation[i][2]].getValueAt(X),
                      _vertaxList[faceLocation[i][0]].getValueAt(Y) - _vertaxList[faceLocation[i][2]].getValueAt(Y),
                      _vertaxList[faceLocation[i][0]].getValueAt(Z) - _vertaxList[faceLocation[i][2]].getValueAt(Z));
        _normalList[i] = new Vector3D(vec1.getValueAt(Y) * vec2.getValueAt(Z) - vec1.getValueAt(Z) * vec2.getValueAt(Y),
                                      vec1.getValueAt(Z) * vec2.getValueAt(X) - vec1.getValueAt(X) * vec2.getValueAt(Z),
                                      vec1.getValueAt(X) * vec2.getValueAt(Y) - vec1.getValueAt(Y) * vec2.getValueAt(X));
        _normalList[i].normalize();
    }

}

void Bin::drawBin(AssimpSimpleModelLoader* loader) {
	glPushMatrix();
    
	glColor3d(1.0, 0.5, 0);
    glTranslated(0.0, -1, 2.3);	
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	loader->recursive_render(loader->getScene(),loader->getScene()->mRootNode->FindNode("Cestino"));
	glEnable(GL_COLOR_MATERIAL);
	glColor3d(1.0, 1.0, 1.0);
    
	glPopMatrix();
}

int Bin::getfaces() {
    return _faces;
}

Vector3D Bin::getNormalAt(int pos) {
    return _normalList[pos];
}

Vector3D Bin::getVertexAt(int pos) {
    return _vertaxList[pos];
}
