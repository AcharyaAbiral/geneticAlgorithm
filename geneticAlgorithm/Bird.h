#pragma once
#include"Tunnel.h"
#include"raylib.h"
#include"nn.h"
class Bird
{
private:
	int id;
	bool alive;
	float width;
	float height;
	float distance;
	float vertical_speed;
	float vertical_pos;
	
	NN nn;
	
	Color color;

	static int count;
public:
	Bird(float x_l, float y_l, float v_pos);

	bool check_collision(Tunnel& tunnel);
	void update_distance();
	void update_vertical_speed();
	void update_state(float tunnel_height1,float tunnel_x_pos);
	void render();
	bool is_alive();
	void revive(float vertical_position);
	void genetic_algorithm(Bird& parent1, Bird& parent2);
	float get_distance();


};

