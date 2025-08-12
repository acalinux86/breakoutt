#include "./math_util.h"

// NOTE: VECTOR2 Implementation
Vector2::Vector2(float x, float y) : x(x), y(y) {}

void Vector2::print() const
{
    printf("Vector2: [%.2f, %.2f]\n", getX(), getY());
}

float Vector2::getX() const
{
    return x;
}

float Vector2::getY() const
{
    return y;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(getX() + other.getX(), getY() + other.getY());
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(getX() - other.getX(), getY() - other.getY());
}

// NOTE: If value is negative, direction reverses else unchanged
Vector2 Vector2::operator*(float value) const
{
    return Vector2(getX()*value, getY()*value);
}

float Vector2::operator*(const Vector2& other) const
{
    return (getX()*other.getX()) + (getY()*other.getY());
}

// NOTE: returns the Magnitude of a Vector
float Vector2::length() const
{
    return sqrtf((x*x) + (y*y));
}

Vector2 Vector2::normalize() const
{
    float mag = length();
    if (mag == 0.0f) return Vector2(0.0f, 0.0f);
    else return Vector2(getX()/mag, getY()/mag);
}

// NOTE: Vector3 Implementation
Vector3::Vector3(float x, float y, float z):
    x(x), y(y), z(z) {}

float Vector3::getX() const
{
    return x;
}

float Vector3::getY() const
{
    return y;
}

float Vector3::getZ() const
{
    return z;
}

void Vector3::print() const
{
    printf("Vector3: [%.2f, %.2f, %.2f]\n", getX(), getY(), getZ());
}

Vector3 Vector3::operator+(const Vector3& other) const
{

    return Vector3(getX() + other.getX(), getY() + other.getY(), getZ() + other.getZ());
}

Vector3 Vector3::operator-(const Vector3& other) const
{

    return Vector3(getX() - other.getX(), getY() - other.getY(), getZ() - other.getZ());
}

// Function that returns the Dot Product of two Vectors -> (a float)
float Vector3::operator*(const Vector3& other) const
{
    return (getX()*other.getX()) + (getY()*other.getY()) + (getZ()*other.getZ());
}

// Function that Returns A Cross Product of two Vectors
Vector3 Vector3::cross(const Vector3& other) const
{
    float cross_x = getY() * other.getZ() - getZ() * other.getY();
    float cross_y = getZ() * other.getX() - getX() * other.getZ();
    float cross_z = getX() * other.getY() - getY() * other.getX();

    return Vector3(cross_x, cross_y, cross_z);
}

// Scale A 3D Vector by a scalar
Vector3 Vector3::operator*(float scalar) const
{
    return Vector3(getX()*scalar, getY()*scalar, getZ()*scalar);
}

// Length of a vector
float Vector3::length() const
{
    return sqrtf(((getX()*getX()) + (getY()*getY()) + (getZ()*getZ())));
}

// Function that Normalizes a 3D Vector
Vector3 Vector3::normalize() const
{
    float mag = length();
    if (mag == 0.0f) return Vector3(0.0f, 0.0f, 0.0f);
    else return Vector3(getX()/mag, getY()/mag, getZ()/mag);
}

// NOTE: Vector4 Implementation

// Constructors for Vector4
Vector4::Vector4(float x, float y, float z, Vector4Type type):
    x(x), y(y), z(z), type(type), w(type == Vector4Type::Point ? 1.0f : 0.0f) {}

Vector4::Vector4(float x, float y, float z, float w):
    x(x), y(y), z(z), w(w) {}

void Vector4::print() const
{
    if (getW() != 0) {
        printf("Point: [%.2f, %.2f, %.2f, %.2f]\n", getX(), getY(), getZ(), getW());
    } else {
        printf("Direction: [%.2f, %.2f, %.2f, %.2f]\n", getX(), getY(), getZ(), getW());
    }
}

float Vector4::getX() const
{
    return x;
}

float Vector4::getY() const
{
    return y;
}

float Vector4::getZ() const
{
    return z;
}

float Vector4::getW() const
{
    return w;
}

Vector4Type Vector4::getType() const
{
    return type;
}

Vector4 Vector4::operator+(const Vector4& other) const
{
    if (getType() == Vector4Type::Point && other.getType() == Vector4Type::Point)
        assert(false && "Cannot Add Two Points");
    return Vector4(getX() + other.getX(), getY() + other.getY(), getZ() + other.getZ(),
                   (getType() == Vector4Type::Point) ? 1.0f : 0.0f); // Operates on all components
}

// Function that Subtracts Two Vector
Vector4 Vector4::operator-(const Vector4& other) const
{
    if (getType() == Vector4Type::Direction && other.getType() == Vector4Type::Point)
        assert(false && "Cannot subtract a point from a direction");

    if (getType() == Vector4Type::Point && other.getType() == Vector4Type::Point)
        return Vector4(x - other.x, y - other.y, z - other.z, Vector4Type::Direction);
    return Vector4(getX() - other.getX(), getY() - other.getY(), getZ() - other.getZ(),
                   (getType() == Vector4Type::Point) ? 1.0f : 0.0f); // Operates on all components
}

// Function that returns the Dot Product of two Vectors -> (a float)
float Vector4::operator*(const Vector4& other) const
{
    ASSERT_DIRECTION(*this);
    ASSERT_DIRECTION(other);
    return ((getX()*other.getX()) + (getY()*other.getY()) + (getZ()*other.getZ()));
}

// Function that Returns A Cross Product of two Vectors
Vector4 Vector4::cross(const Vector4& other) const
{
    ASSERT_DIRECTION(*this);
    ASSERT_DIRECTION(other);
    float cross_x = getY() * other.getZ() - getZ() * other.getY();
    float cross_y = getZ() * other.getX() - getX() * other.getZ();
    float cross_z = getX() * other.getY() - getY() * other.getX();

    return Vector4(cross_x, cross_y, cross_z, Vector4Type::Direction); // cross product always returns direction
}

// Scale A 4D Vector by a value
Vector4 Vector4::operator*(float value) const
{
    if (getType() == Vector4Type::Point)
        assert(false && "Scaling Point Not Geomerically Valid");
    return Vector4(getX()*value, getY()*value, getZ()*value, getW());
}

// Length of a vector
float Vector4::length() const
{
    ASSERT_DIRECTION(*this);
    // Only Compute Length for 3d Products (Homogenous coordinates)
    return sqrtf(((getX()*getX())+(getY()*getY())+(getZ()*getZ())));
}

// Function that Normalizes a 4D Vector
Vector4 Vector4::normalize() const
{
    ASSERT_DIRECTION(*this);
    float mag = length();
    if (mag == 0.0f) return Vector4(0.0f, 0.0f, 0.0f, getW()); // Preserve Original w
    else return Vector4(getX()/mag, getY()/mag, getZ()/mag, getW()); // Preserve Original w
}

Vector4 Vector4::perspective_divide() const
{
    if (getW() == 0) return Vector4(getX(), getY(), getZ(), getW());
    else return Vector4(getX()/getW(), getY()/getW(), getZ()/getW(), Vector4Type::Point);
}

bool Vector4::operator==(const Vector4& other) const
{
    const float epsilion = 1e-3;
    if (getW() != other.getW()) return false;
    if (getW() == 0) {
        return (fabs(getX() - other.getX()) < epsilion)
            && (fabs(getY() - other.getY()) < epsilion)
            && (fabs(getZ() - other.getZ()) < epsilion)
            && (getType() == other.getType());
    } else {
        Vector4 norm_a = perspective_divide();
        Vector4 norm_b = other.perspective_divide();

        return  (fabs(norm_a.getX() - norm_b.getX()) < epsilion)
            &&  (fabs(norm_a.getY() - norm_b.getY()) < epsilion)
            &&  (fabs(norm_a.getZ() - norm_b.getZ()) < epsilion)
            &&  (norm_a.getType() == norm_b.getType());
    }
}

bool Vector4::operator!=(const Vector4& other) const
{
    return !(*this == other);
}

// Matrix4 Implementation
static inline void safe_memcpy(Matrix4 *dest, Matrix4 *src)
{
    if (src && dest) memcpy(dest, src, sizeof(Matrix4));
}

void Matrix4::print() const
{
    printf("Matrix4: {\n");
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        printf("    [ ");
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            printf("%3.2f ", rows[i][j]);
        }
        printf("]\n");
    }
    printf("}\n");
}

float Matrix4::getElement(uint32_t row, uint32_t col) const
{
    assert(((int)row >= 0 && (int)row < MAT4_ROWS) && "Row Out of Bounds");
    assert(((int)col >= 0 && (int)col < MAT4_COLS) && "Col Out of Bounds");
    return rows[row][col];
}

Matrix4 Matrix4::setElement(uint32_t row, uint32_t col, float element)
{
    assert(((int)row >= 0 && (int)row < MAT4_ROWS) && "Row Out of Bounds");
    assert(((int)col >= 0 && (int)col < MAT4_COLS) && "Col Out of Bounds");
    rows[row][col] = element;
    return *this;
}

Matrix4 Matrix4::operator+(const Matrix4& other) const
{
    Matrix4 result = {};
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            result.rows[i][j] = rows[i][j] + other.rows[i][j];
        }
    }
    return result;
}

Matrix4 Matrix4::operator-(const Matrix4& other) const
{
    Matrix4 result = {};
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            result.rows[i][j] = rows[i][j] - other.rows[i][j];
        }
    }
    return result;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
    // a b    e f   ae + bg   af + bh
    //      X
    // c d    g h   ce + dg   cf + dh
    //

    Matrix4 result = {};
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            float c = 0.0f;
            for (uint32_t k = 0; k < MAT4_COLS; ++k) {
                c += rows[i][k] * other.rows[k][j];
            }
            result.rows[i][j] = c;
        }
    }
    return result;
}

Matrix4 Matrix4::value(float value) const
{
    /*Matrix4 result = {
        .rows = {
                {value, 0.0f,  0.0f,  0.0f},
                {0.0f,  value, 0.0f,  0.0f},
                {0.0f,  0.0f,  value, 0.0f},
                {0.0f,  0.0f,  0.0f,  1.0f}
        }
    };*/

    Matrix4 result = {};
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            result.rows[i][j] = (i == j) ? value : 0.0f;
        }
    }

    result.rows[MAT4_ROWS - 1][MAT4_COLS - 1] = 1.0f;
    return result;
}

Matrix4 Matrix4::identity() const
{
    return value(1.0f);
}

Matrix4 Matrix4::transpose() const
{
    /* Matrix4 result =  {
        .rows = {
                {rows[0][0], rows[1][0], rows[2][0], rows[3][0]},
                {rows[0][1], rows[1][1], rows[2][1], rows[3][1]},
                {rows[0][2], rows[1][2], rows[2][2], rows[3][2]},
                {rows[0][3], rows[1][3], rows[2][3], rows[3][3]}
        }
    }; */

    Matrix4 result = {};
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            result.rows[i][j] = rows[j][i];
        }
    }
    return result;
}

Matrix4 Matrix4::copy()
{
    Matrix4 result = {};
    safe_memcpy(&result, this);
    return result;
}

static inline float degrees_to_radians(float degrees)
{
    return degrees * (PI / 180.0f);
}

Matrix4 Matrix4::rotate_x(float degrees)
{
    float c = std::cosf(degrees_to_radians(degrees));
    float s = std::sinf(degrees_to_radians(degrees));

    if (std::fabsf(c) < EPSILON) c = 0.0f;
    if (std::fabsf(s) < EPSILON) s = 0.0f;
    this->identity();
    this->setElement(1, 1, c);
    this->setElement(1, 2, -s);
    this->setElement(2, 1, s);
    this->setElement(2, 2, c);
    return *this;
}

Matrix4 Matrix4::rotate_y(float degrees)
{
    float c = std::cosf(degrees_to_radians(degrees));
    float s = std::sinf(degrees_to_radians(degrees));

    if (std::fabsf(c) < EPSILON) c = 0.0f;
    if (std::fabsf(s) < EPSILON) s = 0.0f;
    this->identity();
    this->setElement(0, 0, c);
    this->setElement(0, 2, s);
    this->setElement(2, 0, -s);
    this->setElement(2, 2, c);
    return *this;
}

Matrix4 Matrix4::rotate_z(float degrees)
{
    float c = std::cosf(degrees_to_radians(degrees));
    float s = std::sinf(degrees_to_radians(degrees));

    if (std::fabsf(c) < EPSILON) c = 0.0f;
    if (std::fabsf(s) < EPSILON) s = 0.0f;
    this->identity();
    this->setElement(0, 0, c);
    this->setElement(0, 1, -s);
    this->setElement(1, 0, s);
    this->setElement(1, 1, c);
    return *this;
}


// Vector4 v4_from_v3(Vector3 vec3)
// {
//     return v4_init(vec3.x, vec3.y, vec3.z, 1.0f);
// }

// Vector3 v3_from_v4(Vector4 vec4)
// {
//     return v3_init(vec4.x, vec4.y, vec4.z);
// }

// Vector4 mv4_transform(Matrix4 mat_4, Vector4 vec_4)
// {
//     /* return v4_init(
//         ((mat_4.row1[0] * vec_4.x) + (mat_4.row1[1] * vec_4.y) + (mat_4.row1[2] * vec_4.z) + (mat_4.row1[3] * vec_4.w)),
//         ((mat_4.row2[0] * vec_4.x) + (mat_4.row2[1] * vec_4.y) + (mat_4.row2[2] * vec_4.z) + (mat_4.row2[3] * vec_4.w)),
//         ((mat_4.row3[0] * vec_4.x) + (mat_4.row3[1] * vec_4.y) + (mat_4.row3[2] * vec_4.z) + (mat_4.row3[3] * vec_4.w)),
//         ((mat_4.row4[0] * vec_4.x) + (mat_4.row4[1] * vec_4.y) + (mat_4.row4[2] * vec_4.z) + (mat_4.row4[3] * vec_4.w))
//     );*/

//     float v4[MAT4_ROWS] = {0};
//     for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
//         v4[i] = ((mat_4.rows[i][0] * vec_4.x) +
//                  (mat_4.rows[i][1] * vec_4.y) +
//                  (mat_4.rows[i][2] * vec_4.z) +
//                  (mat_4.rows[i][3] * vec_4.w));
//     }

//     return v4_init(v4[0], v4[1], v4[2], v4[3]);
// }

// Matrix4 mv4_translate(Vector4 vec_4)
// {
//     // NOTE: We Only Translate points
//     Matrix4 result = {
//         .rows = {
//                 {1.0f, 0.0f, 0.0f, vec_4.x},
//                 {0.0f, 1.0f, 0.0f, vec_4.y},
//                 {0.0f, 0.0f, 1.0f, vec_4.z},
//                 {0.0f, 0.0f, 0.0f, 1.0f}
//         }
//     };
//     return result;
// }

// Vector3 to_screen_coords(Vector3 vec3, uint32_t screen_width, uint32_t screen_height)
// {
//     Vector4 vec4 = v4_from_v3(vec3);
//     float x = screen_width / 2.0f;
//     float y = screen_height / 2.0f;

//     Matrix4 ModelMatrix = {
//         .rows = {
//             {x,    0.0f, 0.0f,    x},
//             {0.0f,   -y, 0.0f,    y},
//             {0.0f, 0.0f, 1.0f, 0.0f},
//             {0.0f, 0.0f, 0.0f, 1.0f}
//         }
//     };

//     Vector4 TransformedVec4 = mv4_transform(ModelMatrix, vec4);
//     return v3_from_v4(TransformedVec4);
// }

// Vector3 to_world_coords(Vector3 vec3, uint32_t screen_width, uint32_t screen_height)
// {
//     Vector4 vec4 = v4_from_v3(vec3);
//     float x = 2.0f / screen_width;
//     float y = 2.0f / screen_height;

//     Matrix4 ModelMatrix = {
//         .rows = {
//             {x,    0.0f, 0.0f,    -1},
//             {0.0f,    y, 0.0f,    -1},
//             {0.0f, 0.0f, 1.0f, 0.0f},
//             {0.0f, 0.0f, 0.0f, 1.0f}
//         }
//     };

//     Vector4 TransformedVec4 = mv4_transform(ModelMatrix, vec4);
//     return v3_from_v4(TransformedVec4);
// }
