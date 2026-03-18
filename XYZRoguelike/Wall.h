#pragma once

#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "GameObject.h"

namespace XYZRoguelike
{
	class Wall
	{
	public:
		Wall(float posX, float posY, int tileSize = 32);
		XYZEngine::GameObject* GetGameObject();
	private:
		XYZEngine::GameObject* gameObject;
	};
}
