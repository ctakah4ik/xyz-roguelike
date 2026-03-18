#include "Enemy.h"
#include <ResourceSystem.h>

namespace XYZRoguelike
{
	Enemy::Enemy(XYZEngine::TransformComponent* target)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("enemy"));
		renderer->SetPixelSize(32, 32);

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto chase = gameObject->AddComponent<XYZEngine::ChaseComponent>();
		chase->SetTarget(target);
		chase->SetDetectionRadius(300.f);
		chase->SetSpeed(120.f);
	}

	XYZEngine::GameObject* Enemy::GetGameObject()
	{
		return gameObject;
	}
}
