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
			collider->destroy();
			break;
		}
		}

	}


	void Player::destroy()
	{
		
	}
	
	void Player::kill()
	{
		
	}


	void PlayerBehavior::stepBehavior(Object* parent, uint32_t timestep)
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
		
		if (getActionStatus(ACTION_SHOOT))
		{
			m_fireBehavior->update(parent);
		}
		else
			m_fireBehavior->resetClock();

		parent->setVelocity(playerVel);
	}

	void PlayerBehavior::setActionStatus(PlayerAction action, bool state)
	{
		m_currentActions.set(action, state);
	}

	bool PlayerBehavior::getActionStatus(PlayerAction action)
	{
		return m_currentActions[action];
	}
	
	
	
	
	
	void PlayerShot::onCollision(Object* collider)
	{
		if (collider->getObjectType() == ObjectType::ENEMY)
		{
			Enemy* hitEnemy = dynamic_cast<Enemy*>(collider);
			
			hitEnemy->dealDamage(m_damage);
			
			destroy();
		}
	}
	
	
	
	
	
	ReimuFireBehavior::~ReimuFireBehavior()
	{
		delete m_basicBulletAnim;
	}
	
	void ReimuFireBehavior::loadAnimation(Object* parent)
	{
		m_basicBulletAnim = getAnimationFromEventReturn(parent->fireEventNow(new LoadAnimationEvent(AnimationId::ANIMATION_BULLET_SMALL)));
	}
	
	PlayerShot* ReimuFireBehavior::createBullet(Object* parent)
	{
		PlayerShot* shot;
		
		Vector position = parent->getCenter() - m_shotSize / 2;
		
		shot = new PlayerShot(m_basicBulletDamage, position, {m_shotSize, m_shotSize}, {0, m_bulletSpeed}, {0, 0}, nullptr, nullptr, m_basicBulletAnim);
		
		return shot;
	}
	
	void ReimuFireBehavior::stepBehavior(Object* parent, uint32_t timestep)
	{
		
		if (m_basicBulletAnim == nullptr)
			loadAnimation(parent);
		
		if (!(m_clock % m_fireRate))
		{
			PlayerShot* shot = createBullet(parent);
			
			parent->getAssociatedSpace()->add(shot);
		}
	}

}
