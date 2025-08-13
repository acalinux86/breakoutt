#include "./breakoutt.hpp"

Ball::Ball(Vector2 position, float radius):
    Position(position), Radius(radius) {}

void Ball::stats() const
{
    printf("Ball Info: \n");
    printf("    Position: ");
    Position.print();
    printf("    Radius: %.2f\n", Radius);
}

Tile::Tile(Vector2 position, Vector2 size):
    Position(position), Size(size) {}

void Tile::stats() const
{
    printf("Tile Info: \n");
    printf("    Position: ");
    Position.print();
    printf("    Size: ");
    Size.print();
}
