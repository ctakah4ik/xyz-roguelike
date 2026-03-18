#pragma once

#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "GameObject.h"

namespace XYZRoguelike
{
	class Floor
	{
	public:
		Floor(float posX, float posY, int tileSize = 32);
		XYZEngine::GameObject* GetGameObject();
	private:
		XYZEngine::GameObject* gameObject;
	};
}
