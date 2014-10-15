
#include "SospParticle.h"

SospParticle::SospParticle()
{
	SospVector3 pos;
	pos.RandomVector3(-100, 100);
	SospVector3 vel;
	vel.RandomVector3(-100, 100);
}

void SospParticle::Update()
{
	_velocity.Add(_acceleration);
	_position.Add(_velocity);
	_lifespan--;
}

void SospParticle::SetPosition(SospVector3 pos)
{
	_position = pos;
}

SospVector3 SospParticle::GetPosition()
{
	return _position;
}

void SospParticle::SetVelocity(SospVector3 vel)
{
	_velocity = vel;
}

SospVector3 SospParticle::GetVelocity()
{
	return _velocity;
}

void SospParticle::SetAcceleration(SospVector3 accel)
{
	_acceleration = accel;
}

SospVector3 SospParticle::GetAcceleration()
{
	return _acceleration;
}

bool SospParticle::isDead()
{
	return _lifespan > 0 ? true : false;
}