#ifndef BREAKOUTT_H_
#define BREAKOUTT_H_

#include "./math_util.h"

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
