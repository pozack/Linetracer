///////////////////////////////////////////////////////////////////
//                                                               //
//         ライントレーサ　　　　　　　　　　　　　　            //
//                                                               //
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <list>
#include <functional>
#include <string>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else 
	//#include <glut.h>//GLフォルダを作らずコピーした場合。
	#include <GL/glut.h>
#endif

using namespace std;
#define GLUT_CURSOR_RIGHT_ARROW 0
#define M_PI 3.14

#define BB 0,0,0
#define WW 1,1,1
#define RR 1,0,0
#define GG 0,1,0

#define BLACK false
#define WHITE true
#define WIDTH  1000
#define HEIGHT 800

#define BGCOLOR WHITE
#define COLOR BLACK 
//#define COLOR WHITE
//#define BGCOLOR BLACK 

#define LINEWIDTH 5



//キーの状態
#define STAT_IDLE	0x001
#define STAT_GO		0x002
#define STAT_BACK	0x004
#define STAT_LEFT	0x008
#define STAT_RIGHT	0x010
#define STAT_JUMP	0x020
#define STAT_SHOT	0x040
#define STAT_CVIEW	0x080
#define STAT_CWEAP  0x100
#define STAT_FLAG1	0x200	//視点切り替え
#define STAT_FLAG2	0x400	//武器切り替え
#define STAT_FLAG3	0x800	//ジャンプ用のフラグ


#define KEY_SHOT 'z'
#define KEY_CHANGE_WEAPON 'x'
#define KEY_CHANGE_VIEWPOINT 'a'
#define KEY_CHANGE_STAGE GLUT_KEY_F4
#define KEY_RESET GLUT_KEY_F5

#define NUMOFLINETRACER 3
#define NUMOFRUNBA 1
#define NUMOFFIGHTER 1
class Machine;
class opt_sensor;
class tch_sensor;
class Game;


//extern Game game;
//extern Machine m[3];


int getRandom(int max,int min);