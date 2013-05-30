#include "common.h"
#include "Game.h"
#include "Machine.h"


//
void OpenGL_init();
//ハンドラ
void display(void);
void timer(int dt);
void init();
void key(unsigned char k, int x, int y);
void mouse(int x,int y);

//global variable
static Game game;
static Machine m[NUMOFMACHINE];
static Runba r[NUMOFRUNBA];

int main(void)
{
	init();
	OpenGL_init();
	return 0;
}

void OpenGL_init()
{
	int i=1;
	char *cv[1]={"Router_Man"};
	glutInit(&i, cv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("LINE TRACER");

	glClearColor( WW, 1);	//オセロ盤の色
	//else glClearColor( BB, 1);

	gluOrtho2D(0, WIDTH, HEIGHT, 0);//座標軸の設定
	glutSetCursor(GLUT_CURSOR_HELP);

	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutMotionFunc(mouse);//ドラッグでラインを引く
	glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	glutTimerFunc(0,timer,10);
	glutMainLoop();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game.DrawDots();
	for(int i=0;i<NUMOFMACHINE;i++){
		m[i].DrawTracer(&m[i]);
	}
	for(int i=0;i<NUMOFRUNBA;i++){
		r[i].DrawTracer(&r[i]);
	}
	glutSwapBuffers();
}

void timer(int dt)
{
	for(int i=0;i<NUMOFMACHINE;i++){
		m[i].move(&game);
	}
	for(int i=0;i<NUMOFRUNBA;i++){
		r[i].move(&game);
	}
	glutPostRedisplay();
	glutTimerFunc(dt,timer,10);
}


void init()
{
	for(int x=0;x<WIDTH;x++){
		for(int y=0;y<HEIGHT;y++){
			game.setDot(x,y,BGCOLOR);
		}
	}
	for(int i=0;i<NUMOFMACHINE;i++){
		m[i].x=100*i+100;
		m[i].y=100;
		m[i].theta=0*M_PI/180;
	}
	for(int i=0;i<NUMOFRUNBA;i++){
		r[i].x=100*i+100;
		r[i].y=200;
		r[i].theta=0*M_PI/180;
	}
}


void key(unsigned char k, int x, int y)
{
	switch (k) {
	case 27:  /* Escape */
		exit(0);
		break;
	case 127: /* delete */
		if(game.getPen() == BGCOLOR ){
			glutSetCursor(GLUT_CURSOR_DESTROY);
			game.setPen(COLOR);
		}else{
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
			game.setPen(BGCOLOR);
		}
		break;
	case 13: /* ENTER */
		for(int i=0;i<NUMOFMACHINE;i++){
			m[i].switching();
		}
		for(int i=0;i<NUMOFRUNBA;i++){
			r[i].switching();
		}
		break;
	case 8: /* bakspace */
		init();
		break;
	case 'i': /* increase machine */
		//init();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


void mouse(int x,int y)
{
	game.setDot(x,y,game.getPen());
}