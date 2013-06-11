#include "common.h"
#include "Game.h"
#include "Machine.h"
#include "Runba.h"
#include "Linetracer.h"
#include "Fighter.h"

//
void OpenGL_init();
//ハンドラ
void display(void);
void timer(int dt);
void init();

void keydown(unsigned char key,int x,int y);
void keyup(unsigned char key,int x,int y);
void special_keydown(int key,int x,int y);
void special_keyup(int key,int x,int y);
void mouse(int x,int y);

//global variable
static Game game;
static Fighter f;
list<Linetracer> linetracerlist;
list<Runba> runbalist;


int main(void)
{
	init();
	OpenGL_init();
	return 0;
}


int getRandom(int max,int min){
	srand(time(NULL)); // 現在時刻を乱数の種の設定
	return min + rand()%(max - min); // MIN以上MAX未満の乱数を生成
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
	glutKeyboardFunc(keydown);//押したとき
	glutKeyboardUpFunc(keyup);//離れたとき
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMotionFunc(mouse);//ドラッグでラインを引く
	glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	glutTimerFunc(0,timer,10);
	glutMainLoop();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game.DrawDots();
	for( list<Linetracer>::iterator it = linetracerlist.begin(); it!=linetracerlist.end(); it++){
		it->DrawTracer();
	}
	for( list<Runba>::iterator it = runbalist.begin(); it!=runbalist.end(); it++){
		it->DrawRunba();
	}
	f.DrawFighter();
	glutSwapBuffers();
}

void timer(int dt)
{
	for( list<Linetracer>::iterator it = linetracerlist.begin(); it!=linetracerlist.end(); it++){
		it->move(&game);
	}

	list<Runba>::iterator it,jt;
	for( it = runbalist.begin(); it!=runbalist.end(); it++){
		for(  jt = runbalist.begin(); jt!=runbalist.end(); jt++){
			if(it==jt)continue;
			if( (it->x-jt->x)*(it->x-jt->x)+(it->y-jt->y)*(it->y-jt->y)< 4*it->r*it->r){
				it->setTurn(true);
				it->setTime(getRandom(50,60));
				//衝突による反動。卑怯技じゃない。
				it->x -= cosf(it->theta);
				it->y -= sinf(it->theta);
			}
		}
		it->move(&game);
	}
	f.move();
	glutPostRedisplay();
	glutTimerFunc(dt,timer,10);
}


void init()
{
	int i=0;
	for(int x=0;x<WIDTH;x++){
		for(int y=0;y<HEIGHT;y++){
			game.setDot(x,y,BGCOLOR);
		}
	}
	i=0;
	linetracerlist.insert(linetracerlist.end(),Linetracer(100,100,30));
	for( list<Linetracer>::iterator it = linetracerlist.begin(); i<NUMOFLINETRACER; i++,it++){
		it->x=WIDTH/2+WIDTH/3*cos(2*i*M_PI/NUMOFLINETRACER);
		it->y=HEIGHT/2+HEIGHT/3*sin(2*i*M_PI/NUMOFLINETRACER);
		it->theta=(360/NUMOFLINETRACER*i+180)*M_PI/180;
		it->tleft.x = it->x + it->height/2*cosf(it->theta+45*M_PI/180);
		it->tleft.y = it->y + it->height/2*sinf(it->theta+45*M_PI/180);
		it->tright.x = it->x + it->height/2*cosf(it->theta-45*M_PI/180);
		it->tright.y = it->y + it->height/2*sinf(it->theta-45*M_PI/180);
		linetracerlist.insert(linetracerlist.end(),*it);
	}
	runbalist.insert(runbalist.end(),Runba(100,100,30));
	i=0;
	for(list<Runba>::iterator it = runbalist.begin(); i<NUMOFRUNBA ; it++){
		it->x=WIDTH/2+WIDTH/2.3*cos(2*i*M_PI/NUMOFRUNBA);
		it->y=HEIGHT/2+HEIGHT/2.3*sin(2*i*M_PI/NUMOFRUNBA);
		it->theta=2*i*M_PI/NUMOFRUNBA;
		runbalist.insert(runbalist.end(),*it);
		i++;
	}
}


void mouse(int x,int y)
{
	game.setDot(x,y,game.getPen());
}


void keydown(unsigned char key,int x,int y){	
	switch (key) {
		case '8':	
			f.keystat|=STAT_GO;
			break;
		case '5':	
			f.keystat|=STAT_BACK;
			break;
		case '4':
			f.keystat|=STAT_LEFT;
			break;
		case '6':	
			f.keystat|=STAT_RIGHT;
			break;
            /*
		case 'y':	//ジャンプ
			f.keystat|=STAT_JUMP;
			break;
             */
		case KEY_SHOT:	//ショット
			f.keystat|=STAT_SHOT;
			break;
		case KEY_CHANGE_VIEWPOINT:	//視点切り替え
			f.keystat |= STAT_CVIEW;
			break;
		case KEY_CHANGE_WEAPON:	//視点切り替え
			f.keystat |= STAT_CWEAP;
			break;
		case 27:
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
			for( list<Linetracer>::iterator it = linetracerlist.begin(); it!=linetracerlist.end(); it++){
				it->switching();
			}
			for( list<Runba>::iterator it = runbalist.begin(); it!=runbalist.end(); it++){
				it->switching();
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

void keyup(unsigned char key,int x,int y){	
	switch (key){
		case '8':	
			f.keystat &= ~STAT_GO;
			break;
		case '5':	
			f.keystat &= ~STAT_BACK;
			break;
		case '4':
			f.keystat &= ~STAT_LEFT;
			break;
		case '6':	
			f.keystat &= ~STAT_RIGHT;
			break;
            /*
		case 'y':	//ジャンプ
			f.keystat &= ~STAT_JUMP;
			break;
             */
		case KEY_SHOT:	//ショット
			f.keystat &= ~STAT_SHOT;
			break;
		case KEY_CHANGE_VIEWPOINT:	//視点切り替え
			f.keystat &= ~STAT_CVIEW;
			f.keystat &= ~STAT_FLAG1;	//フラグリセット
			break;
		case KEY_CHANGE_WEAPON:	//武器切り替え
			f.keystat &= ~STAT_CWEAP;
			f.keystat &= ~STAT_FLAG2;	//フラグリセット
			break;
		default:
			break;
	}
	glutPostRedisplay();
}


void special_keydown(int key,int x,int y){
	switch (key) {
		case GLUT_KEY_UP:	//前進
			f.keystat|=STAT_GO;
			break;
		case GLUT_KEY_DOWN:	//後進
			f.keystat|=STAT_BACK;
			break;
		case GLUT_KEY_LEFT:	//左旋回
			f.keystat|=STAT_LEFT;
			break;
		case GLUT_KEY_RIGHT:	//右旋回
			f.keystat|=STAT_RIGHT;
			break;
		case KEY_RESET:
			//f.time=0;
			//model_init(s);
			break;
		case KEY_CHANGE_STAGE:
			//f.time=0;
            //property.stagetype++;
            //if(property.stagetype==MAX_STAGE)property.stagetype=0;
			//model_init(s);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void special_keyup(int key,int x,int y){
	switch (key){
		case GLUT_KEY_UP:	//前進
			f.keystat &= ~STAT_GO;
			break;
		case GLUT_KEY_DOWN:	//後進
			f.keystat &= ~STAT_BACK;
			break;
		case GLUT_KEY_LEFT:	//左旋回
			f.keystat &= ~STAT_LEFT;
			break;
		case GLUT_KEY_RIGHT:	//右旋回
			f.keystat &= ~STAT_RIGHT;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
