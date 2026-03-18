#include "pch.h"
#include "Component.h"
#include "Logger.h"

namespace XYZEngine
{
	Component::Component(GameObject* gameObject) : gameObject(gameObject) {}
	Component::~Component()
	{
		Logger::Instance()->Debug("Component destroyed.");
	}
	GameObject* Component::GetGameObject()
	{
		return gameObject;
	}
}