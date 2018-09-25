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
	
	shooter::GameSystem* gameSystem = new shooter::GameSystem(mainEventBus, {SCREEN_WIDTH, SCREEN_HEIGHT});
	
	double currentFramerate = 60;
	Uint32 currentDelay = 16;
	
	while (true)
	{
		Uint32 start = getTicks();
		
		mainEventBus->update();
		inputSystem->updateInput();
		gameSystem->update(currentFramerate, currentDelay);
		gfxSystem->update();
		soundSystem->update();
		
		currentDelay = getTicks() - start;
		
		//Make sure the framerate doesn't go too far above 60. Having this here and updating delay seems to keep the framerate more stable than putting it at the end of the frame
		if (currentDelay < MS_PER_FRAME)
		{
			delay(MS_PER_FRAME - currentDelay);
			currentDelay = getTicks() - start;
		}

		currentFramerate = 1000 / (currentDelay ? currentDelay : 1);
	}
	
	//clean up
	
	delete gameSystem;
	delete inputSystem;
	delete soundSystem;
	delete gfxSystem;
	delete mainEventBus;
	
	return 0;
}
