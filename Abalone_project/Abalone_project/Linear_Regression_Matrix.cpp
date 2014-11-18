#include "Linear_Regression_Matrix.h"

Matrix <double> Linear_Regression_Matrix::find_coeff_for_linear_regress(std::vector<Abalone> &Abalones)
{
	int number_of_features = 8;
	std::vector<double *> arr;
	for (Abalone a : Abalones)
	{
		double *tmp = new double[number_of_features + 1];
		double s = 1;
		if (a.get_Sex() == 'I'){ s = 2; }
		else if (a.get_Sex() == 'F'){ s = 3; }
		tmp[0] = s; tmp[1] = a.get_Diameter(); tmp[2] = a.get_Height(); tmp[3] = a.get_Length(); tmp[4] = a.get_Shell_weight();
		tmp[5] = a.get_Shucked_weight(); tmp[6] = a.get_Viscera_weight(); tmp[7] = a.get_Whole_weight(); tmp[8] = a.get_Rings();
		arr.push_back(tmp);
	}
	Matrix<double> F(number_of_features, number_of_features), B(number_of_features, 1);
	for (int i = 0; i < number_of_features; i++)
	{
		B.set_at(i, 0, 0);
		for (int h = 0; h < arr.size(); h++)
		{
			B.set_at(i, 0, B.at(i, 0) + arr[h][number_of_features] * arr[h][i]);
		}
		for (int j = 0; j < number_of_features; j++)
		{
			F.set_at(i, j, 0);
			for (int h = 0; h < arr.size(); h++)
			{
				F.set_at(i, j, F.at(i, j) + arr[h][j] * arr[h][i]);
			}
		}
	}

	F = F.inverse();
	Matrix<double> alpha = F * B;

	for (int h = 0; h < arr.size(); h++)
	{
		delete arr[h];
	}
	arr.clear();

	return alpha;
}

double Linear_Regression_Matrix::predict_rings(Abalone a, Matrix <double> alpha)
{
	double s = 1;
	if (a.get_Sex() == 'I'){ s = 2; }
	else if (a.get_Sex() == 'F'){ s = 3; }
	return s * alpha.at(0, 0) +
		a.get_Diameter() * alpha.at(1, 0) +
		a.get_Height() * alpha.at(2, 0) +
		a.get_Length() * alpha.at(3, 0) +
		a.get_Shell_weight() * alpha.at(4, 0) +
		a.get_Shucked_weight() * alpha.at(5, 0) +
		a.get_Viscera_weight() * alpha.at(6, 0) +
		a.get_Whole_weight() * alpha.at(7, 0);
}

double Linear_Regression_Matrix::calculate_precision_of_prediction(std::vector<Abalone> &test_Abalones, Matrix <double> alpha, int precision)
{
	float almoust_right_answers = 0;
	for (Abalone a : test_Abalones)
	{
		int real_age = a.get_Rings(),
			predicted_age = predict_rings(a, alpha);
		if (predicted_age - ((int)(predicted_age)) > 0.5){ predicted_age = (int)predicted_age + 1; }
		else { predicted_age = (int)predicted_age; }
		if (abs(real_age - predicted_age) <= precision)
		{
			almoust_right_answers++;
		}
	}
	return (almoust_right_answers / test_Abalones.size());
}