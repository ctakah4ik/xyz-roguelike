#include "pch.h"
#include "AttackComponent.h"
#include "GameObject.h"
#include "Logger.h"

namespace XYZEngine
{
	AttackComponent::AttackComponent(GameObject* gameObject) : Component(gameObject)
	{
		auto collider = gameObject->GetComponent<ColliderComponent>();
		if (collider == nullptr)
		{
			Logger::Instance()->Error("AttackComponent requires a ColliderComponent on " + gameObject->GetName());
			return;
		}

		collider->SubscribeCollision([this](Collision collision) {
			OnCollisionHandler(collision);
		});

		Logger::Instance()->Debug("AttackComponent added to " + gameObject->GetName());
	}

	void AttackComponent::Update(float deltaTime)
	{
		if (cooldownTimer > 0.f)
		{
			cooldownTimer -= deltaTime;
		}
	}

	void AttackComponent::Render()
	{
	}

	void AttackComponent::SetDamage(float newDamage)
	{
		XYZ_ASSERT(newDamage >= 0.f, "Damage must be non-negative");
		damage = newDamage;
	}

	void AttackComponent::SetAttackCooldown(float cooldown)
	{
		XYZ_ASSERT(cooldown > 0.f, "Attack cooldown must be positive");
		attackCooldown = cooldown;
	}

	float AttackComponent::GetDamage() const
	{
		return damage;
	}

	void AttackComponent::OnCollisionHandler(Collision collision)
	{
		if (cooldownTimer > 0.f)
		{
			return;
		}

		ColliderComponent* otherCollider = collision.GetFirst();
		if (otherCollider->GetGameObject() == gameObject)
		{
			otherCollider = collision.GetSecond();
		}

		auto targetHealth = otherCollider->GetGameObject()->GetComponent<HealthComponent>();
		if (targetHealth != nullptr && targetHealth->IsAlive())
		{
			Logger::Instance()->Info(
				gameObject->GetName() + " attacks " +
				otherCollider->GetGameObject()->GetName() +
				" for " + std::to_string(damage) + " damage");

			targetHealth->TakeDamage(damage);
			cooldownTimer = attackCooldown;
		}
	}
}
