#pragma once
#include <iostream>
#include "Abalone.h"

class Linear_Regression
{
public:
	double ** multiply(double **matrix_A, double **matrix_B, int m, int n, int k);
	double ** multiply(double **matrix_A, int m, int n, double v);
	void show_matrix(double **matrix_A, int m, int n);
	void delete_matrix(double **matrix_A, int m);
	double determinant(double **matrix_A, int m);
	double ** transpose(double **matrix_A, int m, int n);
	double ** inverse(double **matrix_A, int m);
	double * find_coeff_for_linear_regress(std::vector<Abalone> &Abalones);
	double predict_rings(Abalone a, double * alpha);
	double calculate_precision_of_prediction(std::vector<Abalone> &test_Abalones, double *alpha, int precision);
};