#pragma once
class Mat
{
public:
	float* arr;
	int row; 
	int col;
	Mat(int r, int  c);
	void fill_rand();
	void print_mat();
	float* at(int i, int j);
	friend void mat_mul(Mat& dest, Mat& m1, Mat& m2);
	friend void mat_add(Mat& dest, Mat& m1, Mat& m2);
	
	~Mat();
};
void mat_mul(Mat& dest, Mat& m1, Mat& m2);
void mat_add(Mat& dest, Mat& m1, Mat& m2);
void mat_sigmoid(Mat& m);
float sigmoidf(float x);
float my_tanhf(float x);
void mat_tanh(Mat& m);


