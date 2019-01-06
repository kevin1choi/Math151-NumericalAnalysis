/*#include <iostream>
#include <cmath>
#include <string>

using namespace std;

const double pi = 3.1415926535897;

/////////////////////// Question #3 /////////////////////////////////
double f(double t, double y) {
	return sin(y) / ((t + 2)*(t + 2));
}

double f1(double t, double y) {
	return -2 * sin(y) / pow(t + 2, 3) + cos(y)*sin(y) / pow(t + 2, 2);
}

double f2(double t, double y) {
	return 6 * sin(y) / pow(t + 2, 4) - 4 * cos(y) / pow(t + 2,
		3)*f(t, y) - sin(y) / pow(t + 2, 2)*pow(f(t, y), 2) - 2 *
		sin(y)*cos(y) / pow(t + 2, 5) + pow(cos(y) / pow(t + 2, 2), 2)*f(t,
			y);
}

double taylor(double t, double y, double h) {
	return pi / 2 + h*f(t, y) + h*h / 2 * f1(t, y) + h*h*h / 6 * f2(t, y);
}

void adamBashforth(double ab[], double h) {
	for (int i = 2; i < 11; i++) {
		ab[i] = ab[i - 1] + (3 * h / 2 * f((-1)*h,ab[i - 1])) - (h / 2 * f((i-2)*h,ab[i - 2]));
	}
}

void adamMoulton(double am[], double ab[], double h) {
	for (int i = 2; i < 11; i++) {
		am[i] = am[i - 1] + (5 * h / 12 * f(i*h,ab[i])) + (2*h / 3 * f((i-1)*h,am[i - 1])) - (h/12*f((i-2)*h,am[i-2]));
	}
}

/////////////////////////////////// Question #4 ////////////////////////////////////
double function4(double y) {
	return -15 * y;
}

double f41(double y) {
	return -15 * -15 * y;
}
double f42(double y) {
	return -15 * -15 * -15 * y;
}

double taylor4(double y, double h) {
	return 1 + h*function4(y) + h*h / 2 * f41(y) + h*h*h / 6 * f42(y);
}

void eulers(double a[], double h, int size) {
	for (int i = 1; i < size; i++) {
		a[i] = a[i - 1] + h*function4(a[i - 1]);
	}
}

//////////////////////////////// Question #5 ///////////////////////////////////////
struct w {
	double u1;
	double u2;
};

void adamBashforth(w a[]) {
	for (int i = 2; i < 25; i++) {
		a[i].u1 = a[i - 1].u1 + (3 * .01 / 2 * a[i - 1].u1) - (.01 / 2 * a[i - 2].u1);
		a[i].u2 = a[i - 1].u2 + (3 * .01 / 2 * a[i - 1].u2) - (.01 / 2 * a[i - 2].u2);
	}
}

double secantMethod(double alphas[], int i, w b[], w a[]) {
	return alphas[i] - (alphas[i] - alphas[i - 1]) / ((b[24].u1 - 15) - (a[24].u1 - 15)) * (b[24].u1 - 15);
}

void first2(w a[], double u2) {
	a[0].u1 = 1;
	a[0].u2 = u2;

	a[1].u1 = a[0].u1 + (.01 * a[0].u2) + (.01 * .01 / 2 * (sin(a[0].u1) + 2 * a[0].u1));
	a[1].u2 = a[0].u2 + (.01 * (sin(a[0].u1) + 2 * a[0].u1)) + (.01 * .01 / 2 * (cos(a[0].u1) * a[0].u2 + 2 * a[0].u2));
}

void print(w a[]) {
	for (int i = 0; i < 25; i++) {
		cout << a[i].u1 << endl;
	}
}

int main() {
	//////////////////////////// Question #3 ////////////////////////////////////
	double ab[11];
	ab[0] = pi / 2;
	ab[1] = taylor(0, pi / 2, 0.1);
	adamBashforth(ab, 0.1);

	double am[11];
	am[0] = pi / 2;
	am[1] = taylor(0, pi / 2, 0.1);
	adamMoulton(am, ab, 0.1);

	for (int i = 0; i < 11; i++) {
		cout << i*0.1 << "     " << ab[i] << "     " << am[i] << endl;
	}
	cout << endl;

	//////////////////////////////// Question #4 //////////////////////////////
	double a[21];
	a[0] = 1;
	eulers(a, .25, 21);
	for (int i = 0; i < 21; i++) {
		cout << i*.25 << "     " << a[i] << endl;
	}
	cout << endl;

	double b[37];
	b[0] = 1;
	eulers(b, 2 / 15, 37);
	for (int i = 0; i < 37; i++) {
		cout << i*2/15 << "     " << b[i] << endl;
	}
	cout << endl;

	double c[41];
	c[0] = 1;
	eulers(c, .125, 41);
	for (int i = 0; i < 41; i++) {
		cout << i*.125 << "     " << c[i] << endl;
	}
	cout << endl;

	double d[41];
	d[0] = 1;
	d[1] = taylor4(1, .125);
	adamBashforth(d, 0.125);
	for (int i = 0; i < 41; i++) {
		cout << i*.125 << "     " << c[i] << endl;
	}
	cout << endl;

	////////////////////////////////// Question #5 ////////////////////////////////////

	w alpha0[25];
	w alpha1[25];
	w alpha2[25];
	w alpha3[25];
	w alpha4[25];
	double alphas[5];

	alphas[0] = 1;
	first2(alpha0, alphas[0]);
	adamBashforth(alpha0);


	alphas[1] = -0.7;
	first2(alpha1, alphas[1]);
	adamBashforth(alpha1);


	alphas[2] = secantMethod(alphas, 1, alpha1, alpha0);
	first2(alpha2, alphas[2]);
	adamBashforth(alpha2);


	alphas[3] = secantMethod(alphas, 2, alpha2, alpha1);
	first2(alpha3, alphas[3]);
	adamBashforth(alpha3);


	alphas[4] = secantMethod(alphas, 3, alpha3, alpha2);
	first2(alpha4, alphas[4]);
	adamBashforth(alpha4);


	cout << "alpha0 = " << alphas[0] << endl;
	print(alpha0);
	cout << endl;

	cout << "alpha1 = " << alphas[1] << endl;
	print(alpha1);
	cout << endl;

	cout << "alpha2 = " << alphas[2] << endl;
	print(alpha2);
	cout << endl;

	cout << "alpha3 = " << alphas[3] << endl;
	print(alpha3);
	cout << endl;

	cout << "alpha4 = " << alphas[4] << endl;
	print(alpha4);
	cout << endl;

	string hold;
	cin >> hold;
	return 0;
}

*/