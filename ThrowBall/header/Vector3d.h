#pragma once

#include <cmath>

using namespace std;

class Vector3D
{
private:
	double _x,_y,_z;
public:
	Vector3D(void);
	Vector3D(Vector3D* newVector);
    Vector3D(const Vector3D & newVector);
	Vector3D(double newx, double newy, double newz);
	double getValueAt(int n);
	void setValues(Vector3D* newVector);
	void setValueAt(int pos, double newValue);
	void addValueAt(int pos, double newValue);
    void add(Vector3D &v);
    void add(Vector3D* v);
    void subst(Vector3D &v);
    void subst(Vector3D* v);
    double distance (Vector3D &v);
    void changeDirection(int pos);
    double getLength();
    void normalize();
    double dot(Vector3D &v);
};
