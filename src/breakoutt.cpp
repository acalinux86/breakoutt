#include <iostream>
#include "./breakoutt.h"

int main(void)
{
    Vector2 position(1.0f, 1.0f);
    float value = 10.0;
    position.print();

    Vector2 scaled = position * value;
    scaled.print();
    return 0;
}
