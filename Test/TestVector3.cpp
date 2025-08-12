#include "../util/math_util.hpp"
#include "../util/array.h"

#include <cassert>

struct TestCaseVector3 {
public:
    TestCaseVector3(const char *Name, void (*Fn)(void));
    void RunTestCase();
private:
    const char *Vector3FunctionName;
    void (*TestVector3Function)(void);
};

TestCaseVector3::TestCaseVector3(const char *Name, void (*Fn)(void)):
    Vector3FunctionName(Name), TestVector3Function(Fn) {}

void TestCaseVector3::RunTestCase()
{
    TestVector3Function();
    printf("INFO: TestCase \"%s\" passed.\n", Vector3FunctionName);
}

void TestVector3Constructor(void)
{
    float x = 10.0f;
    float y = 20.0f;
    float z = 30.0f;
    Vector3 Test(x, y, z);
    assert(floatEqual(Test.getX(), 10.0f));
    assert(floatEqual(Test.getY(), 20.0f));
    assert(floatEqual(Test.getZ(), 30.0f));
}

void TestVector3GetX(void)
{
    float x = 10.0f;
    float y = 20.0f;
    float z = 30.0f;
    Vector3 Test(x, y, z);
    assert(floatEqual(Test.getX(), 10.0f));
}

void TestVector3GetY(void)
{
    float x = 10.0f;
    float y = 20.0f;
    float z = 30.0f;
    Vector3 Test(x, y, z);
    assert(floatEqual(Test.getY(), 20.0f));
}

void TestVector3GetZ(void)
{
    float x = 10.0f;
    float y = 20.0f;
    float z = 30.0f;
    Vector3 Test(x, y, z);
    assert(floatEqual(Test.getZ(), 30.0f));
}

void TestVector3Add(void)
{
    Vector3 TestVector3A(10.55f, 20.55f, 30.55f);
    Vector3 TestVector3B(20.55f, 30.55f, 40.55f);

    Vector3 TestVector3C = TestVector3A + TestVector3B;
    float x = TestVector3C.getX();
    float y = TestVector3C.getY();
    float z = TestVector3C.getZ();

    assert(floatEqual(x , 31.10f));
    assert(floatEqual(y , 51.10f));
    assert(floatEqual(z , 71.10f));
}

void TestVector3Sub(void)
{
    Vector3 TestVector3A(10.55f, 50.55f, 70.00f);
    Vector3 TestVector3B(20.55f, 30.55f, 60.00f);

    Vector3 TestVector3C = TestVector3A - TestVector3B;
    float x = TestVector3C.getX();
    float y = TestVector3C.getY();
    float z = TestVector3C.getZ();
    assert(floatEqual(x , -10.00f));
    assert(floatEqual(y ,  20.00f));
    assert(floatEqual(z ,  10.00f));
}

void TestVector3Mult(void)
{
    Vector3 TestVector3A(5.5f, 6.57f, 9.56f);
    Vector3 TestVector3B(2.3f, 7.98f, 10.87f);

    float TestVector3C = TestVector3A * TestVector3B;
    float expected = (5.5f * 2.3f) + (6.57f * 7.98f) + (9.56f*10.87f);
    assert(floatEqual(TestVector3C, expected));
}

void TestVectorScale(void)
{
    Vector3 TestVector3A(5.5f, 6.57f, 1.21f);
    const float scalar = 10.0f;
    Vector3 TestVector3C = TestVector3A * scalar;
    float x = 5.5f * 10.0f;
    float y = 6.57f * 10.0f;
    float z = 1.21f * 10.0f;
    assert(floatEqual(TestVector3C.getX() , x));
    assert(floatEqual(TestVector3C.getY() , y));
    assert(floatEqual(TestVector3C.getZ() , z));
}

void TestVector3Cross(void)
{
    // Test case 1: Basic orthogonal vectors
    Vector3 a(1.0f, 0.0f, 0.0f);
    Vector3 b(0.0f, 1.0f, 0.0f);
    Vector3 cross = a.cross(b);
    assert(floatEqual(cross.getX() , 0.0f));
    assert(floatEqual(cross.getY() , 0.0f));
    assert(floatEqual(cross.getZ() , 1.0f));

    // Test case 2: Another simple case
    Vector3 c(2.0f, 3.0f, 4.0f);
    Vector3 d(5.0f, 6.0f, 7.0f);
    Vector3 cross2 = c.cross(d);

    assert(floatEqual(cross2.getX() , -3.0f));  // 3*7 , 4*6 = -3
    assert(floatEqual(cross2.getY() , 6.0f));     // 4*5 , 2*7 = 6
    assert(floatEqual(cross2.getZ() , -3.0f));  // 2*6 , 3*5 = -3

    // Test case 3: Cross product with itself should be zero
    Vector3 e(1.0f, 2.0f, 3.0f);
    Vector3 cross3 = e.cross(e);

    assert(floatEqual(cross3.getX(), 0.0f));
    assert(floatEqual(cross3.getY(), 0.0f));
    assert(floatEqual(cross3.getZ(), 0.0f));

    // Test case 4: Anti-commutative property (a × b = -b × a)
    Vector3 f(1.0f, 2.0f, 3.0f);
    Vector3 g(4.0f, 5.0f, 6.0f);
    Vector3 cross_fg = f.cross(g);
    Vector3 cross_gf = g.cross(f);

    assert(floatEqual(cross_fg.getX() , -cross_gf.getX()));
    assert(floatEqual(cross_fg.getY() , -cross_gf.getY()));
    assert(floatEqual(cross_fg.getZ() , -cross_gf.getZ()));
}

void TestVector3Length(void)
{
    Vector3 TestVector3A(1.0f, 4.0f, 8.0f);
    float TestVector3ALength = TestVector3A.length();
    assert(TestVector3ALength == 9.0f);
}

void TestVector3Normalize(void)
{
    Vector3 TestVector3A(1.0f, 4.0f, 8.0f);
    Vector3 TestVector3ANormalized = TestVector3A.normalize();
    float   TestVector3ALength = TestVector3A.length();
    float ExpectedX = 1.0f / TestVector3ALength;
    float ExpectedY = 4.0f / TestVector3ALength;
    float ExpectedZ = 8.0f / TestVector3ALength;
    assert(floatEqual(TestVector3ANormalized.getX() , ExpectedX));
    assert(floatEqual(TestVector3ANormalized.getY() , ExpectedY));
    assert(floatEqual(TestVector3ANormalized.getZ() , ExpectedZ));
}

typedef ARRAY(TestCaseVector3) TestCases;
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
    array_new(&Tests, TestCaseVector3);

    array_append(TestCaseVector3, &Tests, TestCaseVector3("TestVector3Constructor", TestVector3Constructor));
    array_append(TestCaseVector3, &Tests, TestCaseVector3("TestVector3GetX", TestVector3GetX));
    array_append(TestCaseVector3, &Tests, TestCaseVector3("TestVector3GetY", TestVector3GetY));
    array_append(TestCaseVector3, &Tests, TestCaseVector3("TestVector3GetZ", TestVector3GetZ));
    array_append(TestCaseVector3, &Tests, TestCaseVector3("TestVector3Add",  TestVector3Add));
    array_append(TestCaseVector3, &Tests, TestCaseVector3("TestVector3Sub",  TestVector3Sub));
    array_append(TestCaseVector3, &Tests, TestCaseVector3("TestVector3Mult",  TestVector3Mult));
    array_append(TestCaseVector3, &Tests, TestCaseVector3("TestVectorScale", TestVectorScale));
    array_append(TestCaseVector3, &Tests, TestCaseVector3("TestVector3Cross", TestVector3Cross));
    array_append(TestCaseVector3, &Tests, TestCaseVector3("TestVector3Length", TestVector3Length));
    array_append(TestCaseVector3, &Tests, TestCaseVector3("TestVector3Normalize", TestVector3Normalize));
    RunAllTestCases(&Tests);
    return 0;
}
