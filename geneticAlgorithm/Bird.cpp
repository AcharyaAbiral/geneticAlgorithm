#include "Bird.h"
//#include "raylib.h"
#include<iostream>
#include<random>

constexpr int horizontal_pos{ 90 };
constexpr float GRAVITY{ 0.4 };
//#define horizontal_pos 40

int Bird::count = 0;
Bird::Bird(float x_l, float y_l, float v_pos) :width(x_l), height(y_l), vertical_pos(v_pos),nn(4,6,1)
{
	id = count++;
	alive = true;
	vertical_speed = 0;
	distance = 0;
	float factor = (float)(id+50) / 100;
	color = { (unsigned char) (253*factor),(unsigned char)(249*factor),(unsigned char)(0*factor),255 };
	nn.rand_init();
}

void Bird::render()
{


	DrawRectangle(horizontal_pos, vertical_pos, width, height, color);
}

void Bird::update_state(float tunnel_height1,float tunnel_x_pos)
{


	float input[] = { vertical_pos / 800,vertical_speed / 25,tunnel_height1 / 800 ,tunnel_x_pos/500};
	nn.set_input(input, 4);
	nn.forward();
	int flap = nn.get_output();
	//std::cout << "flap=" << flap << std::endl;

	if (flap)
	{
		update_vertical_speed();
	}

	vertical_speed += GRAVITY;
	//std::cout << "vertical_speed = " << vertical_speed << std::endl;
	distance++;
	vertical_pos += vertical_speed;
	if ((vertical_pos + 30) >= 800)
	{
		vertical_speed = 0;
		vertical_pos = 770;
	}
	if ((vertical_pos) <= 0)
	{
		vertical_speed = 0;
		vertical_pos = 0;
	}

	distance++;
}

void Bird::update_vertical_speed()
{
	vertical_speed = -9;
}

bool Bird::check_collision(Tunnel& tunnel)
{
	if (vertical_pos + height >= 800)
	{
		alive = false;
	}
	else if (vertical_pos<=0)
	{
		alive = false;
	}
	else if (vertical_pos <= tunnel.get_height1() && (tunnel.get_x_position() - horizontal_pos) <= width)
	{
		alive = false;
	}
	else if (((vertical_pos + height) >= tunnel.get_y_position2()) && (tunnel.get_x_position() - horizontal_pos) <= width)
	{
		alive = false;
	}
	return alive;
}

float Bird::get_distance()
{
	return distance;
}


bool Bird::is_alive()
{
	return alive;
}
void Bird::update_distance()
{
}

void Bird::revive(float vertical_position)
{
	vertical_pos = vertical_position;
	alive = true;
	distance = 0;
	
}

void Bird::genetic_algorithm(Bird& parent1, Bird& parent2)
{
	std::random_device rd;
	std::uniform_int_distribution<int>dist1(0, 1);
	std::uniform_real_distribution<double> dist2(-1.0, 1.0);
	std::uniform_int_distribution<int> mutation(0, 10);
	for (int i = 0; i < nn.layers - 1; i++)
	{
		for (int r = 0; r < nn.weights[i].row; r++)
		{
			for (int c = 0; c < nn.weights[i].col; c++)
			{
				if (mutation(rd) == 0)
				{
					*(nn.weights[i].at(r, c)) = dist2(rd);
				}
				else 
				{
					if (dist1(rd))
					{
						*(nn.weights[i].at(r, c)) = *(parent1.nn.weights[i].at(r, c));
					}
					else
					{
						*(nn.weights[i].at(r, c)) = *(parent2.nn.weights[i].at(r, c));

					}
				}
			}
			
		}
		for (int r = 0; r < nn.biases[i].row; r++)
		{
			for (int c = 0; c < nn.biases[i].col; c++)
			{
				if (mutation(rd) == 0)
				{
					*(nn.biases[i].at(r, c)) = dist2(rd);
				}
				else
				{
					if (dist1(rd))
					{
						*(nn.biases[i].at(r, c)) = *(parent1.nn.biases[i].at(r, c));
					}
					else
					{
						*(nn.biases[i].at(r, c)) = *(parent2.nn.biases[i].at(r, c));

					}
				}
			}
		}
	}
}