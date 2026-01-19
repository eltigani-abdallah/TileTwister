// Tile_Animation.cpp
#include "Tile_Animation.hpp"
#include <algorithm>

TileAnimation::TileAnimation(sf::Vector2f start, sf::Vector2f end, float duration,
                             std::function<float(float)> easing)
    : startPos(start), endPos(end), duration(duration), elapsed(0.f), easingFunc(easing) {}

void TileAnimation::update(float dt) {
    elapsed = std::min(elapsed + dt, duration);
}

bool TileAnimation::isFinished() const {
    return elapsed >= duration;
}

sf::Vector2f TileAnimation::getCurrentPosition() const {
    float t = std::min(1.f, elapsed / duration);
    if (easingFunc) t = easingFunc(t);
    return startPos + t * (endPos - startPos);
}
