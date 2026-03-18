#pragma once

#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "ChaseComponent.h"
#include "GameObject.h"

namespace XYZRoguelike
{
	class Enemy
	{
	public:
		Enemy(XYZEngine::TransformComponent* target);
		XYZEngine::GameObject* GetGameObject();
	private:
		XYZEngine::GameObject* gameObject;
	};
}
