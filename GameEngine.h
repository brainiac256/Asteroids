#ifndef GEHEADER
#define GEHEADER
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\color.h>
#include <iostream>
#include <algorithm>
#include <list>
#include <set>
#include <cassert>
#include <random>

const unsigned long long MAX_NUMBER_OF_OBJECTS = MAXULONGLONG;
const float PI = ALLEGRO_PI;
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};

typedef struct LINE {
	float x[2];
	float y[2];
	LINE(float x1, float y1, float x2, float y2) {
		x[0] = x1;
		x[1] = x2;
		y[0] = y1;
		y[1] = y2;
	}
	LINE(void) {
		LINE(0,0,0,0);
	}
};

typedef struct TRIANGLE {
	float x[3];
	float y[3];
	TRIANGLE(float x1, float y1, float x2, float y2, float x3, float y3) {
		x[0] = x1;
		x[1] = x2;
		x[2] = x3;
		y[0] = y1;
		y[1] = y2;
		y[2] = y3;
	}
	TRIANGLE(void){
		TRIANGLE(0,0,0,0,0,0);
	}
};

typedef struct QUAD{
	float x[4];
	float y[4];
	QUAD(float x1, float y1, float x2, float y2,
		 float x3, float y3, float x4, float y4){
			 x[0]=x1; x[1]=x2; x[2]=x3; x[3]=x4;
			 y[0]=y1; y[1]=y2; y[2]=y3; y[3]=y4;
	}
	QUAD(void) {
		QUAD(0,0,0,0,0,0,0,0);
	}
};

typedef struct VEC2{
	float angle;
	float magnitude;
	VEC2(float a, float m) {
		angle=a;
		magnitude=m;
	}
	VEC2(void) {
		VEC2(0,0);
	}
};

class GameObject
{
public:
	GameObject(void){ this->destroyme = false; }
	virtual void update(void) = 0;
	virtual void draw(void) = 0;
	virtual void collide(GameObject* o) = 0;
	bool needs_destroy() { return destroyme; };
	float getX() {return x;}
	float getY() {return y;}
	float getS() {return size;}
	bool isInvincible() {return (invincibilitycooldown > 0);}
protected:
	bool destroyme;
	float x,y;
	float size;
	int invincibilitycooldown;
};

typedef struct ObjectCapsule {
	GameObject* o;
	int uniqueID;
	ObjectCapsule(GameObject* g, int i) {
		o = g;
		uniqueID = i;
	}
};

unsigned long long add(GameObject* o);

void updateEngine(void);
void drawObjects(void);

bool isKeyOn(int k);
void setKey(int k);
void releaseKey(int k);

void addVEC2(VEC2* va, VEC2* vb);

void drawTriangle(TRIANGLE* t, ALLEGRO_COLOR c);
void drawQuad(QUAD* q, ALLEGRO_COLOR c);

float randfloat(float min, float max);
int randint(int min, int max);

float squareDistance(float x1, float y1, float x2, float y2);

float smootherStep(float t);

void addScore(int n);

#endif //ndef GEHEADER
