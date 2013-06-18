
#pragma once
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

