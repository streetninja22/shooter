#pragma once

#include "Object.h"
#include "Player.h"
#include "GameGraphics.h"



namespace shooter
{
	class Bullet : public VisibleObject
	{
	protected:


	public:
		Bullet(Vector position, Vector size, Vector velocity, Vector acceleration, Worldspace* space, Behavior* behavior, Animation* animation) : VisibleObject(position, size, velocity, acceleration, space, behavior, animation)
		{
			
		}


		~Bullet()
		{

		}

		virtual ObjectType getObjectType() const override { return ObjectType::BULLET; }

		virtual void onCollision(Object* collider) override;


	};




	class Enemy : public VisibleObject
	{
	protected:

		int m_health;
		bool m_invincible;
	
		
	public:
		Enemy(Vector position, Vector size, Vector velocity, Vector acceleration, Worldspace* space, Behavior* behavior, Animation* animation, int health = 100, bool invincible = false) : VisibleObject(position, size, velocity, acceleration, space, behavior, animation), m_health(health), m_invincible(invincible)
		{
		}

		~Enemy()
		{
		}

		void dealDamage(int damage);
		
		virtual void kill();
		
		virtual ObjectType getObjectType() const override {return ObjectType::ENEMY; }
	};
}
