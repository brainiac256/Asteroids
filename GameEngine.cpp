#include "GameEngine.h"

std::list< ObjectCapsule > objectList;
unsigned long long counter = 0; //used to give each GameObject a unique ID, never decrements
int numOfObjects = 0; //used to keep track of how many objects in play at a time
bool key[5]= {false, false, false, false, false};
std::mt19937 randomEngine(time(NULL));

bool compareCapsules(ObjectCapsule a, ObjectCapsule b) {
	return (a.o->getX() < a.o->getY());
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

void mergeInsert(std::list< ObjectCapsule* > *l, ObjectCapsule* c){
	assert(l != NULL);
	assert(c != NULL);
	std::list< ObjectCapsule* >::iterator i = (*l).begin();
	if(!l->empty()){
		//if the list is empty we don't need to do all this
		//advance the iterator until
		//	a) our current x-coord is greater than the x-coord we want to insert
		//orb) we reach the end of the array
		while(i != l->end() && ((*i)->o->getX() < c->o->getX())){
			++i;
		}
		if(i == l->end()) --i;
	}
	//add c to l
	l->insert(i, c);
}

void updateEngine(void){
	std::list< ObjectCapsule* > sortedObjects;
	for (auto c = objectList.begin(); c != objectList.end(); )
	{
		c->o->update();
		
		if(c->o->needs_destroy()) {
			delete (*c).o;
			c = objectList.erase(c); // advances the iterator to the element after the one we erased
		} else {
			mergeInsert(&sortedObjects, &(*c)); //sort the object into a list for spatial hashing
			++c; // advance the iterator
		}
	}

	/***************************************************
	 * Right, so here's how the collision algorithm works.
	 * We're given a sorted list of ObjectCapsule* - that's
	 * sortedObjects. For each element therein, we iterate
	 * in two directions, first forward, then backward, in
	 * each direction going until we either
	 *		a)  exceed a reasonable collidable limit on the
	 *			X-axis, that would be 10 units or
	 *		b)  hit the front or back of the list.
	 * This works because the list is sorted on the X-coord
	 * of the GameObject's, so we're reducing the amount of
	 * collisions that we actually have to check, so in a
	 * good case (decent spread of objects across the X axis)
	 * we're doing, eh, around 1/10 of the work that a brute
	 * force algorithm would do, even taking into account
	 * the construction of the sorted list. Of course, in
	 * the WORST case, we're doing MORE work since we're
	 * doing ALL the collision checks that the brute-force
	 * algo would do, PLUS the merge-sort--but the worst
	 * case requires all the GameObject's to be within 10 u
	 * of each other on the X-axis, which should be rare.
	 *
	 ***************************************************/

	for (auto i = sortedObjects.begin(); i != sortedObjects.end(); ++i)
	{ // FOREACH
		//check collision forward in the list
		auto forwardCheck = i;
		while(forwardCheck!=sortedObjects.end() && (**forwardCheck).o->getX() < ((**i).o->getX() + 10)) {
			if((**i).o->needs_destroy() == false && (**forwardCheck).o->needs_destroy() == false)
				(**i).o->collide((**forwardCheck).o);
			++forwardCheck;
		}
	} // end FOREACH

	for (auto i = sortedObjects.rbegin(); i != sortedObjects.rend(); ++i)
	{ // FOREACH
		//check collision backward in the list
		auto backwardCheck = i;
		while(backwardCheck!=sortedObjects.rend() && (**backwardCheck).o->getX() < ((**i).o->getX() + 10)) {
			if((**i).o->needs_destroy() == false && (**backwardCheck).o->needs_destroy() == false)
				(**i).o->collide((**backwardCheck).o);
			++backwardCheck;
		}
	} // end FOREACH
}
void drawObjects(void){
	for (auto c = objectList.begin(); c != objectList.end(); ++c)
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