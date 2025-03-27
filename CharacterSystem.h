#pragma once
// ALL TIMER ARE SET IN MILLISECOND!!
#include "Object.h"
#include <string>
#include "json.hpp"
#include "Animation.h"

enum class Dir
{
	MOVE_LEFT, MOVE_RIGHT
};
enum class STATE
{
	STANDBY, IDLE, MOVE, JUMP, DASH, SLAM, FALL
};

class player : instance {
private:
	std::string name;
	int MAX_SPEED;
	int BASE_ACCELERATION;
	int DASH_SPEED;
	int dash_time;
	int jump_time;
	int JUMP_FORCE;
	int SLAM_FORCE;
	int AIRBONE;
	int x, y;
	int vx, vy;
	int BASE_DECELERATION;
public:
	Dir Move;
	STATE state;
	int32_t state_timer;
	bool IsAirbone() const;
	void dash();
	void jump();
	void slam();
	void idle();
	void state_update();
	int Load(std::string path);
	int Save(std::string path);
	void Update();
	void Render();
	void SetPosition(int x, int y);
	void SetVelocity(int vx, int vy);
};