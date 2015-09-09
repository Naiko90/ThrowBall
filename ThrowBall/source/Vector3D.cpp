#include "Vector3d.h"

Vector3D::Vector3D(void) {
    this->_x = 0.0;
    this->_y = 0.0;
    this->_z = 0.0;
}

Vector3D::Vector3D(Vector3D* newVector) {
    this->_x = newVector->getValueAt(0);
    this->_y = newVector->getValueAt(1);
    this->_z = newVector->getValueAt(2);
}

Vector3D::Vector3D(const Vector3D &newVector) {
    _x = newVector._x;
    _y = newVector._y;
    _z = newVector._z;
}

Vector3D::Vector3D(double newx, double newy, double newz) {
    this->_x = newx;
    this->_y = newy;
    this->_z = newz;
}

double Vector3D::getValueAt(int n) {
    if (n == 0) return this->_x;
    else if (n == 1) return this->_y;
    else if (n == 2) return this->_z;
	else return 0.0;
}

void Vector3D::setValues(Vector3D* newVector) {
    this->_x = newVector->getValueAt(0);
    this->_y = newVector->getValueAt(1);
    this->_z = newVector->getValueAt(2);
}

void Vector3D::setValueAt(int pos, double newValue) {
    if (pos == 0) this->_x = newValue;
    else if (pos == 1) this->_y = newValue;
    else if (pos == 2) this->_z = newValue;
}

void Vector3D::addValueAt(int pos, double newValue) {
    if (pos == 0) this->_x += newValue;
    else if (pos == 1) this->_y += newValue;
    else if (pos == 2) this->_z += newValue;
}

void Vector3D::add(Vector3D &v) {
	_x = v.getValueAt(0) + _x;
        _y = v.getValueAt(1) + _y;
        _z = v.getValueAt(2) + _z;
}

void Vector3D::add(Vector3D* v) {
	_x = v->getValueAt(0) + _x;
        _y = v->getValueAt(1) + _y;
        _z = v->getValueAt(2) + _z;
}

void Vector3D::subst(Vector3D &v) {
	_x = _x - v.getValueAt(0);
        _y = _y - v.getValueAt(1);
        _z = _z - v.getValueAt(2);
}

void Vector3D::subst(Vector3D* v) {
	_x = _x - v->getValueAt(0);
        _y = _y - v->getValueAt(1);
        _z = _z - v->getValueAt(2);
}

void Vector3D::changeDirection(int pos) {
    if (pos == 0) this->_x *= -1;
    else if (pos == 1) this->_y *= -1;
    else if (pos == 2) this->_z *= -1;
}

double Vector3D::distance(Vector3D& v) {
    this->subst(v);
    double dist = getLength();
    this->add(v);
    return dist;
}

double Vector3D::getLength() {
    double length = sqrt(pow(_x,2) + pow(_y,2) + pow(_z,2));
    return length;
}

void Vector3D::normalize() {
    double length = this->getLength();
    _x = _x / length;
    _y = _y / length;
    _z = _z / length;
}

double Vector3D::dot(Vector3D& v) {
    double dotProd = 0.0;
    dotProd += _x * v._x;
    dotProd += _z * v._z;
    dotProd += _y * v._y;
    return dotProd;
}