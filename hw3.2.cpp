
#include <iostream>
#include <cmath>
#include <string>

	using namespace std;

struct w {
	double u1;
	double u2;
};

//////////////////////////////////// Question 2.a /////////////////////////////////////
double f1(double u1, double u2, double k) {
	return  k*(u1*u1 - 1)*u2 - u1;
}

void fRK1(double h, double u1, double u2, double k, w RK[]) {
	RK[0].u1 = h*u2;
	RK[0].u2 = h*f1(u1, u2, k);

	RK[1].u1 = h*(u2 + 0.5*RK[0].u2);
	RK[1].u2 = h*f1(u1 + 0.5*RK[0].u1, u2 + 0.5*RK[0].u2, k);

	RK[2].u1 = h*(u2 + 0.5*RK[1].u2);
	RK[2].u1 = h*f1(u1 + 0.5*RK[1].u1, u2 + 0.5*RK[1].u2, k);

	RK[3].u1 = h*(u2 + RK[2].u2);
	RK[3].u1 = h*f1(u1 + 0.5*RK[2].u1, u2 + RK[2].u2, k);
}

double f2(double u1, double u2, double k, double y1, double y2) {
	return (k * 2 * y1*y2 - 1)*u1 + k*(y1*y1 - 1)*u2;
}

void fRK2(double h, double u1, double u2, double k, w RK[], double y1, double y2) {
	RK[0].u1 = h*u2;
	RK[0].u2 = h*f1(u1, u2, k);

	RK[1].u1 = h*(u2 + 0.5*RK[0].u2);
	RK[1].u2 = h*f2(u1 + 0.5*RK[0].u1, u2 + 0.5*RK[0].u2, k, y1, y2);

	RK[2].u1 = h*(u2 + 0.5*RK[1].u2);
	RK[2].u1 = h*f2(u1 + 0.5*RK[1].u1, u2 + 0.5*RK[1].u2, k, y1, y2);

	RK[3].u1 = h*(u2 + RK[2].u2);
	RK[3].u1 = h*f2(u1 + 0.5*RK[2].u1, u2 + RK[2].u2, k, y1, y2);
}

void RK4(w RK[], w y[], int i) {
	y[i].u1 = y[i - 1].u1 + (1 / 6)*(RK[0].u1 + 2 * RK[1].u1 + 2 * RK[2].u1 + RK[3].u1);
	y[i].u2 = y[i - 1].u2 + (1 / 6)*(RK[0].u2 + 2 * RK[1].u2 + 2 * RK[2].u2 + RK[3].u2);
}

void print(double t[]) {
	cout << "#          " << "t" << endl;
	for (int i = 0; i < 50; i++) {
		cout << i + 1 << "          " << t[i] << endl;
	}
}

/////////////////////////////////// Question 2.b /////////////////////////////////////

int main() {
	///////////////////////////////// Question 2.a ///////////////////////////////////
	w y1[21];
	w y2[21];
	w RK[4];
	double t01[50] = { 0 };
	double t1[50] = { 0 };
	double t2[50] = { 0 };

	y1[0].u1 = 0;
	y1[0].u2 = (1 - 0) / (2 - 0);

	y2[0].u1 = 0;
	y2[0].u2 = 1;

	t01[0] = (1 - 0) / (2 - 0);
	t1[0] = (1 - 0) / (2 - 0);
	t2[0] = (1 - 0) / (2 - 0);

	double h = 0.1;
	double k = 0.1;
	int j = 1;
	do {
		for (int i = 1; i < 21; i++) {
			fRK1(h, y1[i - 1].u1, y1[i - 1].u2, k, RK);
			RK4(RK, y1, i);           // y1 update at i

			fRK2(h, y2[i - 1].u1, y2[i - 1].u2, k, RK, y1[i - 1].u1, y1[i - 1].u2);
			RK4(RK, y2, i);           // y2 update at i
		}
		t01[j] = t01[j - 1] - (y1[21].u1 - 1) / (y2[21].u1);

		y1[0].u1 = 0;
		y1[0].u2 = t01[j];

		y2[0].u1 = 0;
		y2[0].u2 = 1;

		j++;
	} while (abs(t01[j] - t01[j - 1]) < .001);
	print(t01);
	cout << endl;

	h = 0.1;
	k = 1;
	j = 1;

	y1[0].u1 = 0;
	y1[0].u2 = (1 - 0) / (2 - 0);

	y2[0].u1 = 0;
	y2[0].u2 = 1;
	do {
		for (int i = 1; i < 21; i++) {
			fRK1(h, y1[i - 1].u1, y1[i - 1].u2, k, RK);
			RK4(RK, y1, i);           // y1 update at i

			fRK2(h, y2[i - 1].u1, y2[i - 1].u2, k, RK, y1[i - 1].u1, y1[i - 1].u2);
			RK4(RK, y2, i);           // y2 update at i
		}
		t1[j] = t1[j - 1] - (y1[21].u1 - 1) / (y2[21].u1);

		y1[0].u1 = 0;
		y1[0].u2 = t1[j];

		y2[0].u1 = 0;
		y2[0].u2 = 1;

		j++;
	} while (abs(t1[j] - t1[j - 1]) < .001);
	print(t1);
	cout << endl;

	h = 0.1;
	k = 2;
	j = 1;

	y1[0].u1 = 0;
	y1[0].u2 = (1 - 0) / (2 - 0);

	y2[0].u1 = 0;
	y2[0].u2 = 1;
	do {
		for (int i = 1; i < 21; i++) {
			fRK1(h, y1[i - 1].u1, y1[i - 1].u2, k, RK);
			RK4(RK, y1, i);           // y1 update at i

			fRK2(h, y2[i - 1].u1, y2[i - 1].u2, k, RK, y1[i - 1].u1, y1[i - 1].u2);
			RK4(RK, y2, i);           // y2 update at i
		}
		t2[j] = t2[j - 1] - (y1[21].u1 - 1) / (y2[21].u1);

		y1[0].u1 = 0;
		y1[0].u2 = t2[j];

		y2[0].u1 = 0;
		y2[0].u2 = 1;

		j++;
	} while (abs(t2[j] - t2[j - 1]) < .001);
	print(t2);
	cout << endl;

	//////////////////////////////// Question 2.b /////////////////////////////////////

	string hold;
	cin >> hold;
	return 0;
}