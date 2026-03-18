#include "pch.h"
#include "ChaseComponent.h"
#include "Logger.h"

namespace XYZEngine
{
	ChaseComponent::ChaseComponent(GameObject* gameObject) : Component(gameObject)
	{
		transform = gameObject->GetComponent<TransformComponent>();
		body = gameObject->GetComponent<RigidbodyComponent>();

		XYZ_ASSERT(body != nullptr, "ChaseComponent requires RigidbodyComponent");
		if (body == nullptr)
		{
			Logger::Instance()->Error("ChaseComponent: RigidbodyComponent not found on " + gameObject->GetName());
		}
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
		if (newTarget != nullptr)
		{
			Logger::Instance()->Info("ChaseComponent on " + gameObject->GetName() +
				" now targeting " + newTarget->GetGameObject()->GetName());
		}
	}

	void ChaseComponent::SetDetectionRadius(float newRadius)
	{
		XYZ_ASSERT(newRadius > 0.f, "Detection radius must be positive");
		detectionRadius = newRadius;
	}

	void ChaseComponent::SetSpeed(float newSpeed)
	{
		XYZ_ASSERT(newSpeed >= 0.f, "Chase speed must be non-negative");
		speed = newSpeed;
	}
}
