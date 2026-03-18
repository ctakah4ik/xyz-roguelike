#include "pch.h"
#include "ResourceSystem.h"
#include "Logger.h"

namespace XYZEngine
{
	ResourceSystem* ResourceSystem::Instance()
	{
		static ResourceSystem resourceSystem;
		return &resourceSystem;
	}

	void ResourceSystem::LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth)
	{
		if (textures.find(name) != textures.end())
		{
			Logger::Instance()->Warning("Texture '" + name + "' already loaded. Skipping.");
			return;
		}

		sf::Texture* newTexture = new sf::Texture();
		if (newTexture->loadFromFile(sourcePath))
		{
			newTexture->setSmooth(isSmooth);
			textures.emplace(name, newTexture);
			Logger::Instance()->Info("Loaded texture '" + name + "' from " + sourcePath);
		}
		else
		{
			Logger::Instance()->Error("Failed to load texture '" + name + "' from " + sourcePath);
			delete newTexture;
			throw EngineException("Failed to load texture: " + sourcePath);
		}
	}
	const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
	{
		auto it = textures.find(name);
		if (it == textures.end())
		{
			Logger::Instance()->Error("Texture '" + name + "' not found!");
			throw EngineException("Texture not found: " + name);
		}
		return it->second;
	}
	sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const
	{
		return new sf::Texture(*textures.find(name)->second);
	}
	void ResourceSystem::DeleteSharedTexture(const std::string& name)
	{
		auto texturePair = textures.find(name);

		sf::Texture* deletingTexure = texturePair->second;
		textures.erase(texturePair);
		delete deletingTexure;
	}

	void ResourceSystem::LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth)
	{
		if (textureMaps.find(name) != textureMaps.end())
		{
			Logger::Instance()->Warning("TextureMap '" + name + "' already loaded. Skipping.");
			return;
		}

		sf::Texture textureMap;
		if (textureMap.loadFromFile(sourcePath))
		{
			Logger::Instance()->Info("Loading texture map '" + name + "' from " + sourcePath +
				" (element: " + std::to_string(elementPixelSize.x) + "x" + std::to_string(elementPixelSize.y) +
				", count: " + std::to_string(totalElements) + ")");
			auto textureMapElements = new std::vector<sf::Texture*>();

			auto textureSize = textureMap.getSize();
			int loadedElements = 0;

			for (int y = 0; y <= textureSize.y - elementPixelSize.y; y += elementPixelSize.y)
			{
				if (loadedElements == totalElements)
				{
					break;
				}

				for (int x = 0; x <= textureSize.x - elementPixelSize.x; x += elementPixelSize.x)
				{
					if (loadedElements == totalElements)
					{
						break;
					}

					sf::Texture* newTextureMapElement = new sf::Texture();
					if (newTextureMapElement->loadFromFile(sourcePath, sf::IntRect(x, y, elementPixelSize.x, elementPixelSize.y)))
					{
						newTextureMapElement->setSmooth(isSmooth);
						textureMapElements->push_back(newTextureMapElement);
					}
					loadedElements++;
				}
			}

			textureMaps.emplace(name, *textureMapElements);
		}
	}
	const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return textures[elementIndex];
	}
	sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return new sf::Texture(*textures[elementIndex]);
	}
	int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return textures.size();
	}
	void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
	{
		auto textureMap = textureMaps.find(name);
		auto deletingTextures = textureMap->second;

		for (int i = 0; i < deletingTextures.size(); i++)
		{
			delete deletingTextures[i];
		}

		textureMaps.erase(textureMap);
	}

	void ResourceSystem::CreateColorTexture(const std::string& name, unsigned int width, unsigned int height, const sf::Color& color)
	{
		if (textures.find(name) != textures.end())
		{
			Logger::Instance()->Warning("Color texture '" + name + "' already exists. Skipping.");
			return;
		}

		sf::Image image;
		image.create(width, height, color);

		sf::Texture* newTexture = new sf::Texture();
		if (newTexture->loadFromImage(image))
		{
			textures.emplace(name, newTexture);
			Logger::Instance()->Info("Created color texture '" + name + "' (" +
				std::to_string(width) + "x" + std::to_string(height) + ")");
		}
		else
		{
			Logger::Instance()->Error("Failed to create color texture '" + name + "'");
			delete newTexture;
		}
	}

	void ResourceSystem::LoadSoundBuffer(const std::string& name, std::string sourcePath)
	{
		if (soundBuffers.find(name) != soundBuffers.end())
		{
			Logger::Instance()->Warning("Sound buffer '" + name + "' already loaded. Skipping.");
			return;
		}

		sf::SoundBuffer* newBuffer = new sf::SoundBuffer();
		if (newBuffer->loadFromFile(sourcePath))
		{
			soundBuffers.emplace(name, newBuffer);
			Logger::Instance()->Info("Loaded sound buffer '" + name + "' from " + sourcePath);
		}
		else
		{
			Logger::Instance()->Error("Failed to load sound buffer '" + name + "' from " + sourcePath);
			delete newBuffer;
			throw EngineException("Failed to load sound buffer: " + sourcePath);
		}
	}

	const sf::SoundBuffer* ResourceSystem::GetSoundBuffer(const std::string& name) const
	{
		auto it = soundBuffers.find(name);
		if (it != soundBuffers.end())
		{
			return it->second;
		}
		return nullptr;
	}

	void ResourceSystem::DeleteSoundBuffer(const std::string& name)
	{
		auto it = soundBuffers.find(name);
		if (it != soundBuffers.end())
		{
			delete it->second;
			soundBuffers.erase(it);
		}
	}

	void ResourceSystem::PlayMusic(const std::string& sourcePath, bool loop)
	{
		if (music.openFromFile(sourcePath))
		{
			music.setLoop(loop);
			music.play();
			Logger::Instance()->Info("Playing music: " + sourcePath + (loop ? " (looped)" : ""));
		}
		else
		{
			Logger::Instance()->Error("Failed to open music file: " + sourcePath);
		}
	}

	void ResourceSystem::StopMusic()
	{
		music.stop();
		Logger::Instance()->Info("Music stopped.");
	}

	void ResourceSystem::SetMusicVolume(float volume)
	{
		music.setVolume(volume);
	}

	void ResourceSystem::PlaySound(const std::string& bufferName)
	{
		CleanupFinishedSounds();

		auto it = soundBuffers.find(bufferName);
		if (it != soundBuffers.end())
		{
			sf::Sound* sound = new sf::Sound(*it->second);
			sound->play();
			activeSounds.push_back(sound);
			Logger::Instance()->Debug("Playing sound: " + bufferName);
		}
		else
		{
			Logger::Instance()->Warning("Sound buffer '" + bufferName + "' not found. Cannot play.");
		}
	}

	void ResourceSystem::CleanupFinishedSounds()
	{
		activeSounds.erase(
			std::remove_if(activeSounds.begin(), activeSounds.end(),
				[](sf::Sound* s) {
					if (s->getStatus() == sf::Sound::Stopped)
					{
						delete s;
						return true;
					}
					return false;
				}),
			activeSounds.end());
	}

	ResourceSystem::~ResourceSystem()
	{
		Clear();
	}

	void ResourceSystem::Clear()
	{
		StopMusic();
		DeleteAllTextures();
		DeleteAllTextureMaps();
		DeleteAllSoundBuffers();

		for (auto* s : activeSounds)
		{
			delete s;
		}
		activeSounds.clear();
	}

	void ResourceSystem::DeleteAllTextures()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& texturePair : textures)
		{
			keysToDelete.push_back(texturePair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTexture(key);
		}
	}
	void ResourceSystem::DeleteAllTextureMaps()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& textureMapPair : textureMaps)
		{
			keysToDelete.push_back(textureMapPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTextureMap(key);
		}
	}

	void ResourceSystem::DeleteAllSoundBuffers()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& bufferPair : soundBuffers)
		{
			keysToDelete.push_back(bufferPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSoundBuffer(key);
		}
	}
}