#include "common.h"
#include "Game.h"
#include "Machine.h"


// 回転する時間と直進する時間を乱数で決めて、その時間がくるまで仕事をさせる。
class Linetracer : public Machine
{
public:
	//内部クラスの定義
	class opt_sensor{
	public:
		float x,y;
		bool read(Game *g){return g->getDot((int)x,(int)y);}
	};
	class tch_sensor{
	public:
		float x,y;
		//内側にある時は、0を返す。壁に当たったら1を返す。
		bool read(Game *g){return !(( x>0 && x<WIDTH)&&( y>0 && y<HEIGHT));}
	};
	//内部クラスのインスタンス化
	opt_sensor oleft;
	opt_sensor oright;
	tch_sensor tleft;
	tch_sensor tright;
	bool sw;
	int width;
	int height;
	int h;


	void turn_left();
	void turn_right();
	void go_straight_on();
	void stop();
	void switching();
	void handle(int value);
	void move(Game *g);
	//(中心位置x,中心位置y,角度,サイズ)
	void Drawsquare(int zx,int zy,float theta,int size);
	virtual void DrawTracer(class Linetracer *a);
	Linetracer();
};