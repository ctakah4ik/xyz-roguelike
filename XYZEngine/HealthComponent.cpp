#include "pch.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "Logger.h"

namespace XYZEngine
{
	HealthComponent::HealthComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	void HealthComponent::Update(float deltaTime)
	{
	}

	void HealthComponent::Render()
	{
	}

	void HealthComponent::TakeDamage(float damage)
	{
		XYZ_ASSERT(damage >= 0.f, "Damage value must be non-negative");

		if (!IsAlive())
		{
			return;
		}

		float effectiveDamage = damage * (1.f - armor);
		if (effectiveDamage < 0.f)
		{
			effectiveDamage = 0.f;
		}

		health -= effectiveDamage;

		Logger::Instance()->Info(
			gameObject->GetName() + " took " + std::to_string(effectiveDamage) +
			" damage (armor absorbed " + std::to_string(damage - effectiveDamage) +
			"). HP: " + std::to_string(health) + "/" + std::to_string(maxHealth));

		if (health <= 0.f)
		{
			health = 0.f;
			Logger::Instance()->Warning(gameObject->GetName() + " has been killed!");
		}
	}

	void HealthComponent::Heal(float amount)
	{
		XYZ_ASSERT(amount >= 0.f, "Heal amount must be non-negative");

		if (!IsAlive())
		{
			Logger::Instance()->Warning("Attempted to heal dead object: " + gameObject->GetName());
			return;
		}

		health += amount;
		if (health > maxHealth)
		{
			health = maxHealth;
		}

		Logger::Instance()->Debug(gameObject->GetName() + " healed for " +
			std::to_string(amount) + ". HP: " + std::to_string(health) + "/" + std::to_string(maxHealth));
	}

	bool HealthComponent::IsAlive() const
	{
		return health > 0.f;
	}

	float HealthComponent::GetHealth() const
	{
		return health;
	}

	float HealthComponent::GetMaxHealth() const
	{
		return maxHealth;
	}

	float HealthComponent::GetArmor() const
	{
		return armor;
	}

	void HealthComponent::SetMaxHealth(float maxHp)
	{
		XYZ_ASSERT(maxHp > 0.f, "Max health must be positive");

		if (maxHp <= 0.f)
		{
			Logger::Instance()->Error("Attempted to set non-positive max health for " + gameObject->GetName());
			return;
		}

		maxHealth = maxHp;
		health = maxHp;
		Logger::Instance()->Debug(gameObject->GetName() + " max health set to " + std::to_string(maxHp));
	}

	void HealthComponent::SetArmor(float newArmor)
	{
		if (newArmor < 0.f || newArmor > 1.f)
		{
			Logger::Instance()->Warning("Armor value " + std::to_string(newArmor) +
				" out of range [0,1] for " + gameObject->GetName() + ". Clamping.");
			if (newArmor < 0.f) newArmor = 0.f;
			if (newArmor > 1.f) newArmor = 1.f;
		}

		armor = newArmor;
		Logger::Instance()->Debug(gameObject->GetName() + " armor set to " + std::to_string(armor));
	}
}
