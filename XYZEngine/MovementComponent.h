#pragma once

#include "Component.h"
#include "InputComponent.h"
#include "RigidbodyComponent.h"

namespace XYZEngine
{
	class MovementComponent : public Component
	{
	public:
		MovementComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetSpeed(float newSpeed);
		float GetSpeed() const;
	private:
		float speed = 200.f;
		InputComponent* input;
		RigidbodyComponent* body;
	};
}
