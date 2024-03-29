#ifndef ASTEROID_H
#define ASTEROID_H
#include "gameengine.h"
class Asteroid :
	public GameObject
{
	static const int MAX_AST_INV = 60;
public:
	Asteroid(float nx, float ny, float d, VEC2 v, ALLEGRO_COLOR c,
		     QUAD q, int l, int s, float r){
		isBullet = false;
		al_identity_transform(&myCurrentTransform);
		x = nx;
		y = ny;
		direction = d;
		velocity  = v;
		myColor = c;
		myQuad = q;
		life = l;
		size = s;
		rotation = r;
		destroyme = false;
		invincibilitycooldown = MAX_AST_INV;
	}
	Asteroid(void){
		isBullet = false;
		//completely random asteroid
		al_identity_transform(&myCurrentTransform);
		x = randint(0,640);
		y = randint(0,480);
		level = randint(2,4);
		life = 2*level;
		size = 4*level;
		direction = randfloat(0, PI*2);
		velocity  = VEC2(randfloat(0,PI*2),randfloat(0,3));
		myColor = al_map_rgb_f(randfloat(0.5,1), randfloat(0.5,1), randfloat(0.5,1));
		myQuad = QUAD(randfloat(-1,0),randfloat(0,1),
			          randfloat(0,1),randfloat(0,1),
					  randfloat(0,1),randfloat(-1,0),
					  randfloat(-1,0),randfloat(-1,0));
		rotation = randfloat(-PI/24,PI/24);
		destroyme = false;
		invincibilitycooldown = 20;
	}
	Asteroid(float nx, float ny, int l){
		assert(l > 1);
		isBullet = false;
		//partially random asteroid
		al_identity_transform(&myCurrentTransform);
		x = nx;
		y = ny;
		level = l;
		life = 2*level;
		size = 4*level;
		//randomize components
		direction = randfloat(0, PI*2);
		velocity  = VEC2(randfloat(0,PI*2),randfloat(0,3));
		myColor = al_map_rgb_f(randfloat(0.5,1), randfloat(0.5,1), randfloat(0.5,1));
		myQuad = QUAD(randfloat(-1,0),randfloat(0,1),
			          randfloat(0,1),randfloat(0,1),
					  randfloat(0,1),randfloat(-1,0),
					  randfloat(-1,0),randfloat(-1,0));
		rotation = randfloat(-PI/24,PI/24);
		destroyme = false;
		invincibilitycooldown = 20;
	}
	~Asteroid(void);

	virtual void draw(void) override;
	virtual void update(void) override;
	virtual void collide(GameObject* o) override;
private:
	ALLEGRO_TRANSFORM myCurrentTransform;
	ALLEGRO_COLOR myColor;
	QUAD myQuad;
	float direction;
	VEC2 velocity;
	int life,level;
	float rotation;
};

#endif //ndef ASTEROID_H
