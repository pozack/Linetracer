#include "common.h"
#include "Game.h"

//extern Game game;

//�ǂɓ��������獶�E�ɐ؂�ւ���B
//�}�V�����m�̏Փˏ���
//�����o
//machine
class Machine
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

	float x,y,theta;
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
	virtual void DrawTracer(class Machine *a);
	Machine();
};

class Runba : public Machine
{
private:
	float r;
public:
	void DrawTracer(Runba *a);
	void DrawCircle(float x,float y,float r);
	void move(Game *g);
	Runba();
};