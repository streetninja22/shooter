#pragma once

#include "Object.h"
#include "GameGraphics.h"
#include <bitset>

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

		virtual void destroy() override;

	};


	class PlayerBehavior : public Behavior
	{
		std::bitset<5> m_currentActions;

		double m_moveSpeed;


	public:

		enum PlayerAction
		{
			ACTION_MOVE_FORWARD,
			ACTION_MOVE_BACKWARD,
			ACTION_MOVE_LEFT,
			ACTION_MOVE_RIGHT,
			ACTION_SHOOT,
		};



		PlayerBehavior(Object* parentObject, double moveSpeed) : Behavior(parentObject), m_moveSpeed(moveSpeed)
		{
		}

		~PlayerBehavior()
		{
		}


		double getMoveSpeed()				{ return m_moveSpeed; }
		void setMoveSpeed(double speed)		{ m_moveSpeed = speed; }

		
		virtual void stepBehavior(uint32_t timestep) override;

		void setActionStatus(PlayerAction action, bool state);

		bool getActionStatus(PlayerAction action);

	};

}
