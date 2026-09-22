#include "render/TextureCache.h"

#include <iostream>
#include <unordered_map>

namespace render
{
namespace
{
std::unordered_map<std::string, sf::Texture>& Cache()
{
    static std::unordered_map<std::string, sf::Texture> cache;
    return cache;
}
}

const sf::Texture& GetTexture(const std::string& path)
{
    std::unordered_map<std::string, sf::Texture>& cache = Cache();

    const auto existing = cache.find(path);
    if (existing != cache.end())
        return existing->second;

    sf::Texture texture;
    if (!texture.loadFromFile(path))
        std::cerr << "Warning: could not load sprite " << path << " - it will render blank\n";

    return cache.emplace(path, std::move(texture)).first->second;
}

void ClearCache()
{
    Cache().clear();
}
}
