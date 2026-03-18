#include "pch.h"
#include "MovementComponent.h"

namespace XYZEngine
{
	MovementComponent::MovementComponent(GameObject* gameObject) : Component(gameObject)
	{
		input = gameObject->GetComponent<InputComponent>();
		body = gameObject->GetComponent<RigidbodyComponent>();
	}

	void MovementComponent::Update(float deltaTime)
	{
		if (input == nullptr || body == nullptr)
		{
			return;
		}

		float h = input->GetHorizontalAxis();
		float v = input->GetVerticalAxis();

		body->SetLinearVelocity({ h * speed * deltaTime, v * speed * deltaTime });
	}

	void MovementComponent::Render()
	{
	}

	void MovementComponent::SetSpeed(float newSpeed)
	{
		speed = newSpeed;
	}

	float MovementComponent::GetSpeed() const
	{
		return speed;
	}
}
