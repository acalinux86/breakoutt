#include "../util/math_util.h"
#include "../util/array.h"

#include <assert.h>

struct TestCaseMatrix4 {
public:
    TestCaseMatrix4(const char *Name, void (*Fn)(void));
    void RunTestCase();
private:
    const char *Matrix4FunctionName;
    void (*TestMatrix4Function)(void);
};

TestCaseMatrix4::TestCaseMatrix4(const char *Name, void (*Fn)(void)):
    Matrix4FunctionName(Name), TestMatrix4Function(Fn) {}

void TestCaseMatrix4::RunTestCase()
{
    TestMatrix4Function();
    printf("INFO: TestCase \"%s\" passed.\n", Matrix4FunctionName);
}

// Done:
// float getElement(uint32_t row, uint32_t col) const;
// void  setElement(uint32_t row, uint32_t col, float element) const;
// Matrix4 operator+(const Matrix4& other) const;
// Matrix4 operator-(const Matrix4& other) const;
// Matrix4 operator*(const Matrix4& other) const;

// Remaining:
// Matrix4 value(float value) const;
// Matrix4 identity() const;
// Matrix4 transpose() const;
// Matrix4 copy() const;
// Matrix4 rotate_x(float degrees) const;
// Matrix4 rotate_y(float degrees) const;
// Matrix4 rotate_z(float degrees) const;

void TestMatrix4GetElement(void)
{
    {
        Matrix4 TestMatrix4A = {};
        float element = TestMatrix4A.getElement(3, 3);
        assert(element == 0.00f);
    }
    {
        Matrix4 TestMatrix4A = {};
        TestMatrix4A = TestMatrix4A.identity();
        float TestA = TestMatrix4A.getElement(3, 3);
        float TestB = TestMatrix4A.getElement(3, 2);
        assert(TestA == 1.00f);
        assert(TestB == 0.00f);
    }
}

void TestMatrix4SetElement(void)
{
    {
        Matrix4 TestMatrix4A = {};
        TestMatrix4A.setElement(3, 1, 10.56f);
        float element = TestMatrix4A.getElement(3, 1);
        assert(element == 10.56f);
    }
    {
        Matrix4 TestMatrix4A = {};
        TestMatrix4A = TestMatrix4A.identity().setElement(3, 3, 100.0f).setElement(3, 2, 70.0f);
        float TestA = TestMatrix4A.getElement(3, 3);
        float TestB = TestMatrix4A.getElement(3, 2);
        assert(TestA == 100.00f);
        assert(TestB == 70.00f);
    }
}

void TestMatrix4Add(void)
{
    {
        Matrix4 TestMatrix4A = {};
        Matrix4 TestMatrix4B = {};

        TestMatrix4A = TestMatrix4A.identity();
        TestMatrix4B = TestMatrix4B.identity();

        Matrix4 TestMatrixC = TestMatrix4A + TestMatrix4B;
        float TestLast = TestMatrixC.getElement(3, 3);
        float TestFirst = TestMatrixC.getElement(0, 0);
        assert(TestLast == 2.00f);
        assert(TestFirst == 2.00f);
    }
    {
        Matrix4 TestMatrix4A = {};
        Matrix4 TestMatrix4B = {};

        TestMatrix4A = TestMatrix4A.identity().setElement(3, 2, 50.0f).setElement(1, 3, 53.0f);
        TestMatrix4B = TestMatrix4B.identity().setElement(3, 2, 100.0f).setElement(1, 3, 14.0f);

        Matrix4 TestMatrix4C = TestMatrix4A + TestMatrix4B;
        float TestA = TestMatrix4C.getElement(3, 2);
        float TestB = TestMatrix4C.getElement(1, 3);
        float TestC = TestMatrix4C.getElement(1, 1);
        assert(TestA == 150.00f);
        assert(TestB == 67.00f);
        assert(TestC == 2.00f);
    }
}

void TestMatrix4Sub(void)
{
    {
        Matrix4 TestMatrix4A = {};
        Matrix4 TestMatrix4B = {};

        TestMatrix4A = TestMatrix4A.identity();
        TestMatrix4B = TestMatrix4B.identity();

        Matrix4 TestMatrixC = TestMatrix4A - TestMatrix4B;
        float TestLast = TestMatrixC.getElement(3, 3);
        float TestFirst = TestMatrixC.getElement(0, 0);
        assert(TestLast == 0.00f);
        assert(TestFirst == 0.00f);
    }
    {
        Matrix4 TestMatrix4A = {};
        Matrix4 TestMatrix4B = {};

        TestMatrix4A = TestMatrix4A.identity().setElement(3, 2, 50.0f).setElement(1, 3, 53.0f);
        TestMatrix4B = TestMatrix4B.identity().setElement(1, 3, 14.0f).setElement(3, 2, 100.0f);;

        Matrix4 TestMatrix4C = TestMatrix4A - TestMatrix4B;
        float TestA = TestMatrix4C.getElement(3, 2);
        float TestB = TestMatrix4C.getElement(1, 3);
        float TestC = TestMatrix4C.getElement(1, 1);
        assert(TestA == -50.00f);
        assert(TestB == 39.00f);
        assert(TestC == 0.00f);
    }
}

void TestMatrix4Mult(void)
{
    // 1. Identity × Identity = Identity
    {
        Matrix4 I = Matrix4().identity();
        Matrix4 II = I * I;
        for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
            for (uint32_t j = 0; j < MAT4_COLS; ++j) {
                float expected = (i == j) ? 1.0f : 0.0f;
                assert(floatEqual(II.getElement(i, j), expected));
            }
        }
    }

    // 2. Custom test: ensure specific multiplication works
    {
        // A = identity but set (1,2) = 5
        Matrix4 A = Matrix4().identity().setElement(1, 2, 5.0f);

        // B = identity but set (2,0) = 2
        Matrix4 B = Matrix4().identity().setElement(2, 0, 2.0f);

        // Expected result:
        // (1,0) = 5*2 = 10
        // (1,2) stays 5
        Matrix4 C = A * B;

        // Key modified cell
        assert(floatEqual(C.getElement(1, 0), 10.0f));

        // Original (1,2) from A should be preserved because B’s col 2 matches identity
        assert(floatEqual(C.getElement(1, 2), 5.0f));

        // Identity positions stay 1
        assert(floatEqual(C.getElement(0, 0), 1.0f));
        assert(floatEqual(C.getElement(3, 3), 1.0f));

        // Other off-diagonal positions should remain 0
        assert(floatEqual(C.getElement(0, 1), 0.0f));
        assert(floatEqual(C.getElement(2, 1), 0.0f));
    }

    // 3. Chain multiplication test (A * B * I == A * B)
    {
        Matrix4 A = Matrix4().identity().setElement(0, 1, 3.0f);
        Matrix4 B = Matrix4().identity().setElement(1, 0, 4.0f);

        Matrix4 C1 = A * B;
        Matrix4 C2 = (A * B) * Matrix4().identity();

        for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
            for (uint32_t j = 0; j < MAT4_COLS; ++j) {
                assert(floatEqual(C1.getElement(i, j), C2.getElement(i, j)));
            }
        }
    }
}

typedef ARRAY(TestCaseMatrix4) TestCases;
void RunAllTestCases(const TestCases *Tests)
{
    for (uint32_t i = 0; i < Tests->count; ++i) {
        Tests->items[i].RunTestCase();
    }
    printf("SUCESS: All %u Test cases Passed\n", Tests->count);
}

int main(void)
{
    TestCases Tests = {nullptr, 0, 0};
    array_new(&Tests, TestCaseMatrix4);

    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4GetElement", TestMatrix4GetElement));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4SetElement", TestMatrix4SetElement));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4Add", TestMatrix4Add));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4Sub", TestMatrix4Sub));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4Mult", TestMatrix4Mult));
    RunAllTestCases(&Tests);
    return 0;
}
