#pragma once

#include "Component.h"

namespace XYZEngine
{
	class HealthComponent : public Component
	{
	public:
		HealthComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void TakeDamage(float damage);
		void Heal(float amount);
		bool IsAlive() const;

		float GetHealth() const;
		float GetMaxHealth() const;
		float GetArmor() const;

		void SetMaxHealth(float maxHp);
		void SetArmor(float newArmor);
	private:
		float health = 100.f;
		float maxHealth = 100.f;
		float armor = 0.f;
	};
}
