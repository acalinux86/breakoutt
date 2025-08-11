#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

// Vector2
struct Vector2 {
public:
    Vector2(float x, float y);
    void print() const;

    float getX() const;
    float getY() const;

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    float operator*(const Vector2& other) const;
    Vector2 operator*(float value) const; // NOTE: If value is negative, direction reverses else unchanged

    float length() const; // NOTE: returns the Magnitude of a Vector
    Vector2 normalize() const;

private:
    float x;
    float y;
};


// Vector3

// NOTE: VECTOR3 STRUCTURE
struct Vector3 {
public:
    // NOTE: VECTOR3 PROTOTYPES
    Vector3(float x, float y, float z);
    void print() const;

    float getX() const;
    float getY() const;
    float getZ() const;

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;

    Vector3 cross(const Vector3& other) const;
    Vector3 operator*(float scalar) const;
    float   operator*(const Vector3& other) const;

    float length() const;
    Vector3 normalize() const;

private:
    float x;
    float y;
    float z;
};

// // Vector4

// // NOTE: VECTOR4 STRUCTURE
// typedef struct {
//     float x;
//     float y;
//     float z;
//     float w;
// } Vector4;


// // NOTE: VECTOR4 PROTOTYPES
// Vector4 v4_init(float x, float y, float z, float w);
// Vector4 v4_point(float x, float y, float z);
// Vector4 v4_direction(float x, float y, float z);

// void v4_print(const Vector4 *self, const char *name);
// #define V4_PRINT(self) v4_print(&self, #self)

// Vector4 v4_add(Vector4 a, Vector4 b);
// Vector4 v4_sub(Vector4 a, Vector4 b);

// Vector4 v4_scale(Vector4 a, float value);
// Vector4 v4_cross(Vector4 a, Vector4 b);
// float v4_dot(Vector4 a, Vector4 b);

// float v4_length(Vector4 a);
// Vector4 v4_normalize(Vector4 a);
// Vector4 v4_perspective_divide(Vector4 a);
// bool v4_equals(Vector4 a, Vector4 b);

// // Matrix4
// #define MAT4_ROWS 4
// #define MAT4_COLS 4
// #define PI 3.14593f
// #define EPSILON 1e-3f

// typedef struct {
//     float rows[MAT4_ROWS][MAT4_COLS];
// } Matrix4;

// void mat4_print(const Matrix4 *self, const char *name);
// #define MAT4_PRINT(self) mat4_print(&self, #self);

// Matrix4 mat4_add(Matrix4 a, Matrix4 b);
// Matrix4 mat4_sub(Matrix4 a, Matrix4 b);
// Matrix4 mat4_mult(Matrix4 a, Matrix4 b);

// Matrix4 mat4_value(float value);
// Matrix4 mat4_identity();

// Matrix4 mat4_transpose(Matrix4 mat4);

// Matrix4 mat4_copy(Matrix4 mat4);

// Matrix4 mat4_rotate_x(float degrees);
// Matrix4 mat4_rotate_y(float degrees);
// Matrix4 mat4_rotate_z(float degrees);

// // Matvec (Matrix and Vector related Operations)

// Vector4 v4_from_v3(Vector3 vec3);
// Vector3 v3_from_v4(Vector4 vec4);
// Vector4 mv4_transform(Matrix4 mat_4, Vector4 vec_4);
// Matrix4 mv4_translate(Vector4 vec_4);
// Vector3 to_screen_coords(Vector3 vec3, uint32_t screen_width, uint32_t screen_height);
// Vector3 to_world_coords(Vector3 vec3, uint32_t screen_width, uint32_t screen_height);

#endif // MATH_UTIL_H
