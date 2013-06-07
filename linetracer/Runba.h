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
		class tch_sensor{
	public:
		float x,y;
		//内側にある時は、0を返す。壁に当たったら1を返す。
		bool read(Game *g){return !(( x>0 && x<WIDTH)&&( y>0 && y<HEIGHT));}
	};
	//内部クラスのインスタンス化
	tch_sensor tleft;
	tch_sensor tright;
	float r;
	void turn_left();
	void turn_right();
	void DrawTracer(Runba *a);
	void DrawCircle(float x,float y,float r);
	void DrawFan(float x,float y,float r,float theta,float phi);
	void move(Game *g);
	void clean(Game *g);
	void handle(int value);
	void setTurn(bool turn){this->turn=turn;}
	void setTime(int time){this->time=time;}
	Runba();
};