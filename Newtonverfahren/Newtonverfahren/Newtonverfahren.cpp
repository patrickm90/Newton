// Newtonverfahren.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"


struct Funktion
{
	//1D
	double operator()(double x);
	virtual double value(double x) = 0;
	virtual double x(double x) = 0;
	virtual double xx(double x) = 0;

	//2D
	double operator()(double x, double y);
	//virtual double value(double x, double y) = 0;
	//virtual double x(double x, double y) = 0;
	//virtual double y(double x, double y) = 0;
	//virtual double xx(double x, double y) = 0;
	// virtual double yy(double x, double y) = 0;
	// virtual double xy(double x, double y) = 0;
	// virtual double yx(double x, double y) = 0;
};


using namespace std;
//Thanks to:
//http://stackoverflow.com/a/10467633/2952814
const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

//Thanks to:
//http://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string

std::string ReplaceString(std::string subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}
//Thanks to
//http://stackoverflow.com/a/392988/2952814
double StringToDouble(char* str)
{
	char* endptr;
	double value = strtod(str, &endptr);
	if (*endptr) return 0;
	return value;
}
//Thanks to:
//http://stackoverflow.com/a/34109000/2952814
std::string GetExecutablePath()
{

	char buf[1024] = { 0 };
	char *p;
	p = buf;
	
	DWORD ret = GetModuleFileNameA(NULL, buf, sizeof(buf));
	if (ret == 0 || ret == sizeof(buf))
	{
		//return executable_path_fallback(argv0);
	}
	std::string path = buf;
	return ReplaceString(path, "Newtonverfahren.exe", "");

}

std::string GetConfigLine(int lineNumber)
{
	std::string configPath = GetExecutablePath().append("Config.config");
	
	std::ifstream input(configPath);
	int i = 0;
	for (std::string line; getline(input, line); )
	{
		if (i == lineNumber)
			return line;
		i++;
	}
	return "";

}
void saveLog(std::string logString)
{
	std::string path = GetConfigLine(1);
	path.append("LogFile.txt");
	std::ofstream fs(path);

	fs << logString;
	fs.close();
}

void plot(std::string function, std::string tangente, std::string ableitung, std::string fileName)
{
	std::string call = GetConfigLine(0);

	std::string options = function.append(";").append(tangente).append(";").append(ableitung)
		.append(";").append("\"set terminal png\"").append(";").append("\"set grid front\"").append(";").append("\"set output ").append("'").append(fileName).append("'").append("\";").append("\"set xrange [-5:5]\";").append("\"set yrange [-5:5]\";")
		.append("\"plot ").append("f(x),y(x),g(x)\"");

	call = call.append(" ").append(options);
	const char* run = call.c_str();
	//cout << run;
	system(run);
}

/*
// Verfahren fuer Mehrdimensionales Newtonverfahren. Bricht bei erreichen der Genauigkeit bzw. bei nicht moeglichen Ergebnissen ab. Startpunkt = x0, y0 analog zum Verfahren.
// Bei Erfolg: Plotten (implementieren!)
void newton_md(Funktion &g, double genauigkeit, double startPunktx, double startpunkty)){
int schritte = 0;

}
*/
// Verfahren fuer Eindimensionales Newtonverfahren. Bricht bei erreichen der Genauigkeit bzw. bei nicht moeglichen Ergebnissen ab. Startpunkt = x0 analog zum Verfahren.
// Bei Erfolg: Plotten (implementieren!)
void newton_1d(Funktion &g, double genauigkeit, double startPunkt, std::string function, std::string ableitung) {                  // PLOTTEN ?
	
	std::string logString = "";

	int schritte = 0;

	double vorigerPunkt = startPunkt;
	double aktuellerPunkt = startPunkt;
	double naechsterPunkt = startPunkt;
	
	std::string output = "Step: ";
	output.append(std::to_string(schritte++)).append(" ")
		.append("x=").append(std::to_string(naechsterPunkt)).append(" ")
		.append("y=").append(std::to_string(g.value(naechsterPunkt)));

	logString.append(output).append("\n");

	cout << output << endl << endl;

	for (; schritte < 100; schritte++) {
		std::string path = GetConfigLine(1);
		path = path.append(std::to_string(schritte)).append(".png");

		double k = g.xx(aktuellerPunkt);
		double d = g.x(aktuellerPunkt) - k*aktuellerPunkt;

		std::string tangente = "y(x)=";
		tangente = tangente.append(std::to_string(k)).append("*").append("x").append("+").append(std::to_string(d));

		plot(function, tangente, ableitung, path);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
		naechsterPunkt = aktuellerPunkt - (g.x(aktuellerPunkt) / g.xx(aktuellerPunkt));

		std::string output = "Step: ";
		output.append(std::to_string(schritte)).append(" ")
			.append("x=").append(std::to_string(naechsterPunkt)).append(" ")
			.append("y=").append(std::to_string(g.value(naechsterPunkt)));

		logString.append(output).append("\n");

		cout << output << endl << endl;
		

		if (vorigerPunkt == naechsterPunkt && aktuellerPunkt != vorigerPunkt) 
		{ 
			cout << "Startwert alterniert" << endl; break; 
			logString.append("Startwert alterniert").append("\n");
		}
		if ((abs(g.x(aktuellerPunkt)) > genauigkeit)) {
			vorigerPunkt = aktuellerPunkt;
			aktuellerPunkt = naechsterPunkt;
		}
		else { break; }
	}

	logString.append("\n\n\n");
	logString.append("---------------Log file generated for following parameters---------------").append("\n");
	logString.append("Function: ").append(ReplaceString(function, "**", "^")).append("\n");
	logString.append("Start Point: ").append(std::to_string(startPunkt)).append("\n");
	logString.append("Accuracy: ").append(std::to_string(genauigkeit)).append("\n");
	logString.append("Created at: ").append(currentDateTime()).append("\n");

	saveLog(logString);

	std::string endOutput = "";
	endOutput.append("Found optimal solution at: ").append("x=").append(std::to_string(aktuellerPunkt))
		.append(" ").append("where y=").append(std::to_string(g.value(aktuellerPunkt))).append("\n\n")
		.append("Graphs and Log can be found at: ").append(GetConfigLine(1)).append("\n\n")
		.append("Input anything to escape...");

	cout << endOutput << endl;

}

// Auswerten f. 1-dimensionale Funktion
double auswerten(Funktion &g, double x, int ableitung = 0) {
	if (ableitung == 0) {
		return g(x);
	}
	if (ableitung == 1) {
		return g.x(x);
	}
	if (ableitung == 2) {
		return g.xx(x);
	}
	throw;
}
/*
// Auswertung f. Mehrdimensionales Newtonverfahren          // IMPLEMENTIEREN
double auswerten(Funktion &g, double x, double y, ableitung = 0){
if(ableitung == 0){
return g(x,y);
}
if(ableitung == 1){
// Erste Ableitung einer Mehrdimensionalen Funktion??
}
if(ableitung == 2){
// Zweite Ableitung einer Mehrdimensionalen Funktion??
}
throw;
}
*/
// Klammern ueberladen, um Auswertung wie g(x) moeglich zu machen ... andernfalls: g.value(x) noetig!!
double Funktion::operator()(double x) {
	return this->value(x);
}
// Mehrdimensionales Klammernueberladen
//double Funktion:: operator()(double x, double y){
//    return this-> value(x,y);
//}

int main()
{

	int eingabe = 0;
	// Grundlegende Funktion:  3 Funktionen implementiert, 2 1-Dimensionale, 1 Mehrdimensionale
	cout << "Newtonverfahren, veranschaulicht anhand einiger vordefinierter Beispiele " << endl
		<< "Fuer eine detailliertere Erklaerung besuchen Sie bitte die Website: http://ops-newton.github.io/Page/" << endl << endl
		<< "Bitte waehlen Sie welche Funktion Sie gezeigt bekommen wollen:" << endl
		<< "Funktion 1 - Eindimensional, loesbar f. x0 = 0: x^5 + 5x^4 + 5x^3 - 5x^2 - 6x, Eingabe: 1" << endl
		<< "Funktion 2 - Eindimensional, unloesbar f. x0 = 0: (x^4)/4 - x^2 + 2x, Eingabe: 2" << endl
		<< "Funktion 3 - Mehrdimensional: ___________, Eingabe: 3" << endl << endl
		<< "> ";


	cin >> eingabe;
	// 1 Dimensionale Funktion, Startpunkt beliebig waehlbar. Gute Veranschaulichung des Newtonverfahrens f. 1-Dimensionale Funktionen
	if (eingabe == 1) {
		struct : Funktion {
			double value(double x) { return ((x*x*x*x*x) + (5 * x*x*x*x) + (5 * x*x*x) - (5 * x*x) - (6 * x)); } // g(x)
			double x(double x) { return ((5 * x*x*x*x) + (20 * x*x*x) + (15 * x*x) - (10 * x) - 6); } // g'(x)
			double xx(double x) { return ((20 * x*x*x) + (60 * x*x) + (30 * x) - 10); } // g''(x)
		}g;

		char genauigkeit [1024];
		char startwert[1024];

		//std::string genauigkeit = "";
		//std:string  = "";

		cout << "Bitte Startpunkt eingeben  > ";
		cin >> startwert;

		cout << "Bitte Genauigkeit angeben  > ";
		cin >> genauigkeit;

		newton_1d(g, StringToDouble(genauigkeit), StringToDouble(startwert), "f(x)=x**5+5*x**4+5*x**3-5*x**2-6*x", "g(x)=5*x**4+20*x**3+15*x**2-10*x-6");

	}
	else
		// 1 Dimensionale Funktion, Startpunkt = 0 --> Nicht loesbar. Gute Veranschaulichung des alternierens zwischen 0 und 1
		if (eingabe == 2) {
			struct : Funktion {
				double value(double x) { return ((x*x*x*x) / 4 - (x*x) + (2 * x)); } // f(x)
				double x(double x) { return ((x*x*x) - 2 * x + 2); } // f'(x)
				double xx(double x) { return ((3 * x*x) - 2); } // f''(x)
			}f;

			char genauigkeit[1024];
			char startwert[1024];
			
			cout << "Bitte Startwert eingeben  > ";
			cin >> startwert;

			cout << "Bitte Genauigkeit angeben (< 1), Trennung \".\"  > ";
			cin >> genauigkeit;

			newton_1d(f, StringToDouble(genauigkeit), StringToDouble(startwert), "f(x)=(x**4)/4-x**2+2*x", "g(x)=x**3-2*x+2");

		}
		else
			// Mehrdimensionale Funktion, Startpunkt beliebig waehlbar. Gute Veranschaulichung des Mehrdimensionalen Newtonverfahrens
			if (eingabe == 3) {
				/*struct : Funktion {
				double value(double x, double y) {return __;} // f(x,y)
				double x(double x, double y) {return  __;}                  // IMPLEMENTIEREN ?
				double y(double x, double y) {return __;}
				double xx(double x, double y) {return __;}
				double yy(double x, double y) {return __;}
				double xy(double x, double y) {return __;}
				double yx(double x, double y) {return __;}
				}h;
				double startwertx = 0;                  // STARTWERT X , Y ?
				double startwerty = 0;
				double genauigkeit = 1;

				cout << "Bitte Startwert x eingeben  > ";
				cin >> startwertx;
				cout << "Bitte Startwert y eingeben  > ";
				cin >> startwerty;
				cout << "Bitte Genauigkeit angeben (<1), Trennung \".\"  > ";
				cin >> genauigkeit;

				newton_md(h,genauigkeit, startwertx, startwerty);*/

			}
			else 
			{ 
				cout << "Fehlerhafte eingabe, Prozess terminiert..."; 
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				return 1; 
			}
			int warte = 0;
			cin >> warte;
			return 0;
}

