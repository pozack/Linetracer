
#pragma once
#include "common.h"
#include "Game.h"
#include "Machine.h"


// 回転する時間と直進する時間を乱数で決めて、その時間がくるまで仕事をさせる。
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