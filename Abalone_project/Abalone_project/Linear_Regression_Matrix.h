#pragma once

#include "Matrix.h"
#include "Abalone.h"
#include <vector>

class Linear_Regression_Matrix
{
public:
	Matrix <double> find_coeff_for_linear_regress(std::vector<Abalone> &Abalones);
	double predict_rings(Abalone a, Matrix <double> alpha);
	double calculate_precision_of_prediction(std::vector<Abalone> &test_Abalones, Matrix <double> alpha, int precision);
};