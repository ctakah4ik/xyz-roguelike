#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Logger.h"

namespace XYZEngine
{
	CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
	{
		view = new sf::View(sf::FloatRect(0, 0, 800, -600));
		transform = gameObject->GetComponent<TransformComponent>();
		Logger::Instance()->Debug("CameraComponent created for " + gameObject->GetName());
	}
	CameraComponent::~CameraComponent()
	{
		delete view;
	}

	void CameraComponent::Update(float deltaTime)
	{
		XYZ_ASSERT(window != nullptr, "CameraComponent::Update called with null window");

		auto position = transform->GetWorldPosition();
		auto rotation = transform->GetWorldRotation();

		view->setCenter(Convert<sf::Vector2f, Vector2Df>(position));
		view->setRotation(rotation);

		window->setView(*view);
	}
	void CameraComponent::Render()
	{
		if (window == nullptr)
		{
			Logger::Instance()->Error("CameraComponent: window is null during Render.");
		}
	}

	void CameraComponent::SetBaseResolution(int width, int height)
	{
		XYZ_ASSERT(width > 0 && height > 0, "Camera resolution must be positive");
		view->reset(sf::FloatRect(0, 0, width, -height));
		Logger::Instance()->Info("Camera resolution set to " + std::to_string(width) + "x" + std::to_string(height));
	}
	void CameraComponent::SetWindow(sf::RenderWindow* newWindow)
	{
		XYZ_ASSERT(newWindow != nullptr, "Cannot set null window on CameraComponent");
		if (newWindow == nullptr)
		{
			Logger::Instance()->Error("Attempted to set null window on CameraComponent.");
			throw EngineException("CameraComponent: cannot set null window");
		}
		window = newWindow;
	}
	void CameraComponent::ZoomBy(float newZoom)
	{
		if (newZoom <= 0)
		{
			Logger::Instance()->Warning("CameraComponent: zoom value must be > 0. Got: " + std::to_string(newZoom));
			return;
		}
		view->zoom(newZoom);
	}
}