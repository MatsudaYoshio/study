#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
using namespace std;

double ciede2000(const int L1, const int a1, const int b1, const int L2, const int a2, const int b2) {
	const double delta_Lp = L2 - L1;
	const double L_ = (L1 + L2) / 2;
	const double C1 = sqrt(a1*a1 + b1*b1);
	const double C2 = sqrt(a2*a2 + b2*b2);
	const double C_ = (C1 + C2) / 2;
	const double ap1 = a1 + 0.5*a1*(1 - sqrt(pow(C_, 7) / (pow(C_, 7) + 6103515625)));
	const double ap2 = a2 + 0.5*a2*(1 - sqrt(pow(C_, 7) / (pow(C_, 7) + 6103515625)));
	const double Cp1 = sqrt(ap1*ap1 + b1*b1);
	const double Cp2 = sqrt(ap2*ap2 + b2*b2);
	const double Cp_ = (Cp1 + Cp2) / 2;
	const double delta_Cp = Cp2 - Cp1;

	double hp1;
	if (b1 == 0 && ap1 == 0) {
		hp1 = 0;
	}
	else {
		hp1 = atan2(b1, ap1) * 180 / M_PI;
		if (hp1 < 0) hp1 += 360;
	}

	double hp2;
	if (b2 == 0 && ap2 == 0) {
		hp2 = 0;
	}
	else {
		hp2 = atan2(b2, ap2) * 180 / M_PI;
		if (hp2 < 0) hp2 += 360;
	}

	double delta_hp;
	if (C1 == 0 || C2 == 0) {
		delta_hp = 0;
	}
	else if (fabs(hp1 - hp2) <= 180) {
		delta_hp = hp2 - hp1;
	}
	else if (hp2 <= hp1) {
		delta_hp = hp2 - hp1 + 360;
	}
	else {
		delta_hp = hp2 - hp1 - 360;
	}

	const double delta_Hp = 2 * sqrt(Cp1*Cp2)*sin(delta_hp*M_PI / 180 / 2);

	double Hp_;
	if (fabs(hp1 - hp2) > 180) {
		Hp_ = (hp1 + hp2 + 360) / 2;
	}
	else {
		Hp_ = (hp1 + hp2) / 2;
	}

	const double T = 1 - 0.17*cos((Hp_ - 30)*M_PI / 180) + 0.24*cos(Hp_ * 2 * M_PI / 180) + 0.32*cos((3 * Hp_ + 6)*M_PI / 180) - 0.2*cos((4 * Hp_ - 63)*M_PI / 180);
	const double S_L = 1 + (0.015*pow(L_ - 50, 2)) / sqrt(20 + pow(L_ - 50, 2));
	const double S_C = 1 + 0.045*Cp_;
	const double S_H = 1 + 0.015*Cp_*T;
	const double R_T = -2 * sqrt(pow(Cp_, 7) / (pow(Cp_, 7) + 6103515625))*sin(60 * exp(-pow((Hp_ - 275) / 25, 2))*M_PI / 180);

	return sqrt(pow(delta_Lp / S_L, 2) + pow(delta_Cp / S_C, 2) + pow(delta_Hp / S_H, 2) + R_T*(delta_Cp / S_C)*(delta_Hp / S_H));
}

int main()
{
	cout << ciede2000(57, -8, -24, 57, 70, 67) << endl;
}