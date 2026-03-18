// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "Matrix2D.h"
#include "Logger.h"

using namespace XYZRoguelike;

int main()
{
	// Initialize logger first
	XYZEngine::Logger::Instance()->Init("game.log");
	XYZEngine::Logger::Instance()->Info("=== XYZRoguelike starting ===");

	try
	{
		XYZEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "XYZRoguelike"));
		XYZEngine::Logger::Instance()->Info("Window created: 1280x720");

		// Load texture maps from sprite sheets (smooth=false for pixel art)
		XYZEngine::ResourceSystem::Instance()->LoadTextureMap("player", "Resources/Textures/Player.png", { 48, 63 }, 9, false);
		XYZEngine::ResourceSystem::Instance()->LoadTextureMap("wall", "Resources/Textures/Wall.png", { 64, 64 }, 3, false);
		XYZEngine::ResourceSystem::Instance()->LoadTextureMap("floor", "Resources/Textures/Floor.png", { 16, 16 }, 49, false);

		// Enemy uses a generated red texture (no dedicated sprite)
		XYZEngine::ResourceSystem::Instance()->CreateColorTexture("enemy", 32, 32, sf::Color::Red);

		auto developerLevel = std::make_shared<DeveloperLevel>();
		developerLevel->Start();

		XYZEngine::Engine::Instance()->Run();
	}
	catch (const XYZEngine::EngineException& e)
	{
		XYZEngine::Logger::Instance()->Fatal(std::string("Engine exception: ") + e.what());
		return 1;
	}
	catch (const std::exception& e)
	{
		XYZEngine::Logger::Instance()->Fatal(std::string("Unhandled exception: ") + e.what());
		return 1;
	}

	XYZEngine::Logger::Instance()->Info("=== XYZRoguelike shutting down ===");
	XYZEngine::Logger::Instance()->Shutdown();

	return 0;
}
