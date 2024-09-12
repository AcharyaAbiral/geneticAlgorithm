#include "raylib.h"
#include<iostream>
#include<vector>
#include"Bird.h"
#include"Tunnel.h"
#include<ctime>
#include"nn.h"
#include<random>
#include<string>
//#include"mat.h"

void set_array(int* arr, int val,int cols);

void string_to_char(std::string& input_str, int l, char ans[]);


constexpr int TOT_BIRDS{ 40 };

int main()
{	

	int generation = 0;
	std::random_device rd;
	std::uniform_int_distribution<int>dist(50, 750);

	//std::cout << "hmmm" << std::endl;

	//Bird bird(30,30,400);


	std::vector<Bird> birds;
	//srand(time(0));

	for (int i = 0; i < TOT_BIRDS; i++)
	{
		float pos = dist(rd);
		std::cout << pos<<std::endl;
		birds.push_back(Bird(30, 30, pos));
	}
	int total_alive = TOT_BIRDS;
	int alive_status_array[TOT_BIRDS] ;
	
	set_array(alive_status_array, 1, TOT_BIRDS);
	

	std::vector<Tunnel> tunnels;

	tunnels.push_back(Tunnel(550));
	tunnels.push_back(Tunnel(850));

	
	InitWindow(500, 800, "geneticalgo");
	SetTargetFPS(60);


	int tunnel_turn = 0;

	int p1 = 0;
	int p2 = 0;
	int parent[2];
	parent[0] = -1;
	parent[1] = -1;
	int parent_turn = 0;
	int score = 0;
	std::string score_text_str = std::string("Score : ") + std::to_string(score);
	int length_of_score_str = score_text_str.length() + 1;
	char* score_text_char = new char[length_of_score_str];
	string_to_char(score_text_str, length_of_score_str - 1, score_text_char);
	
	std::string gen_text_str = std::string("Generation : ") + std::to_string(generation);
	int length_of_str = gen_text_str.length()+1;
	//std::cout << length_of_str;
	char* gen_text_char = new char[length_of_str];
	string_to_char(gen_text_str, length_of_str-1, gen_text_char);


	while (!WindowShouldClose())
	{
		BeginDrawing();
		//ClearBackground(CLITERAL(Color) { 0x60, 0xb0, 0xc0, 0xFF });
		ClearBackground(CLITERAL(Color) { 0xff, 0xb0, 0xc0, 0xFF });

		
		Tunnel& tunnel_for_check=tunnels[tunnel_turn];
		
		if (tunnel_for_check.get_x_position() <= 15)
		{
			tunnel_turn = (tunnel_turn + 1) % 2;
			score++;
			delete[] score_text_char;
			score_text_str = std::string("Score : ") + std::to_string(score);
			length_of_score_str = score_text_str.length() + 1;
			score_text_char = new char[length_of_score_str];
			//std::cout << "here" << std::endl;
			string_to_char(score_text_str, length_of_score_str - 1, score_text_char);

			
		}

		//bool alive=bird.check_collision(tunnel_for_check);

		/*if (!alive && IsKeyPressed(KEY_DOWN))
		{
			alive = true;
		}*/


		for (auto& tunnel : tunnels)
		{
			tunnel.update_state();
			/*if (alive)
			{

			}*/
			tunnel.render();
		}
		float tunnel_height1 = tunnel_for_check.get_height1();
		float tunnel_x_pos = tunnel_for_check.get_x_position();
		
		
		for (int i = 0; i < TOT_BIRDS; i++)
		{
			
			if (birds[i].is_alive())
			{
				//std::cout << "bird " << i << " is alive. ";
				//std::cout << "it becomes parent at index " << parent_turn << std::endl;
				if (i != parent[parent_turn])
				{
					parent_turn = (parent_turn + 1) % 2;

				}
				parent[parent_turn] = i;
				//std::cout << parent[0] << std::endl;
				//std::cout << parent[1] << std::endl;
				if (!birds[i].check_collision(tunnel_for_check))
				{
					total_alive--;
					//std::cout << "bird " << i << " died" << std::endl;
					
				};
				birds[i].update_state(tunnel_height1, tunnel_x_pos);
				birds[i].render();

			}
			
		}


		if (total_alive == 0)
		{
	
			tunnel_turn = 0;
			total_alive = TOT_BIRDS;
			parent_turn = 0;
			//set_array(alive_status_array, 1, TOT_BIRDS);
			tunnels[0].set_x_position(550);
			tunnels[1].set_x_position(850);
			//std::cout << "parent 0: " << parent[0] << std::endl;
			//std::cout << "parent 1: " << parent[1] << std::endl;
			for (int i = 0; i < TOT_BIRDS; i++)
			{
				//std::cout << i << ":i= " << birds[i].get_distance()<<std::endl;
				
				birds[i].revive(dist(rd));
				if (i != parent[0] && i != parent[1])
				{
					birds[i].genetic_algorithm(birds[parent[0]], birds[parent[1]]);
				}

				/*else
				{
					std::cout <<i<< " :i was selected."<<std::endl;
				}*/
			}
			parent[0] = -1;
			parent[1] = -1;
			generation++;
			score = 0;
			delete[] score_text_char;
			score_text_str = std::string("Score : ") + std::to_string(score);
			length_of_score_str = score_text_str.length() + 1;
			score_text_char = new char[length_of_score_str];
			//std::cout << "here" << std::endl;
			string_to_char(score_text_str, length_of_score_str - 1, score_text_char);

			//std::cout << generation << std::endl;
			//std::cout << "passed1" << std::endl;
			delete[] gen_text_char;
			//std::cout << "passed2" << std::endl;
			gen_text_str = std::string("Generation : ") + std::to_string(generation);
			length_of_str = gen_text_str.length()+1;
			gen_text_char = new char[length_of_str];
			//std::cout << "here" << std::endl;
			string_to_char(gen_text_str, length_of_str-1, gen_text_char);

		}

		/*if (IsKeyPressed(KEY_UP))
		{
			bird.update_vertical_speed();
		}*/

		//char text_array = text;
		DrawText(gen_text_char, 10, 10, 20, DARKGRAY);
		DrawText(score_text_char, 400, 10, 20, DARKGRAY);

		EndDrawing();
	}
	CloseWindow();
	return 0;
}

void set_array(int* arr, int val, int cols)
{
	for (int i = 0; i < cols; i++)
	{
		arr[i] = val;
	}

}

void string_to_char(std::string& input_str, int l,char ans[])
{
	//int l = input_str.length();
	for (int i = 0; i < l; i++)
	{
		ans[i] = input_str[i];
	}
	ans[l] = '\0';
}