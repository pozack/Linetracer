#include "common.h"
#include "Game.h"
#include "Machine.h"
#include "Runba.h"
#include "Linetracer.h"


//
void OpenGL_init();
//�n���h��
void display(void);
void timer(int dt);
void init();
void key(unsigned char k, int x, int y);
void mouse(int x,int y);

//global variable
static Game game;
static Linetracer m[NUMOFLINETRACER];
static Runba r[NUMOFRUNBA];

int main(void)
{
	init();
	OpenGL_init();
	return 0;
}


int getRandum(int max,int min){
	srand(time(NULL)); // ���ݎ����𗐐��̎�̐ݒ�
	return min + rand()%(max - min); // MIN�ȏ�MAX�����̗����𐶐�
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

	glClearColor( WW, 1);	//�I�Z���Ղ̐F
	//else glClearColor( BB, 1);

	gluOrtho2D(0, WIDTH, HEIGHT, 0);//���W���̐ݒ�
	glutSetCursor(GLUT_CURSOR_HELP);

	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutMotionFunc(mouse);//�h���b�O�Ń��C��������
	glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	glutTimerFunc(0,timer,10);
	glutMainLoop();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game.DrawDots();
	for(int i=0;i<NUMOFLINETRACER;i++){
		m[i].DrawTracer(&m[i]);
	}
	for(int i=0;i<NUMOFRUNBA;i++){
		r[i].DrawTracer(&r[i]);
	}
	glutSwapBuffers();
}

void timer(int dt)
{
	for(int i=0;i<NUMOFLINETRACER;i++){
		m[i].move(&game);
	}
	for(int i=0;i<NUMOFRUNBA;i++){
		for(int j=0;j<NUMOFRUNBA;j++){
			if(i==j)continue;
			if( (r[i].x-r[j].x)*(r[i].x-r[j].x)+(r[i].y-r[j].y)*(r[i].y-r[j].y)< 4*r[i].r*r[i].r){
				r[i].setTurn(true);
				r[i].setTime(getRandum(50,60));
				//�Փ˂ɂ�锽���B�ڋ��Z����Ȃ��B
				r[i].x -= cosf(r[i].theta);
				r[i].y -= sinf(r[i].theta);
			}
		}
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
	for(int i=0;i<NUMOFLINETRACER;i++){
		m[i].x=WIDTH/2+WIDTH/3*cos(2*i*M_PI/NUMOFLINETRACER);
		m[i].y=HEIGHT/2+HEIGHT/3*sin(2*i*M_PI/NUMOFLINETRACER);
		m[i].theta=(360/NUMOFLINETRACER*i+180)*M_PI/180;
		m[i].tleft.x = m[i].x + m[i].height/2*cosf(m[i].theta+45*M_PI/180);
		m[i].tleft.y = m[i].y + m[i].height/2*sinf(m[i].theta+45*M_PI/180);
		m[i].tright.x = m[i].x + m[i].height/2*cosf(m[i].theta-45*M_PI/180);
		m[i].tright.y = m[i].y + m[i].height/2*sinf(m[i].theta-45*M_PI/180);
	}
	for(int i=0;i<NUMOFRUNBA;i++){
		r[i].x=WIDTH/2+WIDTH/2.3*cos(2*i*M_PI/NUMOFRUNBA);
		r[i].y=HEIGHT/2+HEIGHT/2.3*sin(2*i*M_PI/NUMOFRUNBA);
		r[i].theta=2*i*M_PI/NUMOFRUNBA;
		r[i].tleft.x = r[i].x + r[i].height/2*cosf(r[i].theta+45*M_PI/180);
		r[i].tleft.y = r[i].y + r[i].height/2*sinf(r[i].theta+45*M_PI/180);
		r[i].tright.x = r[i].x + r[i].height/2*cosf(r[i].theta-45*M_PI/180);
		r[i].tright.y = r[i].y + r[i].height/2*sinf(r[i].theta-45*M_PI/180);

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
		for(int i=0;i<NUMOFLINETRACER;i++){
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