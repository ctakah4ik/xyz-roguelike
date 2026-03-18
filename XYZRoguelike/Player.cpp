#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <Logger.h>

namespace XYZRoguelike
{
	Player::Player()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player");
		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		playerRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("player", 0));
		playerRenderer->SetPixelSize(32, 42);

		auto playerCamera = gameObject->AddComponent<XYZEngine::CameraComponent>();
		playerCamera->SetWindow(&XYZEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto movement = gameObject->AddComponent<XYZEngine::MovementComponent>();
		movement->SetSpeed(200.f);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto health = gameObject->AddComponent<XYZEngine::HealthComponent>();
		health->SetMaxHealth(100.f);
		health->SetArmor(0.1f);

		auto attack = gameObject->AddComponent<XYZEngine::AttackComponent>();
		attack->SetDamage(25.f);
		attack->SetAttackCooldown(0.5f);
		attack->SetRequireKey(sf::Keyboard::Space);
		attack->SetAttackRange(60.f);

		XYZEngine::Logger::Instance()->Info("Player created with 100 HP, 10% armor, 25 damage.");
	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}