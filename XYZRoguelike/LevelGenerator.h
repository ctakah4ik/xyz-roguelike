#pragma once

#include <vector>
#include <memory>
#include "Wall.h"
#include "Floor.h"

namespace XYZRoguelike
{
	class LevelGenerator
	{
	public:
		void Generate(float centerX, float centerY, int gridWidth, int gridHeight, int tileSize = 32);

	private:
		std::vector<std::shared_ptr<Wall>> walls;
		std::vector<std::shared_ptr<Floor>> floors;
	};
}
