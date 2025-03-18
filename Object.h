#pragma once
#include <string>
#include <vector>
#include "NumberMath.h"
#include "Animation.h"

using namespace std;

class instance
{
public:
	enum TYPE
	{
		GROUND, WALL, PLAYER, NPC
	};
	string sprite;
	int x, y;
	int x_size, y_size;
	bool is_solid;
	TYPE type;



	static vector <instance> INSTANCE_LIST;	

	const instance* check_place(const vector<instance> &instance_list)
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
class Player : instance
{
public:
	enum move
	{
		MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT
	}'';
	move Move;

	enum STATE
	{
		STANDBY, IDLE, MOVE, JUMP, DASH, SLAM
	}; 
	
	STATE state;

	int32_t state_timer;

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
		x += vx;
		y += vy;
		AIRBONE = (this->check_place(INSTANCE_LIST))->type == GROUND;
	}

private:
	bool AIRBONE;
	int vx, vy;// velocity on x - y axis
	uint32_t jump_time = 750;
	uint32_t dash_time = 500;

	int BASE_ACCELARATION;//if negative, it's deaccelaration
	int MAX_SPEED;
	int DASH_SPEED;

	int32_t JUMP_FORCE;
	int32_t SLAM_FORCE;
};