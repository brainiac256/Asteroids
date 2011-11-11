#include "GameEngine.h"

std::list< ObjectCapsule > objectList;
unsigned long long counter = 0; //used to give each GameObject a unique ID, never decrements
int numOfObjects = 0; //used to keep track of how many objects in play at a time
bool key[5]= {false, false, false, false, false};
std::mt19937 randomEngine(time(NULL));

unsigned long long add(GameObject* o){
	if (numOfObjects < MAX_NUMBER_OF_OBJECTS) {
		++counter;
		objectList.push_back(ObjectCapsule(o, counter));
		++numOfObjects;
		return counter;
	} else {
		//delete o
		return -1;
	}
	return -1;
}
void updateEngine(void){
	for (std::list< ObjectCapsule >::iterator c = objectList.begin(); c != objectList.end(); c++)
	{
		c->o->update();
		if(c->o->needs_destroy()) {
			c = objectList.erase(c);
			--c ; //neeed because erase returns the position AFTER the erase, and we're already incrementing
		}
	}
}
void drawObjects(void){
	for (std::list< ObjectCapsule >::iterator c = objectList.begin(); c != objectList.end(); c++)
	{
		c->o->draw();
	}
}

bool isKeyOn(int k){
	return key[k];
}

void setKey(int k){
	key[k]=true;
}

void releaseKey(int k){
	key[k]=false;
}

void addVEC2(VEC2* va, VEC2* vb){
	float resultx = cos(va->angle)*(va->magnitude) + cos(vb->angle)*(vb->magnitude);
	float resulty = sin(va->angle)*(va->magnitude) + sin(vb->angle)*(vb->magnitude);
	va->angle = atan(resulty/resultx);
	if(resultx < 0) va->angle += PI;
	va->magnitude = sqrt(resulty*resulty + resultx*resultx);
}

void drawTriangle(TRIANGLE* t, ALLEGRO_COLOR c){
	al_draw_line(t->x[0], t->y[0],
		         t->x[1], t->y[1],
				 c, 0);
	al_draw_line(t->x[1], t->y[1],
		         t->x[2], t->y[2],
				 c, 0);
	al_draw_line(t->x[2], t->y[2],
		         t->x[0], t->y[0],
				 c, 0);
	return;
}

void drawQuad(QUAD* t, ALLEGRO_COLOR c){
	al_draw_line(t->x[0], t->y[0],
		         t->x[1], t->y[1],
				 c, 0);
	al_draw_line(t->x[1], t->y[1],
		         t->x[2], t->y[2],
				 c, 0);
	al_draw_line(t->x[2], t->y[2],
		         t->x[3], t->y[3],
				 c, 0);
	al_draw_line(t->x[3], t->y[3],
		         t->x[0], t->y[0],
				 c, 0);
	return;
}

float randfloat(float min, float max){
	std::uniform_real_distribution<float> d(min, max);
	float r = d(randomEngine);
	return r;
}

int randint(int min, int max){
	std::uniform_int_distribution<int> d(min, max);
	int r = d(randomEngine);
	return r;
}