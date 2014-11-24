#pragma once
#include <iostream>

template < typename T>
class Matrix
{
private:
	int rows, columns;
	T **arr;
public:
	Matrix();
	Matrix(int rows, int columns);
	Matrix(const Matrix &M);
	~Matrix();
	void set_rows(int rows){ this->rows = rows; }
	void set_columns(int columns){ this->columns = columns; }
	int get_rows(){ return this->rows; }
	int get_columns(){ return this->columns; }
	void set_at(int i, int j, const T& value);
	T at(int i, int j);
	Matrix<T> inverse();
	Matrix<T> transpose();
	T determinant();

	Matrix<T> operator+ (Matrix<T>& M);
	Matrix<T> operator* (Matrix<T>& M);
	Matrix<T> operator* (T& value);
	Matrix<T>& operator= (const Matrix<T>& M);
	Matrix<T>* operator= (const Matrix<T>* M);
	friend std::ostream& operator<< (std::ostream& o, const Matrix<T>& M)
	{
		//o.precision(4);
		for (int i = 0; i < M.rows; i++)
		{
			for (int j = 0; j < M.columns; j++)
				o << M.arr[i][j] << " ";
			o << std::endl;
		}
		return o;
	}
};

template < typename T>
Matrix<T>::Matrix()
{
	this->rows = 1;
	this->columns = 1;
	this->arr = new T*[rows];
	for (int i = 0; i < rows; i++)
	{
		this->arr[i] = new T[columns];
		for (int j = 0; j < columns; j++)
		{
			T *init = new T();
			arr[i][j] = *init;
			delete init;
		}
	}
}

template < typename T>
Matrix<T>::Matrix(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;
	this->arr = new T*[rows];
	for (int i = 0; i < rows; i++)
	{
		this->arr[i] = new T[columns];
		for (int j = 0; j < columns; j++)
		{
			//T tmp = 0;   ?????????????????
			T *init = new T();
			arr[i][j] = *init;
			delete init;
		}
	}
}

template < typename T>
Matrix<T>::Matrix(const Matrix &M)
{
	this->rows = M.rows;
	this->columns = M.columns;
	this->arr = new T*[rows];
	for (int i = 0; i < rows; i++)
	{
		this->arr[i] = new T[columns];
		for (int j = 0; j < columns; j++)
			arr[i][j] = M.arr[i][j];
	}
}

template < typename T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] this->arr[i];
	}
	delete[] this->arr;
}

template < typename T>
Matrix<T> Matrix<T>::operator+ (Matrix<T>& M)
{
	if (M.columns != this->columns || M.rows != this->rows)
	{
		throw std::invalid_argument("Invalid argument.");
	}
	Matrix<T> result(this->rows, this->columns);
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			result.arr[i][j] = this->arr[i][j] + M.arr[i][j];
		}
	}

	return result;
}

template < typename T>
Matrix<T> Matrix<T>::operator* (Matrix<T>& M)
{
	if (this->columns != M.rows)
	{
		throw std::invalid_argument("Invalid argument.");
	}
	Matrix<T> result(this->rows, M.columns);
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < M.columns; j++)
		{
			result.arr[i][j] = 0;
			for (int k = 0; k < this->columns; k++)
			{
				result.arr[i][j] += this->arr[i][k] * M.arr[k][j];
			}
		}
	}

	return result;
}

template < typename T>
Matrix<T> Matrix<T>::operator* (T& value)
{
	Matrix<T> result(this->rows, this->columns);
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			result.arr[i][j] = this->arr[i][j] * value;
		}
	}
	return result;
}

template < typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& M)
{
	if (&M == this)
	{
		return *this;
	}
	if (M.columns != this->columns || M.rows != this->rows)
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] this->arr[i];
		}
		delete[] this->arr;
		this->rows = M.rows;
		this->columns = M.columns;
		this->arr = new T*[rows];
		for (int i = 0; i < rows; i++)
		{
			this->arr[i] = new T[columns];
		}
	}
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			this->arr[i][j] = M.arr[i][j];
		}
	}

	return *this;
}

template < typename T>
Matrix<T>* Matrix<T>::operator= (const Matrix<T>* M)
{
	if (M == this)
	{
		return this;
	}
	if (M->columns != this->columns || M->rows != this->rows)
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] this->arr[i];
		}
		delete[] this->arr;
		this->rows = M->rows;
		this->columns = M->columns;
		this->arr = new T*[rows];
		for (int i = 0; i < rows; i++)
		{
			this->arr[i] = new T[columns];
		}
	}
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			this->arr[i][j] = M->arr[i][j];
		}
	}

	return this;
}

template < typename T>
void Matrix<T>::set_at(int i, int j, const T& value)
{
	if (i >= this->rows || j >= this->columns)
	{
		throw std::invalid_argument("Invalid argument.");
	}
	this->arr[i][j] = value;
}

template < typename T>
T Matrix<T>::at(int i, int j)
{
	if (i >= this->rows || j >= this->columns)
	{
		throw std::invalid_argument("Invalid argument.");
	}
	return this->arr[i][j];
}

template < typename T>
Matrix<T> Matrix<T>::inverse()
{
	if (this->rows != this->columns)
	{
		throw std::invalid_argument("Invalid argument.");
	}
	Matrix<T> result(this->rows, this->columns);
	Matrix<T> **matrix_matrix = new Matrix<T>*[columns];
	for (int i = 0; i < columns; i++)
	{
		matrix_matrix[i] = new Matrix<T>[columns];
		for (int j = 0; j < columns; j++)
		{
			matrix_matrix[i][j] = new Matrix<T>(columns - 1, columns - 1);
			for (int z = 0; z < columns - 1; z++)
			{
				for (int k = 0; k < columns - 1; k++)
				{
					if (k < i)
					{
						if (z < j)
						{
							matrix_matrix[i][j].arr[z][k] = this->arr[z][k];
						}
						else
						{
							matrix_matrix[i][j].arr[z][k] = this->arr[z + 1][k];
						}
					}
					else
					{
						if (z < j)
						{
							matrix_matrix[i][j].arr[z][k] = this->arr[z][k + 1];
						}
						else
						{
							matrix_matrix[i][j].arr[z][k] = this->arr[z + 1][k + 1];
						}
					}
				}
			}
		}
	}
	Matrix<T> det_matrix(columns, columns);
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			T r = matrix_matrix[j][i].determinant();
			det_matrix.arr[i][j] = pow(-1, (i + j)) * r;
		}
	}

	for (int i = 0; i < columns; i++)
	{
		delete[] matrix_matrix[i];
	}
	delete[] matrix_matrix;
	T tmp = 1 / determinant();
	result = det_matrix.transpose() * tmp;
	return result;
}

template < typename T>
Matrix<T> Matrix<T>::transpose()
{
	Matrix<T> result(this->rows, this->columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			result.arr[i][j] = this->arr[j][i];
		}
	}
	return result;
}

template < typename T>
T Matrix<T>::determinant()
{
	if (this->rows != this->columns)
	{
		throw std::invalid_argument("Invalid argument.");
	}
	T det = 0;
	if (columns == 1)
	{
		return this->arr[0][0];
	}
	Matrix<T> * vector_matrix = new Matrix<T>[columns];
	for (int i = 0; i < columns; i++)
	{
		vector_matrix[i] = new Matrix<T>(columns - 1, columns - 1);
		for (int j = 0; j < columns - 1; j++)
		{
			for (int z = 0; z < columns - 1; z++)
			{
				if (z < i)
				{
					vector_matrix[i].arr[j][z] = this->arr[j + 1][z];
				}
				else
				{
					vector_matrix[i].arr[j][z] = this->arr[j + 1][z + 1];
				}
			}
		}
	}
	for (int i = 0; i < columns; i++)
	{
		det += pow(-1, i) * this->arr[0][i] * vector_matrix[i].determinant();
	}

	delete[] vector_matrix;

	return det;
}