#pragma once

class Tile {
    public:
        Tile() = default;
        explicit Tile(int v) : value(v) {}

        bool isEmpty() const { return value == 0; }
        
        int getValue() const { return value; }
        void setValue(int v) { value = v; }

        void clear() { value = 0; }

    private:
        int value{0};
};