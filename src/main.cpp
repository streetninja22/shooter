#include <iostream>
#include <boost/filesystem.hpp>
#include "framework/assets.h"
#include "framework/InputSystem.h"
#include "framework/Event.h"
#include "framework/includeSDL.h"
#include "framework/GraphicsSystem.h"
#include "framework/GraphicsEvents.h"
#include "framework/SoundSystem.h"
#include "framework/soundevents.h"


//NOTE: in its current state, main.cpp is entirely used for testing



class GameSystem : public System
{

	sound::Chunk* m_soundEffect;
	
public:
	GameSystem(evnt::EventBus* bus) : System(bus)
	{
		sound::LoadChunkReturnType* returned = dynamic_cast<sound::LoadChunkReturnType*>(bus->fireEventNow(new sound::LoadChunkEvent(file::getResourceDirectory("sound/death.mp3"))));
		
		m_soundEffect = returned->getChunk();
	}
	
	
	
	EventReturnType* eventFired(Event* event) override
	{
		using namespace inpt;
		if (event->getEventType() == EventType::INPUT)
		{
			InputEvent* inputEvent = dynamic_cast<InputEvent*>(event);
			if (inputEvent->getInputType() == InputEventType::KEYBOARD)
			{
				KeyboardEvent* keyEvent = dynamic_cast<KeyboardEvent*>(inputEvent);
				if (keyEvent->getType() == KeyEventType::KEYDOWN)
				{
					switch (keyEvent->getKeyCode())
					{
						case KeyCode::KEYCODE_SPACE:
						{
							addEvent(new sound::ToggleMusicEvent());
							
							break;
						}
							
						case KeyCode::KEYCODE_P:
						{
							addEvent(new sound::PlayChunkEvent(m_soundEffect));
							
							break;
						}
					}
				}
			}
		}
		return nullptr;
	}
		
};




int main(int argc, char** argv)
{
	evnt::EventBus* bus = new evnt::EventBus();
	
	inpt::InputSystem input(bus);

	gfx::GraphicsSystem graphics(bus, "Test", 0, 80, 640, 480);
	
	sound::SoundSystem sound(bus);

	evnt::EventReturnType* returned = bus->fireEventNow(new gfx::LoadTextureEvent(file::getResourceDirectory("gfx/cryofreeze.jpg")));

	gfx::Texture* texture = static_cast<gfx::LoadTextureReturnType*>(returned)->getTexture();
	
	GameSystem gameSystem(bus);
	
	
	sound::Music* music = static_cast<sound::LoadMusicReturnType*>(bus->fireEventNow(new sound::LoadMusicEvent(file::getResourceDirectory("sound/music.wav"))))->getMusic();
	
	bus->addEvent(new sound::PlayMusicEvent(music));
	
	while (true)
	{
		bus->update();
		
		input.updateInput();
		
		graphics.update();

		gfx::RenderImageEvent* event = new gfx::RenderImageEvent(texture, NULL, NULL);

		bus->addEvent(event);
		
	}
	
	return 0;
}
