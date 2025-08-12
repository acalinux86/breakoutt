#ifndef BREAKOUTT_H_
#define BREAKOUTT_H_

#include "../util/math_util.hpp"

struct Ball {
public:
    Ball(Vector2 position, float radius):
        position(position), radius(radius)
    {}
private:
    Vector2 position;
    float radius;
};

#endif // BREAKOUTT_H_
