#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#define longitud 11
class Regresion {

private:
	double* x;
	double* y;
	double covXY;
	double promX;
	double promY;
	double desvX;
	double desvY;
	double sx;
	double sy;
	double sxy;
	double sx2;
	double sy2;
	double m;
	double i;
	double b;
	double r;
	double* xy;
	double* x2;
	double* y2;


public:
	Regresion() {
		x = new double[longitud];
		y = new double[longitud];
		xy = new double[longitud];
		x2 = new double[longitud];
		y2 = new double[longitud];


		double tx[] = { 14,7,13,12,16,14,18,13,12,16,13 };
		double ty[] = { 16,12,13,14,15,12,16,11,13,18,17 };
		x = tx;
		y = ty;

		sx = 0; sy = 0; sxy = 0; sx2 = 0; sy2 = 0;
		calcularMatrix();
	}
	void leerArchivo() {
		ifstream arch("datos.csv");
		string registro, cadena;
		short c = 0;
		x = new double[longitud];
		y = new double[longitud];
		while (getline(arch, registro)) {
			stringstream ss(registro);
			getline(ss, cadena, ',');
			x[c] = atof(cadena.c_str());
			cout << cadena << '\n';
			getline(ss, cadena, ',');
			y[c] = atof(cadena.c_str());
			cout << cadena << '\n';
			c++;

		}
	}

	void calcularMatrix() {
		for (int i = 0; i<longitud; ++i) {
			xy[i] = x[i] * y[i];
			x2[i] = pow(x[i], 2);
			y2[i] = pow(y[i], 2);
		}
		for (int i = 0; i < longitud; ++i) {

			sx = sx + x[i];
			sy = sy + y[i];
			sxy = sxy + xy[i];
			sx2 = sx2 + x2[i];
			sy2 = sy2 + y2[i];
		}
	}

	void calcularPromedio() {

		promX = sx / longitud;
		promY = sy / longitud;
	}
	void calcularCovarianza() {
		covXY = (sxy / longitud) - (promX*promY);
	}
	void calcularDesviaciones() {
		desvX = sqrt((sx2 / longitud) - pow(promX, 2));
		desvY = sqrt((sy2 / longitud) - pow(promY, 2));
	}
	void calcularR() {
		r = covXY / (desvX*desvY);
	}


	void calcularPendiente() {
		m = (longitud*sxy - sx * sy) / (longitud*sx2 - sx * sx);

	}

	void calcularIntercepcion() {
		i = promY - m * promX;

	}
	//*Diferente formula ,pero representa al mismo valor que al punto corte*//

	void calcularPuntoCorte() {
		b = (sy*sx2 - sx * sxy) / (longitud*sx2 - sx * sx);

		//*Diferente formula ,pero representa al mismo valor que a la intercepcion*//

	}

	void visualizar() {
		cout << "\tRegresion Lineal " << endl;
		cout << "El promedio de X es: " << promX << endl;
		cout << "El promedio de Y es: " << promY << endl;
		cout << "La covarianza es: " << covXY << endl;
		cout << "La desviacion de X: " << desvX << endl;
		cout << "La desviacion de Y: " << desvY << endl;
		cout << "El coeficiente de correalcion es: " << r << endl;
		cout << "\tMetodo de minimos cuadrados :y=mx+b " << endl;
		cout << "La pendiente es: " << m << endl;
		cout << "La intercepcion de y es: " << i << endl;
		cout << "El punto de corte es : " << b << endl;
		cout << "La ecuacion de la recta es y= : " << m << " x  + " << i << endl;

	}

};

int main() {
	Regresion r;
	r.calcularPromedio();
	r.calcularCovarianza();
	r.calcularDesviaciones();
	r.calcularR();
	r.calcularPendiente();
	r.calcularIntercepcion();
	r.calcularPuntoCorte();
	r.visualizar();
	cin.get();
}
