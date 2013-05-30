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
	void DrawTracer(Runba *a);
	void DrawCircle(float x,float y,float r);
	void move(Game *g);
	void clean(Game *g, float x,float y,float r);
	void handle(int value);
	void setTurn(bool turn){this->turn=turn;}
	void setTime(int time){this->time=time;}
	Runba();
};