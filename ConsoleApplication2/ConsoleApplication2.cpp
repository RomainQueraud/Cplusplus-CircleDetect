// ConsoleApplication2.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Accumulateur.h"
#include "Point3D.h"
#include <iostream>

/*
Test de la detection de cercle
*/
int main()
{
	//std::cout << "Bonjour" << std::endl;
	bool b;
	bool d;
	Accumulateur accCercle;
	Accumulateur accRandom;
	std::vector<Point3D> cercle = accCercle.generateCircle(1, 0, 0);
	std::vector<Point3D> random = accRandom.generateRandom();
	for (int i = 0; i < cercle.size(); i++) {
		b = accCercle.tick(cercle.at(i));
		std::cout << "cercle " << i << " : " << b << std::endl;
		d = accRandom.tick(random.at(i));
		std::cout << "random " << i << " : " << d << std::endl;
	}
	system("pause");
}

