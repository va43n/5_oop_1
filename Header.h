#pragma once
// ������������� ������� ���� II (R-�������������)
// f(x, nu) = 1/(2B(nu+1,nu+1))*((1-x^2)/4)^nu
// -1<=x<=1, nu>=0, v=0 �����������, nu=0.5 ������������, nu=1 ��������������
// D=1/(2nu+3), y2=-6/(2nu+5)


//#define __STDCPP_MATH_SPEC_FUNCS__ 201003L
//#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1


#include <fstream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <time.h>


const double PI = acos(-1);


double test(int mode);
void enter(double* args, int size);

double get_f(double x, double mu, double la, double nu);
double* get_moments(double mu, double la, double nu);
double get_model(double mu, double la, double nu);

double get_mix_f(double x, double* args, double mix_param);
double* get_mix_moments(double* args, double mix_param);
double get_mix_model(double* args, double mix_param);

double randomize_X();
int get_k(int n);
int* get_empirical_counter(double* X, double delta, int n, int k, double min);
double* get_empirical_frequency(int* counter, int n, int k);
double* get_empirical_density(int* counter, int n, int k, double delta);
double get_empirical_f(double x, double* density, int k, double delta, double min);
double* get_empirical_moments(double* X, int n);
double get_empirical_model(double* frequency, double delta, int k, double min);