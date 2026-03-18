#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "Vector.h"

namespace XYZEngine
{
	class ChaseComponent : public Component
	{
	public:
		ChaseComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetTarget(TransformComponent* newTarget);
		void SetDetectionRadius(float newRadius);
		void SetSpeed(float newSpeed);
	private:
		TransformComponent* transform;
		RigidbodyComponent* body;
		TransformComponent* target = nullptr;
		float detectionRadius = 300.f;
		float speed = 150.f;
	};
}
