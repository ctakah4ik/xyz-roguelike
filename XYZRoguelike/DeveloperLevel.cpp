#include "DeveloperLevel.h"
#include <ResourceSystem.h>
#include <TransformComponent.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	void DeveloperLevel::Start()
	{
		// Generate level: floor and walls (floor created first so it renders behind)
		levelGenerator = std::make_shared<LevelGenerator>();
		levelGenerator->Generate(0.f, 0.f, 20, 20, 32);

		// Create player at center
		player = std::make_shared<Player>();

		// Create enemy nearby but outside detection radius
		auto playerTransform = player->GetGameObject()->GetComponent<TransformComponent>();
		enemy = std::make_shared<Enemy>(playerTransform);
		enemy->GetGameObject()->GetComponent<TransformComponent>()->SetWorldPosition(200.f, 200.f);

		// Play background music
		ResourceSystem::Instance()->PlayMusic("Resources/Sounds/main.wav", true);
		ResourceSystem::Instance()->SetMusicVolume(50.f);
	}

	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}

	void DeveloperLevel::Stop()
	{
		ResourceSystem::Instance()->StopMusic();
		GameWorld::Instance()->Clear();
	}
}
