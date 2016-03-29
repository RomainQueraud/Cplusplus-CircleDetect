#pragma once
class Point3D
{
private:
	float x;
	float y;
	float z;
	/*
	Temps �coul� depuis le dernier point re�u
	*/
	float t;

public:
	Point3D(float px, float py, float pz, float pt);
	Point3D();
	~Point3D();

	float getX();
	float getY();
	float getZ();
	float getT();
};

