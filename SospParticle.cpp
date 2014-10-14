
#include "SospParticle.h"

SospParticle::SospParticle()
{
	SospVector3 pos;
	pos.RandomVector3(-100, 100);
	SospVector3 vel;
	vel.RandomVector3(-100, 100);
}