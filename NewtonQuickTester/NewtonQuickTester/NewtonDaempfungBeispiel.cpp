#include "stdafx.h"
#include <math.h>
#include <iostream>

double point = 0;
double lambda = 0.5;
int maxRuns = 500;

int main()
{
	//Calculator: f(x) = x^4/4-x²+2x
	//Lösung mit gedämpften Newtonverfahren

	//Info:
	//Wenn Lambda in starker Nähe von 1 ist, tritt ein endloser Zyklus ein vermeidet die Konvergenz


	char c;
	std::cout << "y for default values / n to input values" << std::endl;
	std::cin >> c;

	if (c == 'n')
	{
		std::cout << "enter startpoint (double): ";
		std::cin >> point;
		
		std::cout << std::endl << "enter lambda (double): ";
		std::cin >> lambda;

		std::cout << std::endl << "enter maxRuns int: ";
		std::cin >> maxRuns;

		std::cout << std::endl << std::endl;

	}
	for (int i = 0; i < maxRuns; i++)
	{
		if (point == point - lambda * ((pow(point, 3) - 2 * point + 2) / (3 * (pow(point, 2)) - 2)))
		{
			std::cout << "Done after: " << i+1 << " runs" << std::endl;
			break;
		}
		point = point - lambda * ((pow(point, 3) - 2 * point + 2) / (3 * (pow(point, 2)) - 2));
		std::cout << point << std::endl;
	}
	std::cin >> point;
    return 0;
}

