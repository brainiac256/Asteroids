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
	//al_draw_circle(0,0,1,al_map_rgb(.3,.3,.3),0);
}

void Player::update(void)
{
	if(invincibilitycooldown > 0){
		--invincibilitycooldown;
		myColor = al_map_rgb_f(smootherStep((20-(float)invincibilitycooldown)/20),
			                   smootherStep((20-(float)invincibilitycooldown)/20),
							   1);
	}
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
		//myColor = al_map_rgb_f(1,((float)MAX_COOLDOWN-cooldown)/(float)MAX_COOLDOWN,((float)MAX_COOLDOWN-cooldown)/(float)MAX_COOLDOWN);
	}
	else {
		if (isKeyOn(KEY_SPACE)) {
			//add new Bullet object
			add(new Bullet(x, y, VEC2(direction, 12)));
			add(new Bullet(x, y, VEC2(direction-PI/32, 12)));
			add(new Bullet(x, y, VEC2(direction-PI/16, 12)));
			add(new Bullet(x, y, VEC2(direction+PI/32, 12)));
			add(new Bullet(x, y, VEC2(direction+PI/16, 12)));
			//reset cooldown
			cooldown = MAX_COOLDOWN;
		}
	}
}

void Player::collide(GameObject* o){
	assert(o != NULL);
	//std::cout << "\nCollided Player with a " << typeid(*o).name() << std::endl;
	return;
}
