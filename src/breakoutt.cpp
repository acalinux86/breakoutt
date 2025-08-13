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

Vector2 Ball::GetPosition() const
{
    return Position;
}

float Ball::GetRadius() const
{
    return Radius;
}

void Ball::SetPosition(Vector2 NewPosition)
{
    Position = NewPosition;
}

void Ball::SetRadius(float Radius)
{
    Radius = Radius;
}

void Ball::BallMove(Vector2 moveValue)
{
    Vector2 Pos = GetPosition();
    Pos = Pos + moveValue;
    SetPosition(Pos);
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
