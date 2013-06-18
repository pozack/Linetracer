
#pragma once
#include "common.h"


class Game{
private:
	bool dot[WIDTH][HEIGHT];
	bool pen;
public:
	//ドットを読み込む
	bool getDot(int x,int y){return this->dot[x][y];}
	//ペンを読む
	bool getPen(){return this->pen;}
	//ドットを書き込む
	void setDot(int x,int y,bool color);
	//ペンに書き込む
	void setPen(bool color){this->pen=color;}
	//ドット線を描画する
	void DrawDots();
	Game();
	//~Game();
};
