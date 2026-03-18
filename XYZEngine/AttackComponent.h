#pragma once

#include "Component.h"
#include "ColliderComponent.h"
#include "HealthComponent.h"

namespace XYZEngine
{
	class AttackComponent : public Component
	{
	public:
		AttackComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetDamage(float newDamage);
		void SetAttackCooldown(float cooldown);
		float GetDamage() const;
	private:
		float damage = 10.f;
		float attackCooldown = 1.f;
		float cooldownTimer = 0.f;

		void OnCollisionHandler(Collision collision);
	};
}
