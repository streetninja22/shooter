#pragma once

#include "Object.h"
#include "GameGraphics.h"
#include <bitset>
#include "Enemy.h"

namespace shooter
{

	class Player : public VisibleObject
	{


	public:
		Player(Vector position, Vector size, Vector velocity, Vector acceleration, Worldspace* space, Behavior* behavior, Animation* animation) : VisibleObject(position, size, velocity, acceleration, space, behavior, animation)
		{
		}

		~Player()
		{
		}

		virtual void onCollision(Object* collider) override;

		virtual ObjectType getObjectType() const override { return ObjectType::PLAYER; }
		
		virtual void kill();

		virtual void destroy() override;

	};
	
	
	class PlayerShot : public VisibleObject
	{
		int m_damage;
		
	public:
		PlayerShot(int damage, Vector position, Vector size, Vector velocity = {0, 0}, Vector acceleration = {0, 0}, Worldspace* associatedSpace = nullptr, Behavior* behavior = nullptr, Animation* animation = nullptr) : VisibleObject(position, size, velocity, acceleration, associatedSpace, behavior, animation), m_damage(damage)
		{
			
		}
		
		virtual void onCollision(Object* collider) override;
		
		virtual ObjectType getObjectType() const override { return ObjectType::SHOT; }
	};

	
	class PlayerFireBehavior : public Behavior
	{
	public:
		PlayerFireBehavior() : Behavior()
		{
			
		}
		
	};
	
	
	

	class ReimuFireBehavior : public PlayerFireBehavior
	{
		
		Animation* m_basicBulletAnim;
		
		//negative because y 0 is at top of screen
		double m_bulletSpeed = -15;
		uint32_t m_fireRate = 10;
		double m_shotSize = 16;
		int m_basicBulletDamage = 10;
		
	public:
		ReimuFireBehavior() : PlayerFireBehavior(), m_basicBulletAnim(nullptr)
		{
			
		}
		
		~ReimuFireBehavior();
		
		void loadAnimation(Object* parent);
		
		PlayerShot* createBullet(Object* parent);
		
		virtual void stepBehavior(Object* parent, uint32_t timestep) override;
	};
	
	
	
	
	
	class PlayerBehavior : public Behavior
	{
		std::bitset<5> m_currentActions;

		double m_moveSpeed;
		
		PlayerFireBehavior* m_fireBehavior;

	public:

		enum PlayerAction
		{
			ACTION_MOVE_FORWARD,
			ACTION_MOVE_BACKWARD,
			ACTION_MOVE_LEFT,
			ACTION_MOVE_RIGHT,
			ACTION_SHOOT,
			ACTION_BOMB,
		};



		PlayerBehavior(double moveSpeed, PlayerFireBehavior* fireBehavior) : Behavior(), m_moveSpeed(moveSpeed), m_fireBehavior(fireBehavior)
		{
			
		}

		~PlayerBehavior()
		{
		}


		double getMoveSpeed()				{ return m_moveSpeed; }
		void setMoveSpeed(double speed)		{ m_moveSpeed = speed; }

		
		virtual void stepBehavior(Object* parent, uint32_t timestep) override;

		void setActionStatus(PlayerAction action, bool state);

		bool getActionStatus(PlayerAction action);

	};

}
