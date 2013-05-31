#include "common.h"
#include "Runba.h"
Runba::Runba(){
	time=300;
	turn=false;
	d=false;
	r=30;
	width=50;
	height=50;
	x=600;
	y=900;
	theta=0*M_PI/180;
	sw=false;
}

void Runba::DrawCircle(float x,float y,float r){
	glBegin(GL_TRIANGLE_FAN);
	//center
#define PART 24
	glVertex2i(x,y);
	for(int i=0;i<PART+2;i++){
		glVertex2i(x+r*cos(2*i*M_PI/PART),y+r*sin(2*i*M_PI/PART) );
	}
	glEnd();
}

void Runba::DrawFan(float x,float y,float r,float theta,float phi){
	glBegin(GL_TRIANGLE_FAN);
	//center
#define FANS 24
	glVertex2i(x,y);
	for(int i=0;i<FANS;i++){
		glVertex2i(x+r*cos(theta+phi/FANS*i*M_PI/180-phi*M_PI/180/2),y+r*sin(theta+phi/FANS*i*M_PI/180-phi*M_PI/180/2) );
	}
	glEnd();
}



void Runba::DrawTracer(Runba *a)
{
	//
	if( COLOR == BLACK )glColor3f(BB);
	else if( COLOR == WHITE )glColor3f(WW);
	//float tmp,squar=45*M_PI/180;


	//PLATE
	glColor3f(0.1,0.1,0.1);
	DrawCircle(a->x,a->y,a->r);
	glColor3f(0.9,0.9,0.9);
	DrawCircle(a->x,a->y,a->r*0.9);
	
	glColor3f(0.1,0.1,0.1);
	DrawFan(a->x,a->y,a->r*0.75,a->theta,120);
	glColor3f(0.9,0.9,0.9);
	DrawFan(a->x,a->y,a->r*0.65,a->theta,120);
	
	glColor3f(0.1,0.1,0.1);
	DrawCircle(a->x,a->y,a->r*0.5);
	glColor3f(0.9,0.9,0.9);
	DrawCircle(a->x,a->y,a->r*0.2);
}



void Runba::move(Game *g){
	if(sw){
		//
		if(time<=0){
			turn=!turn;
			if(turn)time=getRandum(1,100);
			else time=getRandum(100,300);
			d=(time%2==0);
		}
		if( (x<r)||(x>WIDTH-r)||(y<r)||(y>HEIGHT-r) ){
			turn=true;
			time=getRandum(50,60);
			d=(time%2==0);
			//衝突による反動。卑怯技じゃない。
			x -= cosf(theta);
			y -= sinf(theta);
		}
		if(turn){
			if(d)handle(1);//turn left
			else handle(10);//turn right
		}else{
			handle(0);//fowarding
		}		
		tleft.x = x + height/2*cosf(theta+45*M_PI/180);
		tleft.y = y + height/2*sinf(theta+45*M_PI/180);
		tright.x = x + height/2*cosf(theta-45*M_PI/180);
		tright.y = y + height/2*sinf(theta-45*M_PI/180);
		clean(g);
		time--;
	}
}

//Runba clean the line.
void Runba::clean(Game *g){
	//計算量を減らすために、ルンバの横のみ調べる。(GOAL)
	float ay=-cos(theta);
	float ax=sin(theta);
	for(float i=-r/2;i<r/2;i+=3){
		g->setDot(x+ax*i,y+ay*i,BGCOLOR);
	}
	/*
	for(int dx=x-r;dx<x+r;dx++){
		for(int dy=y-r;dy<y+r;dy++){
			if((dx-x)*(dx-x)+(dy-y)*(dy-y)<r*r)g->setDot(dx,dy,BGCOLOR);
		}
	}
	*/
}


void Runba::turn_left(){
	theta += 3*M_PI/180;		
}
void Runba::turn_right(){
	theta -= 3*M_PI/180;
}

void Runba::handle(int value){
	switch (value)
	{
	case 11:
		stop();
		break;
	case 10:
		turn_left();
		break;
	case  1:
		turn_right();
		break;
	case  0:
		go_straight_on();
		break;
	default:
		go_straight_on();
		break;
	}
}