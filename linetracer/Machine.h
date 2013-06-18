
#pragma once
#include "common.h"
#include "Game.h"

//extern Game game;

//壁に当たったら左右に切り替える。
//マシン同士の衝突処理
//ルンバ
//machine
class Machine
{
public:
	//内部クラスの定義
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
	//(中心位置x,中心位置y,角度,サイズ)
	void Drawsquare(int zx,int zy,float theta,int size);
	virtual void DrawTracer(class Machine *a);
	Machine();
};

