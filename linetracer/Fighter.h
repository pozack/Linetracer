
#pragma once
#include "common.h"
#include "Game.h"
#include "Machine.h"

class weapon{
public:
	bool active;
	float x,y;
	float vx,vy;
	void move(){
		x+=vx;
		y+=vy;
		//active=false;
		if( x<0 || x>WIDTH ){
			vx=-vx;
		}
		if(  y<0 || y>HEIGHT ){
			vy=-vy;
		}
	}
	void DrawWeapon(){
		if(active){
			int r=10;
			glBegin(GL_TRIANGLE_FAN);
			//center
		#define PART 24
			glVertex2i(x,y);
			for(int i=0;i<PART+2;i++){
				glVertex2i(x+r*cos(2*i*M_PI/PART),y+r*sin(2*i*M_PI/PART) );
			}
			glEnd();
		}
	}
	weapon(){
		active=false;
	}
};

class Fighter : public Machine
{
public:
	float vx,vy;
	float ax,ay;
	float f,torque;
	float vtheta;
	int keystat;
	weapon w;

	void keycontrol(){
		if( keystat & STAT_GO )f=0.05;
		else if( keystat & STAT_BACK )f=-0.05;
		else f=0;
		//¶‚©‰E‚©
		if( keystat & STAT_LEFT )torque=-0.05*M_PI/180;
		else if( keystat & STAT_RIGHT )torque=0.05*M_PI/180;
		else torque=0;
		// ’e‚Ì”­ŽËˆ—
		if ( keystat & STAT_SHOT){
			shoot();
		}			
		//‰½‚à‰Ÿ‚µ‚Ä‚È‚¢‚Æ‚«
		if( (keystat & ~STAT_IDLE)==0 ){
			keystat=STAT_IDLE;
			f=torque=0;
		}
		if((x-w.x)*(x-w.x)+(y-w.y)*(y-w.y)<2250)w.active=false;
	}
	void move(){
		keycontrol();
		vtheta*=0.99;
		vx*=0.99;
		vy*=0.99;
		vtheta+=torque;
		theta+=vtheta;
		vx+=f*cosf(theta);
		vy+=f*sinf(theta);
		x+=vx;
		y+=vy;
		if( x<0 || x>WIDTH ){
			vx=-vx*0.1;
		}
		if(  y<0 || y>HEIGHT ){
			vy=-vy*0.1;
		}

		w.move();
	}
	void shoot(){
		if(w.active==false){
			w.active=true;
			w.x=x+50*cos(theta);
			w.y=y+50*sin(theta);
			w.vx=10*cos(theta);
			w.vy=10*sin(theta);
		}
	}

	void DrawTraiangle(float zx, float zy,float theta, float size){
		glBegin(GL_TRIANGLES);
			glVertex2f(zx+size*cos(theta),zy+size*sin(theta) );
			glVertex2f(zx+size/2*cos(theta+120*M_PI/180),zy+size/2*sin(theta+120*M_PI/180) );
			glVertex2f(zx+size/2*cos(theta+240*M_PI/180),zy+size/2*sin(theta+240*M_PI/180) );
		glEnd();
	}
	
	void DrawFighter(){
		glColor3f(0.1,0.1,0.1);
		DrawTraiangle(x,y,theta,50);
		glColor3f(0.9,0,0);
		DrawTraiangle(x,y,theta,20);
		w.DrawWeapon();
	}
	Fighter(){
		x=100;
		y=100;
		vx=vy=ax=ay=theta=vtheta=torque=0;
		keystat=STAT_IDLE;
	}
};