#include "stdafx.h"
#include "Point3D.h"


Point3D::Point3D(float px, float py, float pz, float pt)
{
	x = px;
	y = py;
	z = pz;
	t = pt;
}

Point3D::Point3D()
{
}


Point3D::~Point3D()
{
}

float Point3D::getX()
{
	return x;
}

float Point3D::getY()
{
	return y;
}

float Point3D::getZ()
{
	return z;
}

float Point3D::getT()
{
	return t;
}

