#include "common.h"
#include "Floor.h"

void Floor::setDot(int x,int y,bool color)
{
	for(int i=x-LINEWIDTH;i<x+LINEWIDTH;i++){
		for(int j=y-LINEWIDTH ;j<y+LINEWIDTH;j++){
			if( (i>0)&&(i<WIDTH) && (j>0) && (j<HEIGHT)){
				dot[i][j]=color;
			}
		}
	}
}


void Floor::DrawDots()
{
	if(COLOR == BLACK)glColor3i(BB);
	else if(COLOR == WHITE)glColor3i(WW);
	glPointSize((GLint)1);
	glBegin(GL_POINTS);
	for(int x=0;x<WIDTH;x++){
		for(int y=0;y<HEIGHT;y++){
			if( dot[x][y] == COLOR )glVertex2i((GLint)x, (GLint)y);
		}
	}
	glEnd();
}

Floor::Floor()
{
	for(int x=0;x<WIDTH;x++){
		for(int y=0;y<HEIGHT;y++){
			dot[x][y] = BGCOLOR;
		}
	}
	pen=COLOR;
}