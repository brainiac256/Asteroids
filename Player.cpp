#include "Player.h"

Player::~Player(void)
{
}

void Player::draw(void)
{
	al_identity_transform(&myCurrentTransform);
	al_rotate_transform(&myCurrentTransform, direction);
	al_scale_transform(&myCurrentTransform,size,size);
	al_translate_transform(&myCurrentTransform,x,y);
	al_use_transform(&myCurrentTransform);
	drawTriangle(&player_tri, this->myColor);
}

void Player::update(void)
{
	//movement stuffs
	if(isKeyOn(KEY_LEFT)){
		direction -= PI/32;
	} else if (isKeyOn(KEY_RIGHT)){
		direction += PI/32;
	}
	if(isKeyOn(KEY_UP)){
		addVEC2(&velocity, new VEC2(direction, .1));
		if(velocity.magnitude > 5) velocity.magnitude = 5;
	}
	if(isKeyOn(KEY_DOWN)){
		if(velocity.magnitude > .5) velocity.magnitude *= .95;
		else if(velocity.magnitude > 0) velocity.magnitude -= .05;
		else velocity.magnitude = 0;
	}
	x += cos(velocity.angle)*(velocity.magnitude);
	y += sin(velocity.angle)*(velocity.magnitude);
	if(x > 640) x-=640;
	if(x < 0)   x+=640;
	if(y > 480) y-=480;
	if(y < 0)   y+=480;

	//firing stuffs
	if(cooldown > 0) {
		--cooldown;
		myColor = al_map_rgb_f(1,((float)MAX_COOLDOWN-cooldown)/(float)MAX_COOLDOWN,((float)MAX_COOLDOWN-cooldown)/(float)MAX_COOLDOWN);
	}
	else {
		if (isKeyOn(KEY_SPACE)) {
		//add new Bullet object

		//reset cooldown
		cooldown = MAX_COOLDOWN;
		}
		myColor = al_map_rgb_f(1,1,1);
	}
}
