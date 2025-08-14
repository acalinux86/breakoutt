#include "./breakoutt.hpp"

Color::Color(float r, float g, float b, float a):
    r(r), g(g), b(b), a(a) {}

void Color::stats() const
{
    printf("Color: [r: %.2f, g: %.2f, b: %.2f, a: %.2f]\n", r, g, b, a);
}

Ball::Ball(Vector3 position, float radius, Color color,
            Vector3 velocity, int vcount, Indices indices,
            Vertices vertices):
    Position(position), Radius(radius), color(color),
    Velocity(velocity), vCount(vcount), indices(indices),
    vertices(vertices)
{}

Ball::~Ball()
{
    array_delete(&vertices);
    array_delete(&indices);
}

void Ball::stats() const
{
    printf("Ball Info: \n");
    printf("    Position: ");
    Position.print();
    printf("    Radius: %.2f\n", Radius);
    printf("    vCount: %d\n", vCount);
    printf("    Color: ");
    color.stats();
    printf("    Velocity: ");
    Velocity.print();
    printf("    Vertices: ");
    array_analysis(&vertices);
    printf("    Indices: ");
    array_analysis(&indices);
}

void Ball::RenderBall()
{
    if (vertices.items) array_delete(&vertices);
    if (indices.items) array_delete(&indices);

    float angle = 360.0f / vCount;
    int triangleCount = vCount - 2;
    array_new(&indices, uint32_t);
    array_new(&vertices, Vertex);

    // positions
    for (int i = 0; i < vCount; i++)
    {
        float currentAngle = angle * i;
        float x = Radius * cosf(degreesToRadians(currentAngle));
        float y = Radius * sinf(degreesToRadians(currentAngle));
        float z = 0.0f;
        array_append(Vertex, &vertices, Vertex(Position + Vector3(x, y, z), color));
    }

    for (int i = 0; i < triangleCount; i++)
    {
        array_append(uint32_t, &indices, 0);
        array_append(uint32_t, &indices, i + 1);
        array_append(uint32_t, &indices, i + 2);
    }
}

Tile::Tile(Vector3 position, Vector3 size, Color color,
           Indices indices, Vertices vertices):
    Position(position), Size(size), color(color),
    indices(indices), vertices(vertices)
{}

Tile::~Tile()
{
    array_delete(&vertices);
    array_delete(&indices);
}

void Tile::stats() const
{
    printf("Tile Info: \n");
    printf("    Position: ");
    Position.print();
    printf("    Size: ");
    Size.print();
    printf("    Color: ");
    color.stats();
    printf("    Vertices: ");
    array_analysis(&vertices);
    printf("    Indices: ");
    array_analysis(&indices);
}

void Tile::RenderTile()
{
    if (vertices.items) array_delete(&vertices);
    if (indices.items) array_delete(&indices);

    // Calculate corner positions
    Vector3 half_size = Size *  0.5f;
    float x = half_size.x;
    float y = half_size.y;
    Vector3 corners[4] = {
        Position + Vector3(-x,  -y, 0.0f), // botom-left
        Position + Vector3(-x,   y, 0.0f), // top-left
        Position + Vector3( x,   y, 0.0f), // top-right
        Position + Vector3( x,  -y, 0.0f) // bottom-right
    };

    uint32_t base_index = vertices.count;
    for (uint32_t i = 0; i < 4; ++i) {
        array_append(Vertex, &vertices, Vertex(corners[i], color));
    }

    uint32_t quad_indices[6] = {
        base_index, base_index+1, base_index+2,
        base_index, base_index+2, base_index+3
    };
    for (uint32_t i = 0; i < 6; ++i) {
        array_append(uint32_t, &indices, quad_indices[i]);
    }
}

Vertex::Vertex(Vector3 Position, Color color):
    Position(Position), color(color) {}
