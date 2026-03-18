#include "pch.h"
#include "Engine.h"
#include "GameWorld.h"
#include "RenderSystem.h"
#include "Logger.h"

namespace XYZEngine
{
	Engine* Engine::Instance()
	{
		static Engine instance;
		return &instance;
	}

	Engine::Engine()
	{
		unsigned int seed = (unsigned int)time(nullptr);
		srand(seed);
	}

	void Engine::Run()
	{
		Logger::Instance()->Info("Engine started. Entering main loop.");

		sf::Clock gameClock;
		sf::Event event;

		while (RenderSystem::Instance()->GetMainWindow().isOpen())
		{
			sf::Time dt = gameClock.restart();
			float deltaTime = dt.asSeconds();

			while (RenderSystem::Instance()->GetMainWindow().pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					Logger::Instance()->Info("Window close event received.");
					RenderSystem::Instance()->GetMainWindow().close();
				}
			}

			if (!RenderSystem::Instance()->GetMainWindow().isOpen())
			{
				break;
			}

			RenderSystem::Instance()->GetMainWindow().clear();

			GameWorld::Instance()->Update(deltaTime);
			GameWorld::Instance()->FixedUpdate(deltaTime);
			GameWorld::Instance()->Render();
			GameWorld::Instance()->LateUpdate();

			RenderSystem::Instance()->GetMainWindow().display();
		}

		Logger::Instance()->Info("Engine main loop ended.");
	}
}
