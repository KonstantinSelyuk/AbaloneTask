#include "Linear_Regression.h"

double ** Linear_Regression::multiply(double **matrix_A, double **matrix_B, int m, int n, int k)
{
	double **matrix_C = new double*[m];
	for (int i = 0; i < m; i++)
	{
		matrix_C[i] = new double[k];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < k; j++)
		{
			matrix_C[i][j] = 0;
			for (int z = 0; z < n; z++)
			{
				matrix_C[i][j] += matrix_A[i][z] * matrix_B[z][j];
			}
		}
	}
	return matrix_C;
}

void Linear_Regression::show_matrix(double **matrix_A, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			//std::cout << matrix_A[i][j] << "  ";
			printf("%4.5f  ", matrix_A[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Linear_Regression::delete_matrix(double **matrix_A, int m)
{
	for (int i = 0; i < m; i++)
	{
		delete[] matrix_A[i];
	}
	delete[] matrix_A;
}

double Linear_Regression::determinant(double **matrix_A, int m)
{
	double det = 0;
	if (m == 1)
	{
		return matrix_A[0][0];
	}
	double ***vector_matrix = new double**[m];
	for (int i = 0; i < m; i++)
	{
		vector_matrix[i] = new double*[m - 1];
		for (int j = 0; j < m - 1; j++)
		{
			vector_matrix[i][j] = new double[m - 1];
			for (int z = 0; z < m - 1; z++)
			{
				if (z < i)
				{
					vector_matrix[i][j][z] = matrix_A[j + 1][z];
				}
				else
				{
					vector_matrix[i][j][z] = matrix_A[j + 1][z + 1];
				}
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		det += pow(-1, i) * matrix_A[0][i] * determinant(vector_matrix[i], m - 1);
	}

	for (int i = 0; i < m; i++)
	{
		delete_matrix(vector_matrix[i], m - 1);
	}
	delete[] vector_matrix;

	return det;
}

double ** Linear_Regression::transpose(double **matrix_A, int m, int n)
{
	double **matrix_B = new double*[n];
	for (int i = 0; i < n; i++)
	{
		matrix_B[i] = new double[m];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			matrix_B[i][j] = matrix_A[j][i];
		}
	}
	return matrix_B;
}

double ** Linear_Regression::multiply(double **matrix_A, int m, int n, double v)
{
	double **matrix_B = new double*[m];
	for (int i = 0; i < m; i++)
	{
		matrix_B[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			matrix_B[i][j] = matrix_A[i][j] * v;
		}
	}
	return matrix_B;
}

double ** Linear_Regression::inverse(double **matrix_A, int m)
{
	double ****matrix_matrix = new double***[m];
	for (int i = 0; i < m; i++)
	{
		matrix_matrix[i] = new double**[m];
		for (int j = 0; j < m; j++)
		{
			matrix_matrix[i][j] = new double*[m - 1];
			for (int z = 0; z < m - 1; z++)
			{
				matrix_matrix[i][j][z] = new double[m - 1];
				for (int k = 0; k < m - 1; k++)
				{
					if (k < i)
					{
						if (z < j)
						{
							matrix_matrix[i][j][z][k] = matrix_A[z][k];
						}
						else
						{
							matrix_matrix[i][j][z][k] = matrix_A[z + 1][k];
						}
					}
					else
					{
						if (z < j)
						{
							matrix_matrix[i][j][z][k] = matrix_A[z][k + 1];
						}
						else
						{
							matrix_matrix[i][j][z][k] = matrix_A[z + 1][k + 1];
						}
					}
				}
			}
		}
	}
	double **det_matrix = new double*[m];
	for (int i = 0; i < m; i++)
	{
		det_matrix[i] = new double[m];
		for (int j = 0; j < m; j++)
		{
			double r = determinant(matrix_matrix[j][i], m - 1);
			det_matrix[i][j] = pow(-1, (i + j)) * r;
		}
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			delete_matrix(matrix_matrix[i][j], m - 1);
		}
		delete[] matrix_matrix[i];
	}
	delete[] matrix_matrix;

	return multiply(transpose(det_matrix, m, m), m, m, (1 / determinant(matrix_A, m)));
}

double * Linear_Regression::find_coeff_for_linear_regress(std::vector<Abalone> &Abalones)
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
	double ** F = new double*[number_of_features];
	double ** B = new double*[number_of_features];
	for (int i = 0; i < number_of_features; i++)
	{
		F[i] = new double[number_of_features];
		B[i] = new double[1];
		B[i][0] = 0;
		for (int h = 0; h < arr.size(); h++)
		{
			B[i][0] += arr[h][number_of_features] * arr[h][i];
		}
		for (int j = 0; j < number_of_features; j++)
		{
			F[i][j] = 0;
			for (int h = 0; h < arr.size(); h++)
			{
				F[i][j] += arr[h][j] * arr[h][i];
			}
		}
	}

	double ** F_inverse = inverse(F, number_of_features);
	double ** alpha = multiply(F_inverse, B, number_of_features, number_of_features, 1);
	double * res = new double[number_of_features];
	for (int i = 0; i < number_of_features; i++)
	{
		res[i] = alpha[i][0];
	}

	for (int h = 0; h < arr.size(); h++)
	{
		delete arr[h];
	}
	arr.clear();
	delete_matrix(F, number_of_features);
	delete_matrix(B, number_of_features);
	delete_matrix(alpha, number_of_features);

	return res;
}

double Linear_Regression::predict_rings(Abalone a, double * alpha)
{

	double s = 1;
	if (a.get_Sex() == 'I'){ s = 2; }
	else if (a.get_Sex() == 'F'){ s = 3; }
	return s * alpha[0] +
		a.get_Diameter() * alpha[1] +
		a.get_Height() * alpha[2] +
		a.get_Length() * alpha[3] +
		a.get_Shell_weight() * alpha[4] +
		a.get_Shucked_weight() * alpha[5] +
		a.get_Viscera_weight() * alpha[6] +
		a.get_Whole_weight() * alpha[7];
}

double Linear_Regression::calculate_precision_of_prediction(std::vector<Abalone> &test_Abalones, double *alpha, int precision)
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