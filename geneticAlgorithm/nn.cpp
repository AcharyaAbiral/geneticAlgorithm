#include "nn.h"
//#include<cmath>
#include<cassert>
#include<iostream>

NN::NN(int i, int j, int k)
{

	layers = 3;
	activations = new Mat[3]
	{
		Mat(1,i),
		Mat(1,j),
		Mat(1,k)
	};

	weights = new Mat[2]
	{
		Mat(i,j),
		Mat(j,k)
	};

	biases = new Mat[2]
	{
		Mat(1,j),
		Mat(1,k)
	};

	
	//weights = new float[i * j + j * k];

	//biases = new float[j + k];

	/*tot_neurons = new int [3];

	tot_neurons[0] = i;
	tot_neurons[1] = j;
	tot_neurons[2] = k;*/
}

void NN::rand_init()
{
	for (int i = 0; i < layers - 1; i++)
	{
		weights[i].fill_rand();
		biases[i].fill_rand();
	}
}
void NN::set_input(float *inputs,int n)
{
	//if (n!=tot_neurons[0])
	assert(activations[0].col == n);

	for (int i = 0; i < n; i++)
	{
		*activations[0].at(0,i) = inputs[i];
	}
}

void NN::forward()
{
	//std::cout << "layers=" << layers<<std::endl;
	for (int i = 0; i < layers-1; i++)
	{
		//std::cout << "i= " << i << std::endl;
		mat_mul(activations[i + 1], activations[i], weights[i]);
		mat_add(activations[i + 1], activations[i+1],biases[i]);
		//std::cout << "after mul and add" << std::endl;
		//activations[i + 1].print_mat();
		mat_tanh(activations[i + 1]);
	}
}

void NN::print_nn()
{
	for (int i = 0; i < layers-1; i++)
	{
		std::cout << "activation " << i << std::endl;
		activations[i].print_mat();
		std::cout << "weight " << i << std::endl;
		weights[i].print_mat();
		std::cout << "biases " << i << std::endl;
		biases[i].print_mat();
	}
	std::cout << "output" << std::endl;
	activations[layers - 1].print_mat();
}

float NN::get_output()
{
	float out= *(activations[2].at(0, 0));
	//std::cout << "out=" << out << std::endl;
	if (out > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

