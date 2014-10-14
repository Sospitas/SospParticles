#pragma once

#include <math.h>
#include "SospVector3.h"

class SospParticle
{
private:
	SospVector3 position;
	SospVector3 velocity;

public:
	SospParticle();

	void SetPosition(SospVector3 pos);
	SospVector3 GetPosition();

	void SetVelocity(SospVector3 vel);
	SospVector3 GetVelocity();
};