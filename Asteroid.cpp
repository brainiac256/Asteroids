#include "Asteroid.h"

Asteroid::~Asteroid(void)
{
}

void Asteroid::update(void){
	//add velocity to position
	x += cos(velocity.angle)*(velocity.magnitude);
	y += sin(velocity.angle)*(velocity.magnitude);
	if(x > 640) x-=640;
	if(x < 0)   x+=640;
	if(y > 480) y-=480;
	if(y < 0)   y+=480;
	//rotate slowly
	direction += rotation;
}

void Asteroid::draw(void){
	al_identity_transform(&myCurrentTransform);
	al_rotate_transform(&myCurrentTransform, direction);
	al_scale_transform(&myCurrentTransform,size,size);
	al_translate_transform(&myCurrentTransform,x,y);
	al_use_transform(&myCurrentTransform);
	drawQuad(&myQuad, myColor);
	//al_draw_circle(0,0,1,al_map_rgb(.3,.3,.3),0);
}

void Asteroid::collide(GameObject* o){
	assert(o != NULL);
	//compare SQUARE distances to save on fpu operations
	//if c = sqrt(a^2 + b^2) then c^2 = a^2 + b^2 with the additional bonus that
	//squares are cheaper to compute than square roots
	if(o != this && squareDistance(x,y,o->getX(), o->getY()) < pow(size + o->getS(), 2))
		myColor = al_map_rgb_f(1.0,.1,.1);
	//std::cout << "\nCollided an Asteroid with a " << typeid(*o).name() << std::endl;
	return;
}