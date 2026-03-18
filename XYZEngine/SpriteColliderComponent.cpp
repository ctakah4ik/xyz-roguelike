#include "pch.h"
#include "SpriteColliderComponent.h"
#include "Logger.h"

namespace XYZEngine
{
	SpriteColliderComponent::SpriteColliderComponent(GameObject* gameObject) : ColliderComponent(gameObject)
	{
		auto spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
		if (spriteRenderer == nullptr)
		{
			Logger::Instance()->Error("SpriteColliderComponent requires SpriteRendererComponent on " + gameObject->GetName());
			gameObject->RemoveComponent(this);
			return;
		}

		sprite = gameObject->GetComponent<SpriteRendererComponent>()->GetSprite();
		PhysicsSystem::Instance()->Subscribe(this);
	}
	SpriteColliderComponent::~SpriteColliderComponent()
	{
		if (&bounds != nullptr)
		{
			std::destroy_at(&bounds);
		}
		PhysicsSystem::Instance()->Unsubscribe(this);
	}

	void SpriteColliderComponent::Update(float deltaTime)
	{
		bounds = sprite->getGlobalBounds();
	}
	void SpriteColliderComponent::Render()
	{
		sf::RectangleShape rectangle(sf::Vector2f(bounds.width, bounds.height));
		rectangle.setPosition(bounds.left, bounds.top);
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setOutlineColor(sf::Color::White);
		rectangle.setOutlineThickness(1);

		RenderSystem::Instance()->Render(rectangle);
	}
}