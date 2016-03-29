// ConsoleApplication2.cpp�: d�finit le point d'entr�e pour l'application console.
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
	Accumulateur acc;
	std::vector<Point3D> cercle = acc.generateCircle(1, 0, 0);
	for (int i = 0; i < cercle.size(); i++) {
		//std::cout << "i : " << i << std::endl;
		b = acc.tick(cercle.at(i));
		std::cout << i << " : " << b << std::endl;
	}
	system("pause");
}

