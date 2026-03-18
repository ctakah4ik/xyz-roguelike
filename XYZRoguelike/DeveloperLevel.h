#pragma once

#include <iostream>
#include <array>
#include <memory>
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelGenerator.h"

using namespace XYZEngine;

namespace XYZRoguelike
{
	class DeveloperLevel : public Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;
	private:
		std::shared_ptr<Player> player;
		std::shared_ptr<Enemy> enemy;
		std::shared_ptr<LevelGenerator> levelGenerator;
	};
}
