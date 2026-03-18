#include "LevelGenerator.h"
#include <cmath>

namespace XYZRoguelike
{
	void LevelGenerator::Generate(float centerX, float centerY, int gridWidth, int gridHeight, int tileSize)
	{
		float halfWidth = (gridWidth * tileSize) / 2.f;
		float halfHeight = (gridHeight * tileSize) / 2.f;

		float startX = std::round(centerX - halfWidth + tileSize / 2.f);
		float startY = std::round(centerY - halfHeight + tileSize / 2.f);

		// Create floor tiles for the interior (created first to render behind)
		for (int y = 1; y < gridHeight - 1; y++)
		{
			for (int x = 1; x < gridWidth - 1; x++)
			{
				float posX = startX + x * tileSize;
				float posY = startY + y * tileSize;
				floors.push_back(std::make_shared<Floor>(posX, posY, tileSize));
			}
		}

		// Create wall tiles around the perimeter
		for (int x = 0; x < gridWidth; x++)
		{
			float posX = startX + x * tileSize;

			// Top row
			walls.push_back(std::make_shared<Wall>(posX, startY, tileSize));

			// Bottom row
			float bottomY = startY + (gridHeight - 1) * tileSize;
			walls.push_back(std::make_shared<Wall>(posX, bottomY, tileSize));
		}

		for (int y = 1; y < gridHeight - 1; y++)
		{
			float posY = startY + y * tileSize;

			// Left column
			walls.push_back(std::make_shared<Wall>(startX, posY, tileSize));

			// Right column
			float rightX = startX + (gridWidth - 1) * tileSize;
			walls.push_back(std::make_shared<Wall>(rightX, posY, tileSize));
		}
	}
}
