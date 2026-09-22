#ifndef TEXTURE_CACHE_H_
#define TEXTURE_CACHE_H_

#include <string>

#include <SFML/Graphics.hpp>

namespace render
{
// Loads each sprite file at most once (keyed by path) and hands back a
// stable reference to it on every later call - Fish/Weed/Decoration clones
// sharing the same sprite all reuse one sf::Texture instead of re-reading
// the file from disk. References it returns stay valid until ClearCache().
const sf::Texture& GetTexture(const std::string& path);

// Releases every cached texture. Must be called while the sf::RenderWindow
// is still alive (before it goes out of scope): the cache would otherwise
// be destroyed later, as a function-local static, after the window (and its
// GL context) is already gone - destroying an sf::Texture with no live GL
// context crashes on exit.
void ClearCache();
}

#endif // TEXTURE_CACHE_H_
