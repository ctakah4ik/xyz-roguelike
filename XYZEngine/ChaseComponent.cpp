#include "pch.h"
#include "ChaseComponent.h"

namespace XYZEngine
{
	ChaseComponent::ChaseComponent(GameObject* gameObject) : Component(gameObject)
	{
		transform = gameObject->GetComponent<TransformComponent>();
		body = gameObject->GetComponent<RigidbodyComponent>();
	}

	void ChaseComponent::Update(float deltaTime)
	{
		if (target == nullptr || body == nullptr || transform == nullptr)
		{
			return;
		}

		Vector2Df myPos = transform->GetWorldPosition();
		Vector2Df targetPos = target->GetWorldPosition();
		Vector2Df diff = targetPos - myPos;
		float distance = diff.GetLength();

		if (distance <= detectionRadius && distance > 0.001f)
		{
			Vector2Df direction = { diff.x / distance, diff.y / distance };
			body->SetLinearVelocity({ direction.x * speed * deltaTime, direction.y * speed * deltaTime });
		}
		else
		{
			body->SetLinearVelocity({ 0.f, 0.f });
		}
	}

	void ChaseComponent::Render()
	{
	}

	void ChaseComponent::SetTarget(TransformComponent* newTarget)
	{
		target = newTarget;
	}

	void ChaseComponent::SetDetectionRadius(float newRadius)
	{
		detectionRadius = newRadius;
	}

	void ChaseComponent::SetSpeed(float newSpeed)
	{
		speed = newSpeed;
	}
}
