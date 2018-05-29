#include "framework/InputSystem.h"
#include "framework/GraphicsSystem.h"
#include "framework/GraphicsEvents.h"
#include "framework/SoundSystem.h"
#include "framework/soundevents.h"
#include "framework/functions.h"

#include "GameSystem.h"


#include <iostream>


//TODO: get these values out of macros, perhaps create an options file or something

//default 480p
#define SCREEN_WIDTH 620
#define SCREEN_HEIGHT 480

#define PROJECT_NAME "Shooter Game"
#define MS_PER_FRAME 16



int main(int argc, char** argv)
{
	//initialize core systems
	evnt::EventBus* mainEventBus = new evnt::EventBus();
	
	//around the middle of a 1080p monitor sounds about right for placement
	gfx::GraphicsSystem* gfxSystem = new gfx::GraphicsSystem(mainEventBus, PROJECT_NAME, 1920/2, 1080/2, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	sound::SoundSystem* soundSystem = new sound::SoundSystem(mainEventBus);
	
	inpt::InputSystem* inputSystem = new inpt::InputSystem(mainEventBus);
	
	shooter::GameSystem* gameSystem = new shooter::GameSystem(mainEventBus);
	
	
	while (true)
	{
		long start = getTicks();
		
		mainEventBus->update();
		inputSystem->updateInput();
		gameSystem->update();
		gfxSystem->update();
		soundSystem->update();
		
		long time = start + MS_PER_FRAME - getTicks();
		
		delay(time > 0 ? time : 0);
	}
	
	//clean up
	
	delete gameSystem;
	delete inputSystem;
	delete soundSystem;
	delete gfxSystem;
	delete mainEventBus;
	
	return 0;
}
