#pragma once

#include "Object.h"
#include "Player.h"



namespace shooter
{
	class Bullet : public Object
	{
	protected:


	public:
		Bullet(Vector position, Vector size, Vector velocity, Vector acceleration, Worldspace* space, Behavior* behavior) : Object(position, size, velocity, acceleration, space, behavior)
		{

		}


		~Bullet()
		{

		}

		virtual ObjectType getObjectType() const override { return ObjectType::BULLET; }

		virtual void onCollision(Object* collider) override;


	};




	class Enemy : public Object
	{
	protected:

		int m_health;

	public:
		Enemy(Vector position, Vector size, Vector velocity, Vector acceleration, Worldspace* space, Behavior* behavior) : Object(position, size, velocity, acceleration, space, behavior)
		{
		}

		~Enemy()
		{
		}


	};
}