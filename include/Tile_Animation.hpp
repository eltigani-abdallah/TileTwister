// TileAnimation.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class TileAnimation {
public:
    TileAnimation(sf::Vector2f start, sf::Vector2f end, float duration,
                  std::function<float(float)> easing = nullptr);

    void update(float dt);
    bool isFinished() const;
    sf::Vector2f getCurrentPosition() const;

private:
    sf::Vector2f startPos, endPos;
    float duration;
    float elapsed;
    std::function<float(float)> easingFunc;
};
