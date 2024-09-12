#pragma once
#include"mat.h"
class NN
{
public:


	Mat* activations;
	Mat* weights;
	Mat* biases;
	int layers;

	//float* first_layer;
	//float* second_layer;
	//float* weights;
	//float* biases;
	//float output;
	
	//int* tot_neurons;

	NN(int i, int j, int k);
	void rand_init();
	void set_input(float * inputs,int n);
	void forward();
	float get_output();
	void print_nn();
};

