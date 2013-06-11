#include "common.h"
#include "Linetracer.h"

void Linetracer::turn_left(){
	theta += 3*M_PI/180;		
	x += cosf(theta);
	y += sinf(theta);
}
void Linetracer::turn_right(){
	theta -= 3*M_PI/180;
	x += cosf(theta);
	y += sinf(theta);
}
void Linetracer::go_straight_on(){
	x += cosf(theta);
	y += sinf(theta);
}
void Linetracer::stop(){
	x += 0;
	y += 0;
}

void Linetracer::switching(){
	sw=(sw)? false : true;
}

void Linetracer::handle(int value){
	switch (value)
	{
	case 11:
		//stop();
		go_straight_on();
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
		stop();
		break;
	}
}

void Linetracer::move(Game *g){
	//
	oleft.x = x + height/2.3*cosf(theta+30*M_PI/180);
	oleft.y = y + height/2.3*sinf(theta+30*M_PI/180);
	oright.x = x + height/2.3*cosf(theta-30*M_PI/180);
	oright.y = y + height/2.3*sinf(theta-30*M_PI/180);
	//
	tleft.x = x + height/2*cosf(theta+45*M_PI/180);
	tleft.y = y + height/2*sinf(theta+45*M_PI/180);
	tright.x = x + height/2*cosf(theta-45*M_PI/180);
	tright.y = y + height/2*sinf(theta-45*M_PI/180);
	if(sw){
		h=( oleft.read(g) == COLOR )*10 + ( oright.read(g) == COLOR);
		//if Linetracer got out from the field
		if( tright.read(g) + tleft.read(g) ){
			h = tleft.read(g) + tright.read(g)*10;

		}
		if( (x<=0)||(x>=WIDTH)||(y<=0)||(y>=HEIGHT) ){
			h=2;
		}
		handle(h);
		g->setDot((int)x,(int)y,COLOR);
	}
}

//(中心位置x,中心位置y,角度,サイズ)
void Linetracer::Drawsquare(int zx,int zy,float theta,int size){
	glBegin(GL_QUADS);
	glVertex2i(zx+size*cos(theta- 45*M_PI/180),zy+size*sin(theta- 45*M_PI/180) );
	glVertex2i(zx+size*cos(theta+ 45*M_PI/180),zy+size*sin(theta+ 45*M_PI/180) );
	glVertex2i(zx+size*cos(theta+135*M_PI/180),zy+size*sin(theta+135*M_PI/180) );
	glVertex2i(zx+size*cos(theta+225*M_PI/180),zy+size*sin(theta+225*M_PI/180) );
	glEnd();
}

void Linetracer::DrawTracer()
{
	int zx,zy;
	//
	if( COLOR == BLACK )glColor3f(BB);
	else if( COLOR == WHITE )glColor3f(WW);
	//float tmp,squar=45*M_PI/180;

	//PLATE
	glColor3f(0.5,0.5,0.5);
	Drawsquare(x,y,theta,width/2);

	//OPT_SENSOR_LEFT
	glColor3f(BB);
	Drawsquare(oleft.x,oleft.y,theta,5);

	//OPT_SENSOR_RIGHT
	glColor3f(BB);
	Drawsquare(oright.x,oright.y,theta,5);

	//TCH_SENSOR_LEFT
	glColor3f(GG);
	Drawsquare(tleft.x,tleft.y,theta,5);

	//TCH_SENSOR_RIGHT
	glColor3f(GG);
	Drawsquare(tright.x,tright.y,theta,5);


	//LED_LEFT
	zx = x + height/4*cosf(theta+30*M_PI/180);
	zy = y + height/4*sinf(theta+30*M_PI/180);
	if(h / 10 )glColor3f(RR);
	else glColor3f(0.5,0,0);
	Drawsquare(zx,zy,theta,5);

	//LED_RIGHT
	zx = x + height/4*cosf(theta-30*M_PI/180);
	zy = y + height/4*sinf(theta-30*M_PI/180);
	if(h % 10 )glColor3f(RR);
	else glColor3f(0.5,0,0);
	Drawsquare(zx,zy,theta,5);

	//TIRE_LEFT
	zx = x + height/2*cosf(theta+90*M_PI/180);
	zy = y + height/2*sinf(theta+90*M_PI/180);
	glColor3f(BB);
	Drawsquare(zx,zy,theta,5);

	//TIRE_RIGHT
	zx = x + width/2*cosf(theta-90*M_PI/180);
	zy = y + width/2*sinf(theta-90*M_PI/180);
	glColor3f(BB);
	Drawsquare(zx,zy,theta,5);
}


Linetracer::Linetracer(float x,float y,float theta){
	width=50;
	height=50;
	this->x=x;
	this->y=y;
	this->theta=theta*M_PI/180;
	sw=false;
}

