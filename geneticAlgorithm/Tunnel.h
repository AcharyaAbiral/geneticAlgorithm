#pragma once
//constexpr int gap_length{ 120 };
class Tunnel
{
private:
	float height1;
	float y_position1;
	float height2;
	float y_position2;
	float x_position;
	static constexpr int gap_length = 200;
	
public:
	Tunnel(int x_pos);
	Tunnel();
	void rand_height();
	void update_state();
	void render();
	Tunnel& compare(Tunnel& tunnel);
	float get_x_position();
	float get_height1();
	float get_height2();
	float get_y_position1();
	float get_y_position2();
	void set_x_position(float x_pos);
};

