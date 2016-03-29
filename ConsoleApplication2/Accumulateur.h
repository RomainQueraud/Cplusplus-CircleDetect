#pragma once
#include <vector>
#include <limits>
#include "Point3D.h"

class Accumulateur
{

private:
	std::vector<Point3D> vector;
	/*
	Number of points inside vector.
	*/
	int maxSize = 100; 
	/*
	Erreur retenue pour le calcul du cycle
	*/
	float error = 0.10;
	/*
	Pourcentage de points dans le cercle pour �tre valid�
	*/
	float percent = 80;

	/*
	Dans le but d'encadrer la zone des points
	*/
	float minX = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float minY = std::numeric_limits<float>::max();
	float maxY = std::numeric_limits<float>::min();
	float minZ = std::numeric_limits<float>::max();
	float maxZ = std::numeric_limits<float>::min();

public:
	Accumulateur();
	~Accumulateur();

	std::vector<Point3D> getVector();
	int getMaxSize();

	/*
	Test si deux points sont suffisement proches, relativement aux erreurs, par rapport � x, y et z	.
	C'est ici qu'on g�re la pr�cision.
	*/
	bool isClose(Point3D p1, Point3D p2);

	/*
	Va remplir les champs minX, maxX, minY, maxY, minZ, maxZ de telle sorte que tous les points captur�s par le 
	cercle soient enferm�s dans un cube.
	Gr�ce au fait qu'on enl�ve les premiers points du vecteur quand on detecte le cercle, on est 
	cens� �tre bien r�duit � la zone du cercle.
	*/
	void setCube();

	/*
	Retourne le point cens� �tre le centre du cercle.
	Retourne null si il n'a pas trouv� de centre.
	Pour l'instant, on prend le centre du cube. 
	Ce qu'on pourrait faire sinon, c'est tester tous les points du cube pour tous les points du vector et calculer
	la diff�rence de distance la plus faible. (S�rement trop co�teux en temps)
	*/
	Point3D getCenter();

	/*
	p le point test�, o le centre de la sphere, r le rayon de la sphere
	Teste si le point p est entre les deux spheres de diff�rence error
	*/
	bool isPointInsideSpheres(Point3D p, Point3D o, int r);

	/* 
	Appel� � chaque frame pour ajouter le point3d � l'accumulateur
	Doit effacer le point de d�part d�s que le vecteur est trop grand (�quivaut � un mouvement trop long)	
	Retourne un booleen correspondant � la detection de cercle
	*/
	bool tick(Point3D p);

	/* 
	D�s que le vecteur est suffisemment long, on regarde dans la premiere moiti� des points si un des
	points est sufisemment proche du dernier.
	Ce qui signifie que le d�but du cercle peut-�tre dans la premiere moiti� des points captur�s, et donc que
	les points d'avant ne servent potentiellement � rien.
	On enl�ve ensuite les points du d�part qui ne servent plus � rien
	*/
	bool isCycleInPath();

	/* 
	Detecte si le vecteur contient des points qui forment un cercle.
	La m�thode est :
		Si on a d�tect� qu'on avait cr�� un cycle, on cherche le point au centre du cycle.
		Puis on regarde si tous les points sont contenus entre une grande sphere et une petite sphere.
		Si c'est bon, on valide.
	Faire attention que le cercle soit assez grand pour �viter de detecter un non-mouvement.
	*/
	bool isCircle();

	/*
	Gen�re un cercle dans les axes x et y.
	Ce sont des donn�es test
	*/
	std::vector<Point3D> generateCircle(float rayon, float cx, float cy);
};

