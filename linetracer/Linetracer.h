#include "common.h"
#include "Game.h"
#include "Machine.h"


// ��]���鎞�Ԃƒ��i���鎞�Ԃ𗐐��Ō��߂āA���̎��Ԃ�����܂Ŏd����������B
class Linetracer : public Machine
{
public:
	//�����N���X�̒�`
	class opt_sensor{
	public:
		float x,y;
		bool read(Game *g){return g->getDot((int)x,(int)y);}
	};
	class tch_sensor{
	public:
		float x,y;
		//�����ɂ��鎞�́A0��Ԃ��B�ǂɓ���������1��Ԃ��B
		bool read(Game *g){return !(( x>0 && x<WIDTH)&&( y>0 && y<HEIGHT));}
	};
	//�����N���X�̃C���X�^���X��
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
	//(���S�ʒux,���S�ʒuy,�p�x,�T�C�Y)
	void Drawsquare(int zx,int zy,float theta,int size);
	virtual void DrawTracer(class Linetracer *a);
	Linetracer();
};