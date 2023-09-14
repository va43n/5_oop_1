#pragma once
// –аспределение ѕирсона типа II (R-распределение)
// f(x, nu) = 1/(2B(nu+1,nu+1))*((1-x^2)/4)^nu
// -1<=x<=1, nu>=0, v=0 равномерное, nu=0.5 полукруговое, nu=1 параболическое
// D=1/(2nu+3), y2=-6/(2nu+5)


#include <fstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>


const double PI = acos(-1);
const double EPS = pow(10, -2);


double check_variables(int mode);
void enter(double* args, int size);
std::string write_in_file(double num);

double get_f(double x, double mu, double la, double nu);
double* get_moments(double mu, double la, double nu);
double get_model(double mu, double la, double nu);
double check_x(double mu, double la);

double get_mix_f(double x, double* args, double mix_param);
double* get_mix_moments(double* args, double mix_param);
double get_mix_model(double* args, double mix_param);

double randomize_X();
int get_k(int n);
double get_min(double* X, int n);
double get_delta(double* X, int n, int k);
int* get_empirical_counter(double* X, double delta, int n, int k, double min);
double* get_empirical_frequency(int* counter, int n, int k);
double* get_empirical_density(int* counter, int n, int k, double delta);
double get_empirical_f(double x, double* density, int k, double delta, double min);
double* get_empirical_moments(double* X, int n);
double get_empirical_model(double* frequency, double delta, int k, double min);

void test();