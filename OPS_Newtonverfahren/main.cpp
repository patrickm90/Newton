#include <iostream>
#include <cmath>
#include <stdexcept>
#include "Funktion.h"

using namespace std;

/*
// Verfahren fuer Mehrdimensionales Newtonverfahren. Bricht bei erreichen der Genauigkeit bzw. bei nicht moeglichen Ergebnissen ab. Startpunkt = x0, y0 analog zum Verfahren.
// Bei Erfolg: Plotten (implementieren!)
void newton_md(Funktion &g, double genauigkeit, double startPunktx, double startpunkty)){
    int schritte = 0;

}
*/
// Verfahren fuer Eindimensionales Newtonverfahren. Bricht bei erreichen der Genauigkeit bzw. bei nicht moeglichen Ergebnissen ab. Startpunkt = x0 analog zum Verfahren.
// Bei Erfolg: Plotten (implementieren!)
void newton_1d(Funktion &g, double genauigkeit, double startPunkt){                  // PLOTTEN ?
    int schritte = 0;

    double vorigerPunkt = startPunkt;
    double aktuellerPunkt = startPunkt;
    double naechsterPunkt = startPunkt;

    cout << "x" << schritte++ << "  "<< naechsterPunkt << endl;

    for(;schritte < 100; schritte++){
        naechsterPunkt = aktuellerPunkt - (g.x(aktuellerPunkt)/g.xx(aktuellerPunkt));
        cout << "x" << schritte << "  " << naechsterPunkt << endl;
        if(vorigerPunkt == naechsterPunkt && aktuellerPunkt != vorigerPunkt){cout << "Startwert alterniert" << endl; break;}
        if((abs(g.x(aktuellerPunkt)) > genauigkeit)){
            vorigerPunkt = aktuellerPunkt;
            aktuellerPunkt = naechsterPunkt;
        } else {break;}
    }
}

// Auswerten f. 1-dimensionale Funktion
double auswerten(Funktion &g, double x, int ableitung = 0){
    if(ableitung == 0){
        return g(x);
    }
    if(ableitung == 1){
        return g.x(x);
    }
    if(ableitung == 2){
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
    if(eingabe == 1){
        struct : Funktion {
            double value(double x) {return ((x*x*x*x*x) + (5*x*x*x*x) + (5*x*x*x) - (5*x*x) - (6*x));} // g(x)
            double x(double x) {return ((5*x*x*x*x) + (20*x*x*x) + (15*x*x) + (10*x) + 6);} // g'(x)
            double xx(double x) {return ((20*x*x*x) + (60*x*x) + (30*x) + 10);} // g''(x)
        }g;

        double genauigkeit = 1;
        double startwert = 0;

        cout << "Bitte Startpunkt eingeben  > ";
        cin >> startwert;

        cout << "Bitte Genauigkeit angeben  > ";
        cin >> genauigkeit;

        newton_1d(g, genauigkeit,startwert);

    } else
    // 1 Dimensionale Funktion, Startpunkt = 0 --> Nicht loesbar. Gute Veranschaulichung des alternierens zwischen 0 und 1
    if(eingabe == 2){
        struct : Funktion {
            double value(double x) {return ((x*x*x*x)/4 - (x*x) + (2*x));} // f(x)
            double x(double x) {return ((x*x*x) - 2*x + 2);} // f'(x)
            double xx(double x) {return ((3*x*x) - 2);} // f''(x)
        }f;

        double startwert = 0;
        double genauigkeit = 1;

        cout << "Bitte Startwert eingeben  > ";
        cin >> startwert;

        cout << "Bitte Genauigkeit angeben (< 1), Trennung \".\"  > ";
        cin >> genauigkeit;

        newton_1d(f, genauigkeit,startwert);

    } else
    // Mehrdimensionale Funktion, Startpunkt beliebig waehlbar. Gute Veranschaulichung des Mehrdimensionalen Newtonverfahrens
    if(eingabe == 3){
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

    } else {cout << "Fehlerhafte eingabe, Prozess terminiert"; return 1;}
    int warte = 0;
    cin >> warte;
    return 0;
}
