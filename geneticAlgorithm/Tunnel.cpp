#include "Tunnel.h"
#include"raylib.h"
#include<cmath>
#include<iostream>
#include<ctime>

Tunnel::Tunnel(int x_pos=0)
{
	x_position = x_pos;
	//srand(69);
	//rand_height();

	height1 = rand() % (580)+10;
	height2 = 800 - gap_length - height1;
	y_position1 = 0;
	y_position2 = height1 + gap_length;
}

Tunnel::Tunnel()
{
	//std::cout << "i was here";
}

void Tunnel::rand_height()
{
	this->height1 = rand() % (500);
	std::cout << height1 << std::endl;
	this->height2 = 800 - gap_length - height1;
}
void Tunnel::update_state()
{
	x_position=x_position-2;
	//std::cout << x_position << std::endl;
	if (x_position <= -85)
	{
		//std::cout << x_position << std::endl;
		//std::cout << "x_pos less than -85";
		x_position = 600 - 85;
		height1 = rand() % (580)+10;
		height2 = 800 - gap_length - height1;
		y_position2 = height1 + gap_length;

		//std::cout << "height1="<<height1 << std::endl;
		//std::cout <<"y_position="<< y_position2 << std::endl;
		//std::cout << "height2=" << height2 << std::endl;
		//rand_height();
	}
}
void Tunnel::render()
{
	DrawRectangle(x_position, y_position1, 85, height1, GREEN);
	DrawRectangle(x_position, y_position2, 85, height2, GREEN);

}



float Tunnel::get_height1()
{
	return height1;
}

float Tunnel::get_height2()
{
	return height2;
}

float Tunnel::get_x_position()
{
	return x_position;
}

float Tunnel::get_y_position1()
{
	return y_position1;
}

void Tunnel::set_x_position(float x_pos)
{
	x_position = x_pos;
}

float Tunnel::get_y_position2()
{
	return y_position2;
}
Tunnel& Tunnel::compare(Tunnel& tunnel)
{


	if ((x_position < tunnel.x_position)&&(x_position>=15))
	{
		std::cout << "first case";
		return *this;
	}
	/*else if ((tunnel.x_position<x_position)&&(tunnel.x_position)>=15)
	{
		std::cout << "second case";
		return tunnel;
	}*/
	else
	{
		std::cout << "second case";
		return tunnel;
	}
}