#include "GameEngine.h"

std::vector< ObjectCapsule > objectList;
std::vector< Particle* > particleList;
unsigned long long counter = 0; //used to give each GameObject a unique ID, never decrements
int numOfObjects = 0; //used to keep track of how many objects in play at a time
bool key[5]= {false, false, false, false, false};
std::mt19937 randomEngine(time(NULL));
int score;

bool compareCapsules(ObjectCapsule a, ObjectCapsule b) {
	return (a.o->getX() < a.o->getX());
}

unsigned long long add(GameObject* o){
	assert(o != NULL);
	if (numOfObjects < MAX_NUMBER_OF_OBJECTS) {
		++counter;
		objectList.push_back(ObjectCapsule(o, counter));
		++numOfObjects;
		return counter;
	} else {
		delete o;
		return -1;
	}
	return -1;
}

void addParticle(Particle* p){
	particleList.push_back(p);
	return;
}

void updateEngine(void){
	std::list< ObjectCapsule* > sortedObjects;
	for (int c = 0; c < objectList.size(); )
	{
		objectList[c].o->update();

		//God help me, I'm doing brute-force collision detection now
		for(int n = 0; n < objectList.size(); ++n){
			//BRUTEFORCE COLLISION DETECTION LOOP, GOD SAVE US ALL
			if(n!=c &&
			   objectList[n].o->isInvincible() == false &&
			   objectList[c].o->isInvincible() == false &&
			   abs(objectList[n].o->getX() - objectList[c].o->getX()) < 12) {
					/*ALLEGRO_TRANSFORM t;
					al_identity_transform(&t);
					al_use_transform(&t);
					al_draw_rectangle(objectList[n].o->getX(), objectList[n].o->getY(), 
						              objectList[c].o->getX(), objectList[c].o->getY(), 
									  al_map_rgba_f(.2,.2,.6,.3),3);*/
				   // ^^^ collision visualization block ^^^
					objectList[n].o->collide(objectList[c].o);
					objectList[c].o->collide(objectList[n].o);
			}
			
		}
		
		if(objectList[c].o->needs_destroy()) {
			delete objectList[c].o;
			objectList[c] = objectList.back();
			objectList.pop_back();
			//no advance of iterator needed because we replaced the current object with the back object
		} else {
			//TODO: sort the object into a list for spatial hashing
			objectList[c].o->draw(); //draw the object
			++c; // advance the iterator
		}
	}//outer for-loop

	//draw particles

	//TODO: draw particles onto a separate buffer, blur it, and overdraw onto the screen display
	if(particleList.size() > 0) {
		ALLEGRO_TRANSFORM t;
		al_identity_transform(&t);
		al_use_transform(&t);
		for(int i=0; i < particleList.size(); ) {
			//draw particleList[i]
			al_draw_filled_circle(particleList[i]->x, particleList[i]->y, 1.5, particleList[i]->myColor);
			--(particleList[i]->life);
			if(particleList[i]->life < 0) {
				
				//remove particle from list by replacing from back
				particleList[i] = particleList.back();
				particleList.pop_back();
			} else {
				addVEC2(&(particleList[i]->velocity), &(particleList[i]->acceleration));
				particleList[i]->x += cos(particleList[i]->velocity.angle)*particleList[i]->velocity.magnitude;
				particleList[i]->y += sin(particleList[i]->velocity.angle)*particleList[i]->velocity.magnitude;
				//advance to next particle
				++i;
			}
		}
	}
	return;
}
void drawObjects(void){
	assert(false);
	//this functionality has been folded into updateEngine() for now
	return;
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
	assert(va != NULL);
	assert(vb != NULL);
	float resultx = cos(va->angle)*(va->magnitude) + cos(vb->angle)*(vb->magnitude);
	float resulty = sin(va->angle)*(va->magnitude) + sin(vb->angle)*(vb->magnitude);
	va->angle = atan(resulty/resultx);
	if(resultx < 0) va->angle += PI;
	va->magnitude = sqrt(resulty*resulty + resultx*resultx);
}

void drawTriangle(TRIANGLE* t, ALLEGRO_COLOR c){
	assert(t != NULL);
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
	assert(t != NULL);
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

float squareDistance( float x1, float y1, float x2, float y2){
	float d = pow(x1 - x2, 2) + pow(y1 - y2, 2);


	return d;
}

float smootherStep(float t){
	assert(t >= 0 && t <= 1);
	return t*t*t*(t*(t*6 - 15) + 10);
}

void addScore(int n){
	score += n;
	return;
}
