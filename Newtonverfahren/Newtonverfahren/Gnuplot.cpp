#include "stdafx.h"

#ifndef Gnuplot
#define Gnuplot

class Gnuplot
{
public:
	static void plot(std::string function, std::string tangente, std::string fileName)
	{
		std::string call = "gnu/gnuplot.exe -p -e";
	
		std::string options = function.append(";").append(tangente)
			.append(";").append("set terminal png").append(";").append("set output \"").append(fileName).append("\";")
			.append("plot ").append("f(x),y(x)");

		call = call.append(" ").append(options);
		const char* run = call.c_str();

		system(run);
	}
};

#endif