
#pragma once
#include "common.h"
#include "Game.h"
#include "Machine.h"


// ��]���鎞�Ԃƒ��i���鎞�Ԃ𗐐��Ō��߂āA���̎��Ԃ�����܂Ŏd����������B
class Runba : public Machine
{
private:
	unsigned int time;
	bool turn,d;
public:
	float r;
	void turn_left();
	void turn_right();
	void DrawRunba();
	void DrawCircle(float x,float y,float r);
	void DrawFan(float x,float y,float r,float theta,float phi);
	void move(Game *g);
	void clean(Game *g);
	void handle(int value);
	void setTurn(bool turn){this->turn=turn;}
	void setTime(int time){this->time=time;}
	Runba(float x,float y,float theta);
};