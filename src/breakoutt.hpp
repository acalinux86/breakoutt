#ifndef BREAKOUTT_H_
#define BREAKOUTT_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <cerrno>

#include "../util/math_util.hpp"
#include "../util/array.h"

struct Ball;
struct Game;
struct Tile;
struct Color;
typedef ARRAY(Ball) Balls;

struct Ball {
public:
    Ball(Vector2 Position, float Radius);
    void stats() const;
    Vector2 GetPosition() const;
    float GetRadius() const;
    void SetPosition(Vector2 NewPosition);
    void SetRadius(float Radius);
    void BallMove(Vector2 MoveValue);
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

struct Color {
public:
    Color(float r, float g, float b, float a);
    void print() const;
    float r;
    float g;
    float b;
    float a;
};

// Opengl Shader Related Functions
char *read_file(const char *file_path, uint8_t *size);
bool log_shader_error(GLuint Id);
bool log_program_error(GLuint Id);
GLuint compile_vertex(char *vertex_code);
GLuint compile_fragment(char *fragment_code);
GLuint LoadShader(const char *vertex_file_path, const char *fragment_file_path);
void calculate_fps(double *last_time, double *frame_count);

#endif // BREAKOUTT_H_
