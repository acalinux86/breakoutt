#include "../util/math_util.h"
#include "../util/array.h"

#include <assert.h>

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
    assert(Test.getX() == 10.0f);
    assert(Test.getY() == 20.0f);
    assert(Test.getZ() == 30.0f);
}

void TestVector3GetX(void)
{
    float x = 10.0f;
    float y = 20.0f;
    float z = 30.0f;
    Vector3 Test(x, y, z);
    assert(Test.getX() == 10.0f);
}

void TestVector3GetY(void)
{
    float x = 10.0f;
    float y = 20.0f;
    float z = 30.0f;
    Vector3 Test(x, y, z);
    assert(Test.getY() == 20.0f);
}

void TestVector3GetZ(void)
{
    float x = 10.0f;
    float y = 20.0f;
    float z = 30.0f;
    Vector3 Test(x, y, z);
    assert(Test.getZ() == 30.0f);
}

void TestVector3Add(void)
{
    Vector3 TestVector3A(10.55f, 20.55f, 30.55f);
    Vector3 TestVector3B(20.55f, 30.55f, 40.55f);

    Vector3 TestVector3C = TestVector3A + TestVector3B;
    float x = TestVector3C.getX();
    float y = TestVector3C.getY();
    float z = TestVector3C.getZ();

    const float epsilion = 1e-5f;
    assert(fabs(x - 31.10f) < epsilion);
    assert(fabs(y - 51.10f) < epsilion);
    assert(fabs(z - 71.10f) < epsilion);
}

void TestVector3Sub(void)
{
    Vector3 TestVector3A(10.55f, 50.55f, 70.00f);
    Vector3 TestVector3B(20.55f, 30.55f, 60.00f);

    Vector3 TestVector3C = TestVector3A - TestVector3B;
    float x = TestVector3C.getX();
    float y = TestVector3C.getY();
    float z = TestVector3C.getZ();
    const float epsilion = 1e-5f;
    assert(fabs(x - -10.00f) < epsilion);
    assert(fabs(y -  20.00f) < epsilion);
    assert(fabs(z -  10.00f) < epsilion);
}

void TestVector3Mult(void)
{
    Vector3 TestVector3A(5.5f, 6.57f, 9.56f);
    Vector3 TestVector3B(2.3f, 7.98f, 10.87f);

    float TestVector3C = TestVector3A * TestVector3B;
    float expected = (5.5f * 2.3f) + (6.57f * 7.98f) + (9.56f*10.87f);
    assert(TestVector3C == expected);
}

void TestVectorScale(void)
{
    Vector3 TestVector3A(5.5f, 6.57f, 1.21f);
    const float scalar = 10.0f;
    Vector3 TestVector3C = TestVector3A * scalar;
    float x = 5.5f * 10.0f;
    float y = 6.57f * 10.0f;
    float z = 1.21f * 10.0f;
    assert(TestVector3C.getX() == x);
    assert(TestVector3C.getY() == y);
    assert(TestVector3C.getZ() == z);
}

void TestVector3Cross(void)
{
    const float epsilion = 1e-4;
    // Test case 1: Basic orthogonal vectors
    Vector3 a(1.0f, 0.0f, 0.0f);
    Vector3 b(0.0f, 1.0f, 0.0f);
    Vector3 cross = a.cross(b);
    assert(fabs(cross.getX() - 0.0f) < epsilion);
    assert(fabs(cross.getY() - 0.0f) < epsilion);
    assert(fabs(cross.getZ() - 1.0f) < epsilion);

    // Test case 2: Another simple case
    Vector3 c(2.0f, 3.0f, 4.0f);
    Vector3 d(5.0f, 6.0f, 7.0f);
    Vector3 cross2 = c.cross(d);
    assert(fabs(cross2.getX() - (-3.0f)) < epsilion);  // 3*7 - 4*6 = -3
    assert(fabs(cross2.getY() - 6.0f) < epsilion);     // 4*5 - 2*7 = 6
    assert(fabs(cross2.getZ() - (-3.0f)) < epsilion);  // 2*6 - 3*5 = -3

    // Test case 3: Cross product with itself should be zero
    Vector3 e(1.0f, 2.0f, 3.0f);
    Vector3 cross3 = e.cross(e);

    assert(fabs(cross3.getX()) < epsilion);
    assert(fabs(cross3.getY()) < epsilion);
    assert(fabs(cross3.getZ()) < epsilion);

    // Test case 4: Anti-commutative property (a × b = -b × a)
    Vector3 f(1.0f, 2.0f, 3.0f);
    Vector3 g(4.0f, 5.0f, 6.0f);
    Vector3 cross_fg = f.cross(g);
    Vector3 cross_gf = g.cross(f);

    assert(fabs(cross_fg.getX() + cross_gf.getX()) < epsilion);
    assert(fabs(cross_fg.getY() + cross_gf.getY()) < epsilion);
    assert(fabs(cross_fg.getZ() + cross_gf.getZ()) < epsilion);
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
    const float epsilion = 1e-5;
    assert(fabs(TestVector3ANormalized.getX() - ExpectedX) < epsilion);
    assert(fabs(TestVector3ANormalized.getY() - ExpectedY) < epsilion);
    assert(fabs(TestVector3ANormalized.getZ() - ExpectedZ) < epsilion);
}

typedef ARRAY(TestCaseVector3) TestCases;
void RunAllTestCases(const TestCases *Tests)
{
    for (uint32_t i = 0; i < Tests->count; ++i) {
        Tests->items[i].RunTestCase();
    }
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
