#include "../util/math_util.h"
#include "../util/array.h"

#include <assert.h>

struct TestCaseVector4 {
public:
    TestCaseVector4(const char *Name, void (*Fn)(void));
    void RunTestCase();
private:
    const char *Vector4FunctionName;
    void (*TestVector4Function)(void);
};

TestCaseVector4::TestCaseVector4(const char *Name, void (*Fn)(void)):
    Vector4FunctionName(Name), TestVector4Function(Fn) {}

void TestCaseVector4::RunTestCase()
{
    TestVector4Function();
    printf("INFO: TestCase \"%s\" passed.\n", Vector4FunctionName);
}

void TestVector4Constructor(void)
{
    {
        float x = 10.0f;
        float y = 20.0f;
        float z = 30.0f;
        Vector4 Test(x, y, z, Vector4Type::Point);
        assert(Test.getX() == 10.0f);
        assert(Test.getY() == 20.0f);
        assert(Test.getZ() == 30.0f);
        assert(Test.getW() == 1.0f);
    }

    {
        float x = 10.0f;
        float y = 20.0f;
        float z = 30.0f;
        Vector4 Test(x, y, z, Vector4Type::Direction);
        assert(Test.getX() == 10.0f);
        assert(Test.getY() == 20.0f);
        assert(Test.getZ() == 30.0f);
        assert(Test.getW() == 0.0f);
    }
}

void TestVector4GetX(void)
{
    float x = 10.0f;
    float y = 20.0f;
    float z = 30.0f;
    Vector4 Test(x, y, z, Vector4Type::Direction);
    assert(Test.getX() == 10.0f);
}

void TestVector4GetY(void)
{
    float x = 10.0f;
    float y = 20.0f;
    float z = 30.0f;
    Vector4 Test(x, y, z, Vector4Type::Direction);
    assert(Test.getY() == 20.0f);
}

void TestVector4GetZ(void)
{
    float x = 10.0f;
    float y = 20.0f;
    float z = 30.0f;
    Vector4 Test(x, y, z, Vector4Type::Direction);
    assert(Test.getZ() == 30.0f);
}

void TestVector4GetW(void)
{
    {
        float x = 10.0f;
        float y = 20.0f;
        float z = 30.0f;
        Vector4 Test(x, y, z, Vector4Type::Direction);
        assert(Test.getW() == 0.0f);
    }
    {
        float x = 10.0f;
        float y = 20.0f;
        float z = 30.0f;
        Vector4 Test(x, y, z, Vector4Type::Point);
        assert(Test.getW() == 1.0f);
    }
}

void TestVector4Add(void)
{
    Vector4 TestVector4A(10.55f, 20.55f, 30.55f, Vector4Type::Direction);
    Vector4 TestVector4B(20.55f, 30.55f, 40.55f, Vector4Type::Direction);

    Vector4 TestVector4C = TestVector4A + TestVector4B;
    float x = TestVector4C.getX();
    float y = TestVector4C.getY();
    float z = TestVector4C.getZ();
    float w = TestVector4C.getW();

    assert(floatEqual(x , 31.10f));
    assert(floatEqual(y , 51.10f));
    assert(floatEqual(z , 71.10f));
    assert(w == 0.0f);
}

void TestVector4Sub(void)
{
    Vector4 TestVector4A(10.55f, 50.55f, 70.00f, Vector4Type::Point);
    Vector4 TestVector4B(20.55f, 30.55f, 60.00f, Vector4Type::Point);

    Vector4 TestVector4C = TestVector4A - TestVector4B;
    float x = TestVector4C.getX();
    float y = TestVector4C.getY();
    float z = TestVector4C.getZ();
    float w = TestVector4C.getW();

    assert(floatEqual(x , -10.00f));
    assert(floatEqual(y ,  20.00f));
    assert(floatEqual(z ,  10.00f));
    assert(w == 0.0f);
}

void TestVector4Mult(void)
{
    Vector4 TestVector4A(5.5f, 6.57f, 9.56f, Vector4Type::Direction);
    Vector4 TestVector4B(2.3f, 7.98f, 10.87f, Vector4Type::Direction);

    float TestVector4C = TestVector4A * TestVector4B;
    float expected = (5.5f * 2.3f) + (6.57f * 7.98f) + (9.56f*10.87f);
    assert(TestVector4C == expected);
}

void TestVectorScale(void)
{
    Vector4 TestVector4A(5.5f, 6.57f, 1.21f, Vector4Type::Direction);
    const float scalar = 10.0f;
    Vector4 TestVector4C = TestVector4A * scalar;
    float x = 5.5f * 10.0f;
    float y = 6.57f * 10.0f;
    float z = 1.21f * 10.0f;
    assert(TestVector4C.getX() == x);
    assert(TestVector4C.getY() == y);
    assert(TestVector4C.getZ() == z);
    assert(TestVector4C.getW() == 0.0f);

}

void TestVector4Cross(void)
{
    // Test case 1: Basic orthogonal vectors
    Vector4 a(1.0f, 0.0f, 0.0f, Vector4Type::Direction);
    Vector4 b(0.0f, 1.0f, 0.0f, Vector4Type::Direction);
    Vector4 cross = a.cross(b);
    assert(floatEqual(cross.getX() , 0.0f));
    assert(floatEqual(cross.getY() , 0.0f));
           assert(floatEqual(cross.getZ() , 1.0f));

    // Test case 2: Another simple case
    Vector4 c(2.0f, 3.0f, 4.0f, Vector4Type::Direction);
    Vector4 d(5.0f, 6.0f, 7.0f, Vector4Type::Direction);
    Vector4 cross2 = c.cross(d);
    assert(floatEqual(cross2.getX() , -3.0f));  // 3*7 , 4*6 = -3
    assert(floatEqual(cross2.getY() , 6.0f));     // 4*5 , 2*7 = 6
    assert(floatEqual(cross2.getZ() , -3.0f));  // 2*6 , 3*5 = -3

    // Test case 3: Cross product with itself should be zero
    Vector4 e(1.0f, 2.0f, 3.0f, Vector4Type::Direction);
    Vector4 cross3 = e.cross(e);

    assert(floatEqual(cross3.getX(), 0.0f));
    assert(floatEqual(cross3.getY(), 0.0f));
    assert(floatEqual(cross3.getZ(), 0.0f));

    // Test case 4: Anti-commutative property (a × b = -b × a)
    Vector4 f(1.0f, 2.0f, 3.0f, Vector4Type::Direction);
    Vector4 g(4.0f, 5.0f, 6.0f, Vector4Type::Direction);
    Vector4 cross_fg = f.cross(g);
    Vector4 cross_gf = g.cross(f);

    assert(floatEqual(cross_fg.getX(), -cross_gf.getX()));
    assert(floatEqual(cross_fg.getY(), -cross_gf.getY()));
    assert(floatEqual(cross_fg.getZ(), -cross_gf.getZ()));
}

void TestVector4Length(void)
{
    Vector4 TestVector4A(1.0f, 4.0f, 8.0f, Vector4Type::Direction);
    float TestVector4ALength = TestVector4A.length();
    assert(TestVector4ALength == 9.0f);
}

void TestVector4Normalize(void)
{
    Vector4 TestVector4A(1.0f, 4.0f, 8.0f, Vector4Type::Direction);
    Vector4 TestVector4ANormalized = TestVector4A.normalize();
    float   TestVector4ALength = TestVector4A.length();
    float ExpectedX = 1.0f / TestVector4ALength;
    float ExpectedY = 4.0f / TestVector4ALength;
    float ExpectedZ = 8.0f / TestVector4ALength;

    assert(floatEqual(TestVector4ANormalized.getX() , ExpectedX));
    assert(floatEqual(TestVector4ANormalized.getY() , ExpectedY));
    assert(floatEqual(TestVector4ANormalized.getZ() , ExpectedZ));
}

void TestVector4Equal(void)
{
    {
        Vector4 TestVector4A(1.0f, 2.0f, 3.0f, Vector4Type::Point);
        Vector4 TestVector4B(3.0f, 2.0f, 1.0f, Vector4Type::Direction);
        assert(TestVector4A != TestVector4B);
    }
    {
        Vector4 TestVector4A(1.0f, 2.0f, 3.0f, Vector4Type::Point);
        Vector4 TestVector4B(1.0f, 2.0f, 1.0f, Vector4Type::Direction);
        assert(TestVector4A != TestVector4B);
    }
    {
        Vector4 TestVector4A(1.0f, 2.0f, 3.0f, Vector4Type::Point);
        Vector4 TestVector4B(1.0f, 2.0f, 3.0f, Vector4Type::Point);
        assert(TestVector4A == TestVector4B);
    }
}

void TestVector4PerspectiveDivide()
{
    // Case 1: w == 0 → should return unchanged vector
    {
        Vector4 v(4.0f, 8.0f, 12.0f, Vector4Type::Direction); // Direct w constructor
        Vector4 result = v.perspective_divide();

        assert(floatEqual(result.getX() , 4.0f));
        assert(floatEqual(result.getY() , 8.0f));
        assert(floatEqual(result.getZ() , 12.0f));
        assert(floatEqual(result.getW() , 0.0f));
    }

    // Case 2: w != 0 → should divide x, y, z by w and set type to Point
    {
        Vector4 v(10.0f, 20.0f, 30.0f, 10.0f);
        Vector4 result = v.perspective_divide();

        assert(floatEqual(result.getX() , 1.0f));
        assert(floatEqual(result.getY() , 2.0f));
        assert(floatEqual(result.getZ() , 3.0f));
        assert(result.getType() == Vector4Type::Point);
    }

    // Case 3: w != 1 but not zero (more general test)
    {
        Vector4 v(6.0f, 9.0f, 12.0f, 3.0f);
        Vector4 result = v.perspective_divide();

        assert(floatEqual(result.getX() , 2.0f));
        assert(floatEqual(result.getY() , 3.0f));
        assert(floatEqual(result.getZ() , 4.0f));
        assert(result.getType() == Vector4Type::Point);
    }
}

typedef ARRAY(TestCaseVector4) TestCases;
void RunAllTestCases(const TestCases *Tests)
{
    for (uint32_t i = 0; i < Tests->count; ++i) {
        Tests->items[i].RunTestCase();
    }
    printf("SUCCESS: All %u Test cases Passed\n", Tests->count);
}

int main(void)
{
    TestCases Tests = {nullptr, 0, 0};
    array_new(&Tests, TestCaseVector4);

    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4Constructor", TestVector4Constructor));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4GetX", TestVector4GetX));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4GetY", TestVector4GetY));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4GetZ", TestVector4GetZ));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4GetW", TestVector4GetW));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4Add",  TestVector4Add));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4Sub",  TestVector4Sub));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4Mult",  TestVector4Mult));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVectorScale", TestVectorScale));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4Cross", TestVector4Cross));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4Length", TestVector4Length));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4Normalize", TestVector4Normalize));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4Equal", TestVector4Equal));
    array_append(TestCaseVector4, &Tests, TestCaseVector4("TestVector4PerspectiveDivide", TestVector4PerspectiveDivide));
    RunAllTestCases(&Tests);
    return 0;
}
