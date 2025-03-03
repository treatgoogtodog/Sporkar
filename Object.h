#pragma once
#include <string>
#include <vector>
#include "NumberMath.h"

using namespace std;


enum TYPE
	{
		GROUND, WALL, NPC

};

struct HITBOX
{
	int x, y, x_size, y_size;
	HITBOX(int INPUTX, int INPUTY, int INPUT_VSIZE, int INPUT_HSIZE) {};
};

const instance* check_place(const vector<instance>& instance_list) 
{

}

bool collision_check(const instance* Tar, int fx, int fy, int fxsize, int fysize)
{
	bool check = (fx > Tar->x + Tar->x_size) || (fy > Tar->y + Tar->y_size) || (fx + fxsize < Tar->x) || (fy + fysize < Tar->y);
	return !check;
}


class instance
{
public:

	instance(int INPUTx, int INPUTy, int INPUT_XSIZE, int INPUT_YSIZE, bool SOLID, TYPE OBJ_TYPE) : x(INPUTx), y(INPUTy), x_size(INPUT_XSIZE), y_size(INPUT_YSIZE), is_solid(SOLID), type(OBJ_TYPE) {};



	int x, y;
	int x_size, y_size;
	bool is_solid;
	TYPE type;

	static vector <instance> instance_list;


	const instance* check_place(const vector<instance>& instance_list)
	{
		for (const instance& i : instance_list)
		{
			if (this->collision_check(&i))
			{
				return &i;
			}
		}
		return nullptr;
	}

	bool collision_check(const instance* Tar) {
		bool check = (this->x > Tar->x + Tar->x_size) || (this->y > Tar->y + Tar->y_size) || (this->x + this->x_size < Tar->x) || (this->y + this->y_size < Tar->y);
		return !check;
	}

};
// ALL TIMER ARE SET IN MILLISECOND!!

//player class
class Player : instance
{
public:
	enum direction
	{
		MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT
	};//It's for input
	direction Move;

	enum STATE
	{
		STANDBY, IDLE, MOVE, JUMP, DASH, SLAM
	};//5 states of players, if left standby for 10 seconds, it will triggers idle animation 
	
	STATE state = STANDBY;

	int32_t state_timer;
	//Special movement
	void dash();
	
	void jump();

	void slam();

	void end_slam();
	//Updating
	void state_update();

	void dash() {
	if (state != DASH)
		{
			state = DASH;
			state_timer = dash_time;
		}
	}

	void jump() {
		if (state != JUMP) 
		{
			state = JUMP;
			state_timer = jump_time;
		}
	}

	void slam() {
		if ((AIRBONE) && (state != SLAM)) {
			state = SLAM;
		}
	}

	void end_slam() {
		vy = 0;
		vx = 0;
		state = STANDBY;
	}

	void state_update() 
	{
		switch (this->state)
		{
		case STANDBY:
			vx -= BASE_ACCELARATION;

		case MOVE:
		{
			if (Move == MOVE_RIGHT) {
				vx += BASE_ACCELARATION;
				clamp(vx, -MAX_SPEED, MAX_SPEED);
			}
			if (Move == MOVE_LEFT) {
				vx -= BASE_ACCELARATION;
				clamp(vx, -MAX_SPEED, MAX_SPEED);
			}
		}

		case DASH:
		{
			state_timer--;
			if (Move == MOVE_RIGHT) {
				vx = DASH_SPEED;
			}
			else
			{
				if (Move == MOVE_LEFT) {
					vx = -DASH_SPEED;
				}
			}
		}

		case JUMP:
		{
			state_timer--;
			vy += JUMP_FORCE;
		}

		case SLAM:
		{
			vy = -SLAM_FORCE;
			if (AIRBONE == false) { end_slam(); }
		}
		default:
			break;
		}
		if (state_timer == 0) 
		{
			state = IDLE;
		}
	}

	void update_player()
	{
 
		AIRBONE = (this->check_place(instance_list))->type == GROUND;
		if (AIRBONE && (vy < 0)) { vy = 0; }
		if ((this->check_place(instance_list))->type == WALL){}
		x += vx;
		y += vy;
		
	}

private:
	bool AIRBONE;
	int vx, vy;// velocity on x - y axis
	uint32_t jump_time = 750;
	uint32_t dash_time = 500;

	int BASE_ACCELARATION;//if negative, it's deaccelaration
	int MAX_SPEED;
	int DASH_SPEED;

	uint32_t JUMP_FORCE;
	uint32_t SLAM_FORCE;

	
};