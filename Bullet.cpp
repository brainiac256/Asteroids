#include "Bullet.h"

Bullet::~Bullet(void)
{
}

void Bullet::update(void){
	//add velocity to position
	x += cos(velocity.angle)*(velocity.magnitude);
	y += sin(velocity.angle)*(velocity.magnitude);
	if(x > 640) x-=640;
	if(x < 0)   x+=640;
	if(y > 480) y-=480;
	if(y < 0)   y+=480;
	--life;
	if(life <= 0) destroyme = true;
	if(invincibilitycooldown > 0){
		--invincibilitycooldown;
		myColor = al_map_rgb_f(0,
			                   smootherStep((20-(float)invincibilitycooldown)/20),
							   1);
	}
}

void Bullet::draw(void){
	al_identity_transform(&myCurrentTransform);
	al_rotate_transform(&myCurrentTransform, direction);
	al_scale_transform(&myCurrentTransform,size,size);
	al_translate_transform(&myCurrentTransform,x,y);
	al_use_transform(&myCurrentTransform);
	drawQuad(&myQuad, myColor);
	//al_draw_circle(0,0,1,al_map_rgb(.3,.3,.3),0);
}

void Bullet::collide(GameObject* o){
	assert(o != NULL);
	//std::cout << "\nCollided a Bullet with a " << typeid(*o).name() << std::endl;
	if(o != this && squareDistance(x,y,o->getX(), o->getY()) < pow(size + o->getS(), 2))
	{
		life = 1; // set life to 1 so it'll be destroyed on the next tick
	}
	return;
}
