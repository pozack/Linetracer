///////////////////////////////////////////////////////////////////
//                                                               //
//         ライントレーサ　　　　　　　　　　　　　　            //
//                                                               //
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else 
	//#include <glut.h>//GLフォルダを作らずコピーした場合。
	#include <GL/glut.h>
#endif

#define GLUT_CURSOR_RIGHT_ARROW 0
#define M_PI 3.14

#define BB 0,0,0
#define WW 1,1,1
#define RR 1,0,0
#define GG 0,1,0

#define BLACK false
#define WHITE true
#define WIDTH  600
#define HEIGHT 450

#define BGCOLOR WHITE
#define COLOR BLACK 
//#define COLOR WHITE
//#define BGCOLOR BLACK 

#define LINEWIDTH 5

class Machine;
class opt_sensor;
class tch_sensor;
class Game;


//extern Game game;
//extern Machine m[3];