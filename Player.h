#ifndef PLAYER_H
#define PLAYER_H
#include "gameengine.h"
//#include <allegro5\allegro_primitives.h>
#include <allegro5\color.h>

class Player :
	public GameObject
{
	static const int MAX_COOLDOWN = 20;
public:
	Player(void){
		al_identity_transform(&myCurrentTransform);
		player_tri = TRIANGLE(2.0,0.0,-1.0,-1.0,-1.0,1.0);
		myColor = al_map_rgb_f(1.0,1.0,1.0);
		x=320;
		y=240;
		size = 5;
		direction=0;
		velocity = VEC2(0.0,0.0);
		cooldown=0;
	};
	~Player(void);

	virtual void draw(void) override;
	virtual void update(void) override;
private:
	ALLEGRO_TRANSFORM myCurrentTransform;
	ALLEGRO_COLOR myColor;
	TRIANGLE player_tri;
	float direction;
	VEC2 velocity;
	int cooldown;
};

#endif PLAYER_H