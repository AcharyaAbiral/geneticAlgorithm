#include "mat.h"
#include<cassert>
#include<cmath>
#include<iostream>
#include<iomanip>
//#include<ctime>
#include<random>

Mat::Mat(int r, int c)
{
	row = r;
	col = c;
	arr = new float[r * c];
}

void Mat::fill_rand()
{
	std::random_device rd;
	std::uniform_real_distribution<double> dist(-1.0, 1.0);
	//srand(time(0));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			*(this->at(i, j)) = dist(rd);
		}
	}
}

void Mat::print_mat()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{

			std::cout << std::fixed << std::setprecision(3) << *(this->at(i, j)) << "  ";
			//std::cout << *(this->at(i, j)) << "  ";
		}
		std::cout << std::endl;
	}
}

float* Mat::at(int i, int j)
{
	return arr + ((i * col) + j);
}

Mat::~Mat()
{
	delete[] arr;
}

void mat_mul(Mat& dest, Mat& m1, Mat& m2)
{
	//std::cout << m1.row << " * " << m1.col << std::endl;
	//std::cout << m2.row << " * " << m2.col << std::endl;
	//std::cout << std::endl;
	assert(m1.col == m2.row);
	assert(dest.row = m1.row);
	assert(dest.col = m2.col);
	int r = dest.row;
	int c = dest.col;
	int x = m1.col;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			float sum=0;
			for (int k = 0; k < x; k++)
			{
				sum+=(*(m1.at(i, k)))* (*(m2.at(k, j)));
			}
			*(dest.at(i, j)) = sum;
		}
	}
}

void mat_add(Mat& dest, Mat& m1, Mat& m2)
{
	assert(dest.row == m1.row && dest.row == m2.row);
	assert(dest.col == m1.col && dest.col == m2.col);
	int r = dest.row;
	int c = dest.col;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			*(dest.at(i, j)) = ( * (m1.at(i, j))) + ( * (m2.at(i, j)));
		}
	}
}

float sigmoidf(float x)
{
	return (1 / (1 + exp(-x)));
}

float my_tanhf(float x)
{
	return std::tanh(x);
}

void mat_sigmoid(Mat& m)
{
	for (int i = 0; i < m.col; i++)
	{
		*(m.at(0, i)) = sigmoidf(*(m.at(0, i)));
	}
}

void mat_tanh(Mat& m)
{
	for (int i = 0; i < m.col; i++)
	{
		*(m.at(0, i)) = my_tanhf(*(m.at(0, i)));
	}
}