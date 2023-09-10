#include "Header.h"

void test() {
	double temp, *moments;
	bool pass;

	//_________________________default_____________________________
	double 
		nu[10]{0., 0.5, 1., 2., 3., 4., 5., 6., 7., 8.}, 
		f0[10]{ 0.5, 0.637, 0.75, 0.938, 1.094, 1.23, 1.354, 1.466, 1.571, 1.669 },
		D[10]{ 1. / 3., 0.25, 0.2, 0.143, 0.111, 0.091, 0.077, 0.067, 0.059, 0.053 },
		y2[10]{ -1.2, -1., -0.86, -0.67, -0.55, -0.46, -0.4, -0.35, -0.32, -0.29 };;

	pass = true;
	//default 1
	for (int i = 0; i < 10; i++) {
		temp = get_f(0, 0, 1, nu[i]);
		moments = get_moments(0, 1, nu[i]);
		if (abs(temp - f0[i]) < EPS && abs(moments[1] - D[i]) < EPS && abs(moments[3] - y2[i]) < EPS) {
			std::cout << ":D Test default 1." << i + 1 << " passed" << std::endl;
		}
		else {
			std::cout << ":C Test default 1." << i + 1 << " failed" << std::endl;
			std::cout << "    |expected: f0 = " << f0[i] << ", D = " << D[i] << ", y2 = " << y2[i] << std::endl;
			std::cout << "    |got: f0 = " << temp << ", D = " << moments[1] << ", y2 = " << moments[3] << std::endl;
			pass = false;
		}
	}
	if (pass) {
		std::cout << "------ :D Test default 1 passed ------" << std::endl << std::endl;
	}
	else {
		std::cout << "------ :C Test default 1 failed ------" << std::endl << std::endl;
		pass = true;
	}

	//default 2
	for (int i = 0; i < 10; i++) {
		temp = get_f(0, -3.5, 2, nu[i]);
		moments = get_moments(-3.5, 2, nu[i]);
		if (abs(moments[1] - D[i] * 4) < EPS && abs(moments[3] - y2[i]) < EPS) {
			std::cout << ":D Test default 2." << i + 1 << " passed" << std::endl;
		}
		else {
			std::cout << ":C Test default 2." << i + 1 << " failed" << std::endl;
			std::cout << "    |expected: f0 = " << f0[i] << ", D = " << D[i] << ", y2 = " << y2[i] << std::endl;
			std::cout << "    |got: f0 = " << temp << ", D = " << moments[1] << ", y2 = " << moments[3] << std::endl;
			pass = false;
		}
	}
	if (pass) {
		std::cout << "------ :D Test default 2 passed ------" << std::endl << std::endl;
	}
	else {
		std::cout << "------ :C Test default 2 failed ------" << std::endl << std::endl;
		pass = true;
	}
	//_________________________default_____________________________

	//___________________________mix_______________________________
	double args[6]{7.1, 2, 0, 7.1, 2, 0};
	double param = 0.75;
	double mix_D, mix_y2;

	for (int i = 0; i < 10; i++) {
		break;
		args[2] = nu[i];
		args[5] = nu[i];
		temp = get_mix_f(0, args, param);
		moments = get_mix_moments(args, param);

		if (abs(moments[1] - mix_D * 4) < EPS && abs(moments[3] - mix_y2) < EPS) {
			std::cout << ":D Test mix 1." << i + 1 << " passed" << std::endl;
		}
		else {
			std::cout << ":C Test mix 2." << i + 1 << " failed" << std::endl;
			std::cout << "    |expected: f0 = " << f0[i] << ", D = " << D[i] << ", y2 = " << y2[i] << std::endl;
			std::cout << "    |got: f0 = " << temp << ", D = " << moments[1] << ", y2 = " << moments[3] << std::endl;
			pass = false;
		}
	}
	if (pass) {
		std::cout << "------ :D Test mix 1 passed ------" << std::endl << std::endl;
	}
	else {
		std::cout << "------ :C Test mix 1 failed ------" << std::endl << std::endl;
		pass = true;
	}
	//___________________________mix_______________________________

	//________________________empirical____________________________
	double
		mu[10]{ 0., 5., -3., 9., 3.1, -9.4, 0.5, -0.23, 12.5, -10. },
		la[10]{ 1., 2., 8., 1.7, 1.3, 5.1, 10.3, 5.9, 0.1, 9.9 },
		x[10];
	double* X;
	double min, delta, * density;
	int z = 2, k, * counter;

	X = new double[100 * z * pow(2, 9)];

	//empirical 1-2-3 d
	for (int i = 1; i < 10; i++) {
		for (int j = 0; j < 100 * z; j++) {
			X[j] = get_model(mu[i], la[i], nu[i]);
		}
		for (int j = 0; j < 10; j++) {
			x[j] = X[j];
		}

		min = get_min(X, 100 * z);
		k = get_k(100 * z);
		delta = get_delta(X, 100 * z, k);
		counter = get_empirical_counter(X, delta, 100 * z, k, min);
		density = get_empirical_density(counter, 100 * z, k, delta);

		for (int q = 0; q < 10; q++) {
			moments = get_empirical_moments(X, 100 * z);
			if (abs(moments[1] - D[i]) < EPS && abs(moments[3] - y2[i]) < EPS && abs(get_empirical_f(x[q], density, k, delta, min) - get_f(x[q], mu[i], la[i], nu[i]) < EPS)) {
				std::cout << ":D Test empirical 2." << i + 1 << "." << q + 1 << " passed" << std::endl;
			}
			else {
				temp = get_f(x[q], mu[i], la[i], nu[i]);
				std::cout << ":C Test empirical 2." << i + 1 << "." << q + 1 << " failed" << std::endl;
				std::cout << "    |expected: f = " << temp << std::endl;
				std::cout << "    |got: f = " << get_empirical_f(x[q], density, k, delta, min) << std::endl;
				pass = false;
			}
		}
		if (pass) {
			std::cout << "------ :D Test empirical 2." << i + 1 << " (n = " << z * 100 <<") passed ------" << std::endl << std::endl;
		}
		else {
			std::cout << "    |expected: D = " << D[i] << ", y2 = " << y2[i] << std::endl;
			std::cout << "    |got: D = " << moments[1] << ", y2 = " << moments[3] << std::endl;
			std::cout << "------ :C Test empirical 2." << i + 1 << "(n = "<< z * 100 <<") failed------" << std::endl << std::endl;
			pass = true;
		}

		/*std::cout << std::endl << std::endl;
		for (int j = 0; j < 100 * z; j++) {
			std::cout << X[j] << std::endl;
		}
		std::cout << std::endl << std::endl;*/

		z *= 2;
	}
	//________________________empirical____________________________
}