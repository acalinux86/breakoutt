#include "../util/math_util.hpp"
#include "../util/array.h"

#include <cassert>

struct TestCaseVector2 {
public:
    TestCaseVector2(const char *Name, void (*Fn)(void));
    void RunTestCase();
private:
    const char *Vector2FunctionName;
    void (*TestVector2Function)(void);
};

TestCaseVector2::TestCaseVector2(const char *Name, void (*Fn)(void)):
    Vector2FunctionName(Name), TestVector2Function(Fn) {}

void TestCaseVector2::RunTestCase()
{
    TestVector2Function();
    printf("INFO: TestCase \"%s\" passed.\n", Vector2FunctionName);
}

void TestVector2Constructor(void)
{
    float x = 10.0f;
    float y = 20.0f;
    Vector2 Test(x, y);
    assert(floatEqual(Test.getX(), x));
    assert(floatEqual(Test.getY(), y));
}

void TestVector2GetX(void)
{
    float x = 10.0f;
    float y = 20.0f;
    Vector2 Test(x, y);
    assert(floatEqual(Test.getX() , x));
}

void TestVector2GetY(void)
{
    float x = 10.0f;
    float y = 20.0f;
    Vector2 Test(x, y);
    assert(floatEqual(Test.getY(), y));
}

void TestVector2Add(void)
{
    Vector2 TestVector2A(10.55f, 20.55f);
    Vector2 TestVector2B(20.55f, 30.55f);

    Vector2 TestVector2C = TestVector2A + TestVector2B;
    float x = TestVector2C.getX();
    float y = TestVector2C.getY();
    assert(floatEqual(x , 31.10f));
    assert(floatEqual(y , 51.10f));
}

void TestVector2Sub(void)
{
    Vector2 TestVector2A(10.55f, 50.55f);
    Vector2 TestVector2B(20.55f, 30.55f);

    Vector2 TestVector2C = TestVector2A - TestVector2B;
    float x = TestVector2C.getX();
    float y = TestVector2C.getY();
    assert(floatEqual(x , -10.00f));
    assert(floatEqual(y ,  20.00f));
}

void TestVector2Mult(void)
{
    Vector2 TestVector2A(5.5f, 6.57f);
    Vector2 TestVector2B(2.3f, 7.98f);

    float TestVector2C = TestVector2A * TestVector2B;
    float expected = (5.5f * 2.3f) + (6.57f * 7.98f);
    assert(floatEqual(TestVector2C , expected));
}

void TestVectorScale(void)
{
    Vector2 TestVector2A(5.5f, 6.57f);

    const float scalar = 10.0f;
    Vector2 TestVector2C = TestVector2A * scalar;
    float x = 5.5f * 10.0f;
    float y = 6.57f * 10.0f;
    assert(floatEqual(TestVector2C.getX(), x));
    assert(floatEqual(TestVector2C.getY(), y));
}

void TestVector2Length(void)
{
    Vector2 TestVector2A(6.0f, 8.0f);
    float TestVector2ALength = TestVector2A.length();
    assert(floatEqual(TestVector2ALength , 10.0f));
}

void TestVector2Normalize(void)
{
    Vector2 TestVector2A(4.0f, 8.0f);
    Vector2 TestVector2ANormalized = TestVector2A.normalize();
    float   TestVector2ALength = TestVector2A.length();
    float ExpectedX = 4.0f / TestVector2ALength;
    float ExpectedY = 8.0f / TestVector2ALength;
    assert(floatEqual(TestVector2ANormalized.getX() , ExpectedX));
    assert(floatEqual(TestVector2ANormalized.getY() , ExpectedY));
}

typedef ARRAY(TestCaseVector2) TestCases;
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
    array_new(&Tests, TestCaseVector2);

    array_append(TestCaseVector2, &Tests, TestCaseVector2("TestVector2Constructor", TestVector2Constructor));
    array_append(TestCaseVector2, &Tests, TestCaseVector2("TestVector2GetX", TestVector2GetX));
    array_append(TestCaseVector2, &Tests, TestCaseVector2("TestVector2GetY", TestVector2GetY));
    array_append(TestCaseVector2, &Tests, TestCaseVector2("TestVector2Add",  TestVector2Add));
    array_append(TestCaseVector2, &Tests, TestCaseVector2("TestVector2Sub",  TestVector2Sub));
    array_append(TestCaseVector2, &Tests, TestCaseVector2("TestVector2Mult",  TestVector2Mult));
    array_append(TestCaseVector2, &Tests, TestCaseVector2("TestVectorScale", TestVectorScale));
    array_append(TestCaseVector2, &Tests, TestCaseVector2("TestVector2Length", TestVector2Length));
    array_append(TestCaseVector2, &Tests, TestCaseVector2("TestVector2Normalize", TestVector2Normalize));

    RunAllTestCases(&Tests);
    return 0;
}
