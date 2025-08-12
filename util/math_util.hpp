#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include <cstdio>
#include <cstdbool>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <cassert>

// Forward declarations
struct Vector2;
struct Vector3;
struct Vector4;
struct Matrix4;

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
    Vector4 to_v4() const;
private:
    float x;
    float y;
    float z;
};

// Vector4
enum class Vector4Type {
    Point, // w = 0
    Direction // w = 1
};

// NOTE: VECTOR4 STRUCTURE
struct Vector4 {
public:
    Vector4(float x, float y, float z, Vector4Type type);
    Vector4(float x, float y, float z, float w);
    void print() const;
    float getX() const;
    float getY() const;
    float getZ() const;
    float getW() const;
    Vector4Type getType() const;
    Vector4 operator+(const Vector4& other) const;
    Vector4 operator-(const Vector4& other) const;
    Vector4 operator*(float value) const;
    float operator*(const Vector4& other) const;
    Vector4 cross(const Vector4& other) const;
    bool operator==(const Vector4& other) const;
    bool operator!=(const Vector4& other) const;
    float length() const;
    Vector4 normalize() const;
    Vector4 perspective_divide() const;
    Vector3 to_v3() const;
private:
    float x;
    float y;
    float z;
    Vector4Type type;
    float w;
};

#define ASSERT_DIRECTION(vec) \
    assert(((vec).getType() == Vector4Type::Direction) && "Expected a direction")

#define ASSERT_POINT(vec) \
    assert(((vec).getType() == Vector4Type::Point) && "Expected a point")

// Matrix4
#define MAT4_ROWS 4
#define MAT4_COLS 4
#define PI 3.14593f
#define EPSILION 0.15f
#define ROT_EPSILION 1e-5f

struct Matrix4 {
public:
    Matrix4();
    void print() const;

    float getElement(uint32_t row, uint32_t col) const;
    Matrix4 setElement(uint32_t row, uint32_t col, float element);
    Matrix4 operator+(const Matrix4& other) const;
    Matrix4 operator-(const Matrix4& other) const;
    Matrix4 operator*(const Matrix4& other) const;
    Matrix4 value(float value) const;
    Matrix4 identity() const;
    Matrix4 transpose() const;
    Matrix4 copy();
    Matrix4 scale(const Vector4& other) const;
    Matrix4 rotate_x(float degrees);
    Matrix4 rotate_y(float degrees);
    Matrix4 rotate_z(float degrees);
    bool operator==(const Matrix4& other) const;
    bool operator!=(const Matrix4& other) const;
    Vector4 transform(const Vector4& vec4) const;
    Matrix4 translate(const Vector4& vec4) const;
private:
    float rows[MAT4_ROWS][MAT4_COLS];
};

// Helper Functions
static inline bool floatEqual(float a, float b) {
    return fabsf(a - b) <= EPSILION;
}

static inline bool almostEqual(float a, float b) {
    return fabsf(a - b) < 5e-3f;
}

static inline void safeMemcpy(Matrix4 *dest, Matrix4 *src)
{
    if (src && dest) memcpy(dest, src, sizeof(Matrix4));
}

static inline float degreesToRadians(float degrees)
{
    return degrees * (PI / 180.0f);
}

#endif // MATH_UTIL_H
