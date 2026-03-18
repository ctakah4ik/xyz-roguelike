#include "Floor.h"
#include <ResourceSystem.h>
#include <TransformComponent.h>

namespace XYZRoguelike
{
	Floor::Floor(float posX, float posY, int tileSize)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Floor");

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("floor", 0));
		renderer->SetPixelSize(tileSize, tileSize);

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(posX, posY);
	}

	XYZEngine::GameObject* Floor::GetGameObject()
	{
		return gameObject;
	}
}
