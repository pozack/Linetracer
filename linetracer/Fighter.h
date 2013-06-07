#include "common.h"
#include "Game.h"
#include "Machine.h"

class weapon{
public:
	float x,y;
	float vx,vy;
	void move(){
		x=+vx;
		y=+vy;
	}
};

class Fighter : public Machine
{
public:
	float vx,vy;
	float ax,ay;
	float vtheta;
	int keystate;
	weapon w;
private:
	void readkey(){
			
		keystate;
	}
	void move(Game *g){
		readkey();
		

		vx+=ax;
		vx+=ay;
		x+=vx;
		y+=vy;
	}
	//void shoot();
};