#ifndef BULLET_H
#define BULLET_H
#include "gameengine.h"
class Bullet :
	public GameObject
{
public:
	Bullet(float nx, float ny, VEC2 v){
		x = nx;
		y = ny;
		velocity = v;
		direction = v.angle;
		myQuad = QUAD(-1,0,
			          0,1,
					  1,0,
					  0,-1);
		destroyme = false;
		size = 2;
		life = 90;
		invincibilitycooldown = 2;
		myColor = al_map_rgb_f(0,1,1);
	}
	~Bullet(void);

	virtual void draw(void) override;
	virtual void update(void) override;
	virtual void collide(GameObject* o) override;
private:
	ALLEGRO_TRANSFORM myCurrentTransform;
	ALLEGRO_COLOR myColor;
	QUAD myQuad;
	float direction;
	VEC2 velocity;
	int life;
};

#endif //ndef BULLET_H
