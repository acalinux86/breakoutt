#ifndef BREAKOUTT_H_
#define BREAKOUTT_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <cerrno>

#include "../util/math_util.hpp"
#include "../util/array.h"

struct Color {
    Color(float r, float g, float b, float a);
    void stats() const;
    float r;
    float g;
    float b;
    float a;
};

struct Vertex {
    Vector3 Position;
    Color color;
    Vertex(Vector3 Position, Color color);
};

struct Ball;
struct Tile;

typedef ARRAY(Ball) Balls;
typedef ARRAY(Tile) Bricks;
typedef ARRAY(uint32_t) Indices;
typedef ARRAY(Vertex) Vertices;

struct Ball {
public:
    Ball(Vector3 position, float radius, Color color,
         Vector3 velocity, int vcount, Indices indices,
         Vertices vertices);
    ~Ball();
    void stats() const;
    void RenderBall();

    Vector3 Position;
    float Radius;
    Color color;
    Vector3 Velocity;
    int vCount;
    Indices indices;
    Vertices vertices;
};

struct Tile {
public:
    Tile(Vector3 position, Vector3 size, Color color, Indices indices, Vertices vertices);
    ~Tile();
    void stats() const;
    void RenderTile();

    Vector3 Position;
    Vector3 Size;
    Color color;
    Indices indices;
    Vertices vertices;
};

struct Game {
    Game();
    void GameUpdate();

    Balls balls;
    Tile tile;
};

// Opengl Shader Related Functions
char *read_file(const char *file_path, uint8_t *size);
bool log_shader_error(GLuint Id);
bool log_program_error(GLuint Id);
GLuint compile_vertex(char *vertex_code);
GLuint compile_fragment(char *fragment_code);
GLuint LoadShader(const char *vertex_file_path, const char *fragment_file_path);
void calculate_fps(double *last_time, double *frame_count);

// Helper Functions
static inline int randomNumber()
{
    int min = 1;
    int max = 3;
    return (rand() % (max - min + 1)) + min;
}


#endif // BREAKOUTT_H_
