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
	if(invincibilitycooldown > 0) {
		--invincibilitycooldown;
		myColor = al_map_rgb_f(smootherStep((MAX_AST_INV-(float)invincibilitycooldown)/MAX_AST_INV),
			                   smootherStep(((float)invincibilitycooldown)/MAX_AST_INV),
							   1);
	}
}

void Asteroid::draw(void){
	al_identity_transform(&myCurrentTransform);
	al_rotate_transform(&myCurrentTransform, direction);
	al_scale_transform(&myCurrentTransform,size*1.2,size*1.2);
	al_translate_transform(&myCurrentTransform,x,y);
	al_use_transform(&myCurrentTransform);
	drawQuad(&myQuad, myColor);
}

void Asteroid::collide(GameObject* o){
	assert(o != NULL);
	//compare SQUARE distances to save on fpu operations
	//if c < sqrt(a^2 + b^2) then c^2 < a^2 + b^2 with the additional bonus that
	//squares are cheaper to compute than square roots
	if(o != this && squareDistance(x,y,o->getX(), o->getY()) < pow(size + o->getS(), 2)
		&& isInvincible() == false)
	{
		destroyme = true;
		//TODO: particle stuff managed in the GameEngine

		addParticle(new Particle(x, y, VEC2(randfloat(-PI, PI), randfloat(0,1)), VEC2(randfloat(-PI, PI), randfloat(-.1,0)), al_map_rgba_f(.5,.1,.1,.5)));
		addParticle(new Particle(x, y, VEC2(randfloat(-PI, PI), randfloat(0,1)), VEC2(randfloat(-PI, PI), randfloat(-.1,0)), al_map_rgba_f(.5,.1,.1,.5)));
		addParticle(new Particle(x, y, VEC2(randfloat(-PI, PI), randfloat(0,1)), VEC2(randfloat(-PI, PI), randfloat(-.1,0)), al_map_rgba_f(.5,.1,.1,.5)));
		//addParticle(new Particle(x, y, VEC2(randfloat(-PI, PI), randfloat(0,1)), VEC2(randfloat(-PI, PI), randfloat(-.1,0)), al_map_rgba_f(.5,.1,.1,.5)));
		//addParticle(new Particle(x, y, VEC2(randfloat(-PI, PI), randfloat(0,1)), VEC2(randfloat(-PI, PI), randfloat(-.1,0)), al_map_rgba_f(.5,.1,.1,.5)));

		//myColor = al_map_rgb_f(1.0,.1,.1);
		if(level < 3) {
			//Smallest asteroid, just die
			//TODO: score stuff managed in the GameEngine
		} else {
			//make smaller asteroids
			add(new Asteroid(x, y, level-1));
			add(new Asteroid(x, y, level-1));
			//add(new Asteroid(x, y, level-1));
			//add(new Asteroid(x, y, level-1));
			//add(new Asteroid(x, y, level-1));
			//add(new Asteroid(x, y, level-1));
			//TODO: score stuff managed in the GameEngine
		}
	}
	return;
}
