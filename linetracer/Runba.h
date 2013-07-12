
#pragma once
#include "common.h"
#include "Floor.h"
#include "Machine.h"


// ��]���鎞�Ԃƒ��i���鎞�Ԃ𗐐��Ō��߂āA���̎��Ԃ�����܂Ŏd����������B
class Runba : public Machine
{
private:
	unsigned int time;
	bool turn,d;
public:
	float r;
	void go_straight_on();
	void turn_left();
	void turn_right();
	void DrawRunba();
	void DrawCircle(float x,float y,float r);
	void DrawFan(float x,float y,float r,float theta,float phi);
	void move(Floor *g);
	void clean(Floor *g);
	void handle(int value);
	void setTurn(bool turn){this->turn=turn;}
	void setTime(int time){this->time=time;}
	Runba(float x,float y,float theta);
};