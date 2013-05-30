#include "common.h"
#include "Machine.h"

void Machine::turn_left(){
	theta += 3*M_PI/180;		
	x += cosf(theta);
	y += sinf(theta);
}
void Machine::turn_right(){
	theta -= 3*M_PI/180;
	x += cosf(theta);
	y += sinf(theta);
}
void Machine::go_straight_on(){
	x += cosf(theta);
	y += sinf(theta);
}
void Machine::stop(){
	x += 0;
	y += 0;
}

void Machine::switching(){
	sw=(sw)? false : true;
}

void Machine::handle(int value){
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

void Machine::move(Game *g){
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
		//if machine got out from the field
		if( tright.read(g) + tleft.read(g) ){
			h = tleft.read(g) + tright.read(g)*10;

		}
		handle(h);
	}
}

//(中心位置x,中心位置y,角度,サイズ)
void Machine::Drawsquare(int zx,int zy,float theta,int size){
	glBegin(GL_QUADS);
	glVertex2i(zx+size*cos(theta- 45*M_PI/180),zy+size*sin(theta- 45*M_PI/180) );
	glVertex2i(zx+size*cos(theta+ 45*M_PI/180),zy+size*sin(theta+ 45*M_PI/180) );
	glVertex2i(zx+size*cos(theta+135*M_PI/180),zy+size*sin(theta+135*M_PI/180) );
	glVertex2i(zx+size*cos(theta+225*M_PI/180),zy+size*sin(theta+225*M_PI/180) );
	glEnd();
}

void Machine::DrawTracer(class Machine *a)
{
	int zx,zy;
	//
	if( COLOR == BLACK )glColor3f(BB);
	else if( COLOR == WHITE )glColor3f(WW);
	//float tmp,squar=45*M_PI/180;

	//PLATE
	glColor3f(0.5,0.5,0.5);
	Drawsquare(a->x,a->y,a->theta,a->width/2);

	//OPT_SENSOR_LEFT
	glColor3f(BB);
	Drawsquare(a->oleft.x,a->oleft.y,a->theta,5);

	//OPT_SENSOR_RIGHT
	glColor3f(BB);
	Drawsquare(a->oright.x,a->oright.y,a->theta,5);

	//TCH_SENSOR_LEFT
	glColor3f(GG);
	Drawsquare(a->tleft.x,a->tleft.y,a->theta,5);

	//TCH_SENSOR_RIGHT
	glColor3f(GG);
	Drawsquare(a->tright.x,a->tright.y,a->theta,5);


	//LED_LEFT
	zx = a->x + a->height/4*cosf(a->theta+30*M_PI/180);
	zy = a->y + a->height/4*sinf(a->theta+30*M_PI/180);
	if(a->h / 10 )glColor3f(RR);
	else glColor3f(0.5,0,0);
	Drawsquare(zx,zy,a->theta,5);

	//LED_RIGHT
	zx = a->x + a->height/4*cosf(a->theta-30*M_PI/180);
	zy = a->y + a->height/4*sinf(a->theta-30*M_PI/180);
	if(a->h % 10 )glColor3f(RR);
	else glColor3f(0.5,0,0);
	Drawsquare(zx,zy,a->theta,5);

	//TIRE_LEFT
	zx = a->x + a->height/2*cosf(a->theta+90*M_PI/180);
	zy = a->y + a->height/2*sinf(a->theta+90*M_PI/180);
	glColor3f(BB);
	Drawsquare(zx,zy,a->theta,5);

	//TIRE_RIGHT
	zx = a->x + a->width/2*cosf(a->theta-90*M_PI/180);
	zy = a->y + a->width/2*sinf(a->theta-90*M_PI/180);
	glColor3f(BB);
	Drawsquare(zx,zy,a->theta,5);
}


Machine::Machine(){
	width=50;
	height=50;
	x=600;
	y=900;
	theta=0*M_PI/180;
	sw=false;
}

