#include "pch.h"
#include "AttackComponent.h"
#include "GameObject.h"
#include "PhysicsSystem.h"
#include "Logger.h"

namespace XYZEngine
{
	AttackComponent::AttackComponent(GameObject* gameObject) : Component(gameObject)
	{
		transform = gameObject->GetComponent<TransformComponent>();

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

		// Key-press mode: attack nearby targets when key is pressed
		if (hasRequiredKey && sf::Keyboard::isKeyPressed(requiredKey) && cooldownTimer <= 0.f)
		{
			auto myHealth = gameObject->GetComponent<HealthComponent>();
			if (myHealth == nullptr || myHealth->IsAlive())
			{
				AttackNearbyTarget();
			}
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

	void AttackComponent::SetRequireKey(sf::Keyboard::Key key)
	{
		hasRequiredKey = true;
		requiredKey = key;
	}

	void AttackComponent::SetAttackRange(float range)
	{
		XYZ_ASSERT(range > 0.f, "Attack range must be positive");
		attackRange = range;
	}

	void AttackComponent::AttackNearbyTarget()
	{
		if (transform == nullptr)
		{
			return;
		}

		Vector2Df myPos = transform->GetWorldPosition();
		const auto& colliders = PhysicsSystem::Instance()->GetColliders();

		for (auto* collider : colliders)
		{
			if (collider->GetGameObject() == gameObject)
			{
				continue;
			}

			auto targetHealth = collider->GetGameObject()->GetComponent<HealthComponent>();
			if (targetHealth == nullptr || !targetHealth->IsAlive())
			{
				continue;
			}

			auto targetTransform = collider->GetGameObject()->GetComponent<TransformComponent>();
			Vector2Df targetPos = targetTransform->GetWorldPosition();
			Vector2Df diff = targetPos - myPos;
			float distance = diff.GetLength();

			if (distance <= attackRange)
			{
				Logger::Instance()->Info(
					gameObject->GetName() + " attacks " +
					collider->GetGameObject()->GetName() +
					" for " + std::to_string(damage) + " damage");

				targetHealth->TakeDamage(damage);
				cooldownTimer = attackCooldown;
				return;
			}
		}
	}

	void AttackComponent::OnCollisionHandler(Collision collision)
	{
		// Auto-attack mode (no key required)
		if (hasRequiredKey || cooldownTimer > 0.f)
		{
			return;
		}

		auto myHealth = gameObject->GetComponent<HealthComponent>();
		if (myHealth != nullptr && !myHealth->IsAlive())
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
