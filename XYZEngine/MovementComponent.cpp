#include "pch.h"
#include "MovementComponent.h"
#include "Logger.h"

namespace XYZEngine
{
	MovementComponent::MovementComponent(GameObject* gameObject) : Component(gameObject)
	{
		input = gameObject->GetComponent<InputComponent>();
		body = gameObject->GetComponent<RigidbodyComponent>();

		if (input == nullptr)
		{
			Logger::Instance()->Warning("MovementComponent: InputComponent not found on " + gameObject->GetName());
		}
		if (body == nullptr)
		{
			Logger::Instance()->Warning("MovementComponent: RigidbodyComponent not found on " + gameObject->GetName());
		}
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
