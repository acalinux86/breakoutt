#ifndef BREAKOUTT_H_
#define BREAKOUTT_H_

#include "../util/math_util.hpp"
#include "../util/array.h"

struct Ball;
struct Game;
struct Tile;
typedef ARRAY(Ball) Balls;

struct Ball {
public:
    Ball(Vector2 position, float radius);
    void stats() const;
private:
    Vector2 Position;
    float Radius;
};

struct Tile {
public:
    Tile(Vector2 position, Vector2 size);
    void stats() const;
private:
    Vector2 Position;
    Vector2 Size;
};

struct Game {
    Game();
    int GameUpdate();
private:
    Balls balls;
    Tile tile;
};

#endif // BREAKOUTT_H_
