#include "Header.h"

double randomize_X() {
	double X;

	X = (rand() - 16384.) / 16384.;
	std::cout << X << std::endl;

	return X;
}

int get_k(int n) {
	return (int) (log(n) / log(2)) + 1;
}

int* get_empirical_counter(double* X, double delta, int n, int k, double min) {
	int* counter;
	bool flag;

	counter = new int[k];

	for (int i = 0; i < k; i++) {
		counter[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		flag = false;
		for (int j = 0; j < k; j++) {
			if (X[i] >= min + delta * j && X[i] < min + delta * (j + 1)) {
				counter[j]++;
				flag = true;
				break;
			}
		}
		if (!flag) {
			counter[k - 1]++;
		}
	}

	return counter;
}

double* get_empirical_frequency(int* counter, int n, int k) {
	double* frequency = new double[k];

	for (int i = 0; i < k; i++) {
		frequency[i] = counter[i] / (double)n;
	}

	return frequency;
}

double* get_empirical_density(int* counter, int n, int k, double delta) {
	double* density;

	density = new double[k];
	for (int i = 0; i < k; i++) {
		density[i] = counter[i] / (double)n / delta;
	}

	return density;
}

double get_empirical_f(double x, double* density, int k, double delta, double min) {
	for (int i = 0; i < k; i++) {
		if (x >= min + i * delta && x < min + (i + 1) * delta) {
			return density[i];
		}
	}
	return density[k - 1];
}

double* get_empirical_moments(double* X, int n) {
	double* moments;

	moments = new double[4];

	for (int i = 0; i < 4; i++) {
		moments[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		moments[0] += X[i];
	}
	moments[0] /= (double)n;

	for (int i = 0; i < n; i++) {
		moments[1] += pow(X[i] - moments[0], 2);
	}
	moments[1] /= (double)n;

	for (int i = 0; i < n; i++) {
		moments[2] += pow(X[i] - moments[0], 3);
	}
	moments[2] /= ((double)n * pow(moments[1], 3. / 2.));

	for (int i = 0; i < n; i++) {
		moments[3] += pow(X[i] - moments[0], 4);
	}
	moments[3] = moments[3] / ((double)n * pow(moments[1], 2)) - 3;

	return moments;
}

double get_empirical_model(double* frequency, double delta, int k, double min) {
	double r1, r2, sum = 0;

	do r1 = (double)rand() / RAND_MAX; while (r1 == 0. || r1 == 1.);

	for (int i = 0; i < k; i++) {
		sum += frequency[i];
		if (sum > r1) {
			//return frequency[i] / delta;
			if (i == k - 1) {
				r2 = (double)rand() / RAND_MAX;
			}
			else {
				do r2 = (double)rand() / RAND_MAX; while (r2 == 1.);
			}
			return  min + delta * i + r2 * delta;
		}
	}
	return 10;
}