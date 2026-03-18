#include "Wall.h"
#include <ResourceSystem.h>
#include <TransformComponent.h>

namespace XYZRoguelike
{
	Wall::Wall(float posX, float posY, int tileSize)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Wall");

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("wall", 0));
		renderer->SetPixelSize(tileSize, tileSize);

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		body->SetKinematic(true);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(posX, posY);
	}

	XYZEngine::GameObject* Wall::GetGameObject()
	{
		return gameObject;
	}
}
