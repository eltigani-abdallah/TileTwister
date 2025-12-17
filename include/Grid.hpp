#pragma once

#include <vector>
#include <array>
#include <utility>
#include "Tile.hpp"
#include "Direction.hpp"

class Grid {
    public:
        static const int GRID_SIZE = 4;
        using Row = std::array<Tile, GRID_SIZE>;
        using Board = std::array<Row, GRID_SIZE>;

        Grid();

        const Board& board() const { return m_board; }

        bool move(Direction dir);
        void reset();
        void addRandomTile();
        bool canMove() const;

    private:
        Board m_board{};

        std::vector<std::pair<int, int>> emptyCells() const;

        bool moveLeft();
        bool moveRight();
        bool moveUp();
        bool moveDown();

        bool slideAndCombineRow(std::array<Tile, GRID_SIZE>& line);
};