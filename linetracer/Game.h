
#pragma once
#include "common.h"


class Game{
private:
	bool dot[WIDTH][HEIGHT];
	bool pen;
public:
	//�h�b�g��ǂݍ���
	bool getDot(int x,int y){return this->dot[x][y];}
	//�y����ǂ�
	bool getPen(){return this->pen;}
	//�h�b�g����������
	void setDot(int x,int y,bool color);
	//�y���ɏ�������
	void setPen(bool color){this->pen=color;}
	//�h�b�g����`�悷��
	void DrawDots();
	Game();
	//~Game();
};
