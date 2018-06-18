#include "Enemy.h"


namespace shooter
{

	void Bullet::onCollision(Object* collider)
	{
		switch (collider->getObjectType())
		{
		case ObjectType::PLAYER:
		{
			collider->destroy();
		}
		}
	}

}