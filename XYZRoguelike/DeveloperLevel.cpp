#include "DeveloperLevel.h"
#include <ResourceSystem.h>
#include <TransformComponent.h>
#include <Logger.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	void DeveloperLevel::Start()
	{
		Logger::Instance()->Info("DeveloperLevel: Starting level...");

		// Generate level: floor and walls (floor created first so it renders behind)
		levelGenerator = std::make_shared<LevelGenerator>();
		levelGenerator->Generate(0.f, 0.f, 30, 30, 32);
		Logger::Instance()->Info("DeveloperLevel: Level generated (30x30 grid, tile size 32).");

		// Create player at center
		player = std::make_shared<Player>();
		Logger::Instance()->Info("DeveloperLevel: Player created at origin.");

		// Create enemy outside detection radius (300), distance ~424
		auto playerTransform = player->GetGameObject()->GetComponent<TransformComponent>();
		enemy = std::make_shared<Enemy>(playerTransform);
		enemy->GetGameObject()->GetComponent<TransformComponent>()->SetWorldPosition(300.f, 300.f);
		Logger::Instance()->Info("DeveloperLevel: Enemy spawned at (300, 300).");

		// Play background music
		ResourceSystem::Instance()->PlayMusic("Resources/Sounds/main.wav", true);
		ResourceSystem::Instance()->SetMusicVolume(50.f);

		Logger::Instance()->Info("DeveloperLevel: Level started successfully.");
	}

	void DeveloperLevel::Restart()
	{
		Logger::Instance()->Info("DeveloperLevel: Restarting...");
		Stop();
		Start();
	}

	void DeveloperLevel::Stop()
	{
		Logger::Instance()->Info("DeveloperLevel: Stopping...");
		ResourceSystem::Instance()->StopMusic();
		GameWorld::Instance()->Clear();
	}
}
