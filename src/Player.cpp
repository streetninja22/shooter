#include "Player.h"


//testing
#include <iostream>

namespace shooter
{


	void Player::onCollision(Object* collider)
	{
		//TODO this

		switch (collider->getObjectType())
		{
		case ObjectType::BULLET:
		{
		//	collider->destroy();
			break;
		}
		}

	}


	void Player::destroy()
	{
		//std::cout << "Object destroyed!\n";
	}


	void PlayerBehavior::stepBehavior(uint32_t timestep)
	{
		Vector playerVel = { 0, 0 };

		if (getActionStatus(ACTION_MOVE_FORWARD))
			playerVel.y = -m_moveSpeed;
		else if (getActionStatus(ACTION_MOVE_BACKWARD))
			playerVel.y = m_moveSpeed;
		else
			playerVel.y = 0;

		if (getActionStatus(ACTION_MOVE_RIGHT))
			playerVel.x = m_moveSpeed;
		else if (getActionStatus(ACTION_MOVE_LEFT))
			playerVel.x = -m_moveSpeed;
		else
			playerVel.x = 0;

		m_parentObject->setVelocity(playerVel);
	}

	void PlayerBehavior::setActionStatus(PlayerAction action, bool state)
	{
		m_currentActions.set(action, state);
	}

	bool PlayerBehavior::getActionStatus(PlayerAction action)
	{
		return m_currentActions[action];
	}

}
