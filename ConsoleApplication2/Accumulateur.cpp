#include "stdafx.h"
#include "Accumulateur.h"
#include <iostream>


Accumulateur::Accumulateur()
{
}


Accumulateur::~Accumulateur()
{
}

std::vector<Point3D>& Accumulateur::getVector()
{
	return vector;
}

int Accumulateur::getMaxSize()
{
	return maxSize;
}

bool Accumulateur::isClose(Point3D p1, Point3D p2)
{
	bool okX = false;
	bool okY = false;
	bool okZ = false;
	bool okRet = false;

	if ((p1.getX() > p2.getX() - error) && (p1.getX() < p2.getX() + error)) {
		okX = true;
	}
	if ((p1.getY() > p2.getY() - error) && (p1.getY() < p2.getY() + error)) {
		okY = true;
	}
	if ((p1.getZ() > p2.getZ() - error) && (p1.getZ() < p2.getZ() + error)) {
		okZ = true;
	}
	okRet = okX && okY && okZ;
	return okRet;
}

void Accumulateur::setCube()
{
	Point3D p;
	for (int i = 0; i < getVector().size(); i++) {
		p = getVector().at(i);
		if (p.getX() < minX) {
			minX = p.getX();
		}
		if (p.getX() > maxX) {
			maxX = p.getX();
		}
		if (p.getY() < minY) {
			minY = p.getY();
		}
		if (p.getY() > maxY) {
			maxY = p.getY();
		}
		if (p.getZ() < minZ) {
			minZ = p.getZ();
		}
		if (p.getZ() > maxZ) {
			maxZ = p.getZ();
		}
	}
}

Point3D Accumulateur::getCenter()
{
	Point3D p;
	float x = (minX + maxX) / 2;
	float y = (minY + maxY) / 2;
	float z = (minZ + maxZ) / 2;
	p = Point3D(x, y, z, 0);

	return p;
}

bool Accumulateur::isPointInsideSpheres(Point3D p, Point3D o, int r)
{
	bool ret = false;
	float calc = pow(p.getX() - o.getX(), 2) + pow(p.getY() - o.getY(), 2) + pow(p.getZ() - o.getZ(), 2);
	float diff = calc - pow(r, 2);
	if (diff < 0) {
		diff *= -1;
	}
	if (diff <= error * 2) {
		ret = true;
	}
	return ret;
}

bool Accumulateur::tick(Point3D p)
{
	bool ret = false;
	vector.push_back(p);
	if (isCycleInPath()) {
		std::cout << "Cycle" << std::endl;
		setCube();
		ret = isCircle();
	}
	return ret;
}


bool Accumulateur::isCycleInPath()
{
	bool ret = false;
	Point3D last;
	Point3D actual;

	if (getVector().size() >= getMaxSize()) {
		last = getVector().at(getVector().size()-1);
		for (int i = 0; i < getMaxSize()/2; i++) {
			actual = getVector().at(i);
			if (isClose(last, actual)) {
				std::cout << "CycleTrue : " << i << std::endl;
				ret = true;
				std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Point3D>>> begin = getVector().begin();
				getVector().erase(begin, begin + i); //Enlève les points inutiles
			}
		}
	}

	return ret;
}

bool Accumulateur::isCircle()
{
	bool ret = false;
	int nbDedans = 0; //Nombre de points dans la sphere
	Point3D o = getCenter(); //Centre
	Point3D p = getVector().at(0);
	Point3D p1;
	float r = sqrt(pow(o.getX() - p.getX(), 2) + pow(o.getY() - p.getY(), 2) + pow(o.getZ() - p.getZ(), 2)); //Rayon
	for (int i = 0; i < getVector().size(); i++) {
		p1 = getVector().at(i);
		if (isPointInsideSpheres(p1, o, r)) {
			nbDedans++;
		}
	}
	if (100.0 * nbDedans / getVector().size() > percent) {
		ret = true;
	}
	return ret;
}

std::vector<Point3D> Accumulateur::generateCircle(float rayon, float cx, float cy)
{
	std::vector<Point3D> ret;
	float theta;
	for (theta = 0; theta < 2*3.14159265359; theta = theta + (2* 3.14159265359/100)) { //On génère 100 points 
		float x = 1 * cos(theta);
		float y = 1 * sin(theta);
		float z = 0;
		ret.push_back(Point3D(x, y, z, 10)); //10 millisecondes
	}
	return ret;
}

std::vector<Point3D> Accumulateur::generateRandom()
{
	std::vector<Point3D> ret;
	for (int i = 0; i < 100; i++) {
		float x = (rand() % 100) / 100.0;
		float y = (rand() % 100) / 100.0;
		float z = (rand() % 100) / 100.0;
		ret.push_back(Point3D(x, y, z, 10));
	}
	return ret;
}
