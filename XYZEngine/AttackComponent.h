#pragma once

#include "Component.h"
#include "ColliderComponent.h"
#include "HealthComponent.h"
#include "TransformComponent.h"
#include <SFML/Window/Keyboard.hpp>

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

		void SetRequireKey(sf::Keyboard::Key key);
		void SetAttackRange(float range);

	private:
		float damage = 10.f;
		float attackCooldown = 1.f;
		float cooldownTimer = 0.f;
		float attackRange = 50.f;

		bool hasRequiredKey = false;
		sf::Keyboard::Key requiredKey = sf::Keyboard::Unknown;

		TransformComponent* transform = nullptr;

		void OnCollisionHandler(Collision collision);
		void AttackNearbyTarget();
	};
}
