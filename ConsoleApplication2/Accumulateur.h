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
	Pourcentage de points dans le cercle pour être validé
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
	Test si deux points sont suffisement proches, relativement aux erreurs, par rapport à x, y et z	.
	C'est ici qu'on gère la précision.
	*/
	bool isClose(Point3D p1, Point3D p2);

	/*
	Va remplir les champs minX, maxX, minY, maxY, minZ, maxZ de telle sorte que tous les points capturés par le 
	cercle soient enfermés dans un cube.
	Grâce au fait qu'on enlève les premiers points du vecteur quand on detecte le cercle, on est 
	censé être bien réduit à la zone du cercle.
	*/
	void setCube();

	/*
	Retourne le point censé être le centre du cercle.
	Retourne null si il n'a pas trouvé de centre.
	Pour l'instant, on prend le centre du cube. 
	Ce qu'on pourrait faire sinon, c'est tester tous les points du cube pour tous les points du vector et calculer
	la différence de distance la plus faible. (Sûrement trop coûteux en temps)
	*/
	Point3D getCenter();

	/*
	p le point testé, o le centre de la sphere, r le rayon de la sphere
	Teste si le point p est entre les deux spheres de différence error
	*/
	bool isPointInsideSpheres(Point3D p, Point3D o, int r);

	/* 
	Appelé à chaque frame pour ajouter le point3d à l'accumulateur
	Doit effacer le point de départ dès que le vecteur est trop grand (équivaut à un mouvement trop long)	
	Retourne un booleen correspondant à la detection de cercle
	*/
	bool tick(Point3D p);

	/* 
	Dès que le vecteur est suffisemment long, on regarde dans la premiere moitié des points si un des
	points est sufisemment proche du dernier.
	Ce qui signifie que le début du cercle peut-être dans la premiere moitié des points capturés, et donc que
	les points d'avant ne servent potentiellement à rien.
	On enlève ensuite les points du départ qui ne servent plus à rien
	*/
	bool isCycleInPath();

	/* 
	Detecte si le vecteur contient des points qui forment un cercle.
	La méthode est :
		Si on a détecté qu'on avait créé un cycle, on cherche le point au centre du cycle.
		Puis on regarde si tous les points sont contenus entre une grande sphere et une petite sphere.
		Si c'est bon, on valide.
	Faire attention que le cercle soit assez grand pour éviter de detecter un non-mouvement.
	*/
	bool isCircle();

	/*
	Genère un cercle dans les axes x et y.
	Ce sont des données test
	*/
	std::vector<Point3D> generateCircle(float rayon, float cx, float cy);
};

