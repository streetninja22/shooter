#include "Enemy.h"


namespace shooter
{

	void Bullet::onCollision(Object* collider)
	{
		switch (collider->getObjectType())
		{
		case ObjectType::PLAYER:
		{
			dynamic_cast<Player*>(collider)->kill();
		}
		}
	}

	
	void Enemy::dealDamage(int damage)
	{
		if (!m_invincible)
		{
			m_health -= damage;
			
			if (m_health <= 0)
			{
				kill();
			}
		}
	}
	
	
	void Enemy::kill()
	{
		destroy();
	}
}
