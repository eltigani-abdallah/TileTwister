float t = std::min(1.f, elapsed / duration);
sf::Vector2f pos = startPos + t * (targetPos - startPos);
tile.setPosition(pos);
