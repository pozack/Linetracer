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
	void DrawTracer(Runba *a);
	void DrawCircle(float x,float y,float r);
	void move(Game *g);
	void clean(Game *g, float x,float y,float r);
	void handle(int value);
	void setTurn(bool turn){this->turn=turn;}
	void setTime(int time){this->time=time;}
	Runba();
};