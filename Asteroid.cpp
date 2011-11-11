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
}