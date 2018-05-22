#include "GameSystem.h"


#include <iostream>

namespace shooter
{
	
	Object obj1 {{0, 3}, {5, 3}};
	
	Object obj2 {{3, 0}, {5, 3}};
	
	
	void GameSystem::update()
	{
		//Currently, this is a test function
		
		if (checkCollision(obj1, obj2))
			std::cout << "Collision detected!\n";
		
		
		
	}
	
	
	
	
}
