#include "Game.hpp"

void Game::addRandomTile() {
    grid.addRandomTile();
}

bool Game::isGameOver() const {
    return !grid.canMove();
}

bool Game::hasWon() const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Tile* tile = grid.getTile(i, j);
            if (tile && tile->getValue() >= 2048) {
                return true;
            }
        }
    }
    return false;
}

Grid& Game::getGrid() {
    return grid;
}

void Game::move(Direction dir) {
    const bool moved1 = grid.move(dir);
    grid.mergeTiles(dir);
    const bool moved2 = grid.move(dir);

    if (moved1 || moved2) {
        addRandomTile();
    }
}
