#pragma once

#include <math.h>
#include "SospVector3.h"

class SospParticle
{
private:
	SospVector3		_position;
	SospVector3		_velocity;
	SospVector3		_acceleration;
	float			_lifespan;

public:
	SospParticle();

	void Update();

	void SetPosition(SospVector3 pos);
	SospVector3 GetPosition();

	void SetVelocity(SospVector3 vel);
	SospVector3 GetVelocity();

	void SetAcceleration(SospVector3 accel);
	SospVector3 GetAcceleration();

	bool isDead();
};