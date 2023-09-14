#include "Header.h"

double get_mix_f(double x, double* args, double mix_param) {
	return (1. - mix_param) * get_f(x, args[0], args[1], args[2]) + mix_param * get_f(x, args[3], args[4], args[5]);
}

double* get_mix_moments(double* args, double mix_param) {
	double* mix_moments, *moments1, * moments2;

	mix_moments = new double[4];
	moments1 = new double[4];
	moments2 = new double[4];

	mix_moments = get_moments(args[0], args[1], args[2]);
	moments1[0] = mix_moments[0]; moments1[1] = mix_moments[1]; moments1[2] = mix_moments[2]; moments1[3] = mix_moments[3];

	mix_moments = get_moments(args[3], args[4], args[5]);
	moments2[0] = mix_moments[0]; moments2[1] = mix_moments[1]; moments2[2] = mix_moments[2]; moments2[3] = mix_moments[3];


	mix_moments[0] = (1. - mix_param) * moments1[0] + mix_param * moments2[0];

	mix_moments[1] = (1. - mix_param) * (pow(moments1[0], 2) + moments1[1]) + mix_param * (pow(moments2[0], 2) + moments2[1]) - pow(mix_moments[0], 2);

	mix_moments[2] = 1. / pow(mix_moments[1], 3. / 2.) * ((1 - mix_param) * (pow(moments1[0] - mix_moments[0], 3) + 3 * moments1[1] * (moments1[0] - mix_moments[0]) + pow(moments1[1], 3. / 2.) * moments1[2]) + (1 - mix_param) * (pow(moments2[0] - mix_moments[0], 3) + 3 * moments2[1] * (moments2[0] - mix_moments[0]) + pow(moments2[1], 3. / 2.) * moments2[2]));

	mix_moments[3] = 1. / pow(mix_moments[1], 2) * ((1 - mix_param) * (pow(moments1[0] - mix_moments[0], 4) + 6 * moments1[1] * pow(moments1[0] - mix_moments[0], 2) + 4 * (moments1[0] - mix_moments[0]) * pow(moments1[1], 3. / 2.) * moments1[2] + pow(moments1[1], 2) * moments1[3]) + mix_param * (pow(moments2[0] - mix_moments[0], 4) + 6 * moments2[1] * pow(moments2[0] - mix_moments[0], 2) + 4 * (moments2[0] - mix_moments[0]) * pow(moments2[1], 3. / 2.) * moments2[2] + pow(moments2[1], 2) * moments2[3])) - 3;

	return mix_moments;
}

double get_mix_model(double* args, double mix_param) {
	double r;

	do r = (double)rand() / RAND_MAX; while (r == 0. || r == 1.);

	if (r > mix_param) {
		return get_model(args[0], args[1], args[2]);
	}
	return get_model(args[3], args[4], args[5]);
}