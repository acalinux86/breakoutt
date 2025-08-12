#include "../util/math_util.hpp"
#include "../util/array.h"

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

void TestMatrix4GetElement(void)
{
    {
        Matrix4 TestMatrix4A = {};
        float element = TestMatrix4A.getElement(3, 3);
        assert(element == 0.00f);
    }
    {
        Matrix4 TestMatrix4A = Matrix4().identity();
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
        Matrix4 TestMatrix4A = Matrix4().identity().setElement(3, 3, 100.0f).setElement(3, 2, 70.0f);
        float TestA = TestMatrix4A.getElement(3, 3);
        float TestB = TestMatrix4A.getElement(3, 2);
        assert(TestA == 100.00f);
        assert(TestB == 70.00f);
    }
}

void TestMatrix4Add(void)
{
    {
        Matrix4 TestMatrix4A = Matrix4().identity();
        Matrix4 TestMatrix4B = Matrix4().identity();

        Matrix4 TestMatrixC = TestMatrix4A + TestMatrix4B;
        float TestLast = TestMatrixC.getElement(3, 3);
        float TestFirst = TestMatrixC.getElement(0, 0);
        assert(TestLast == 2.00f);
        assert(TestFirst == 2.00f);
    }
    {
        Matrix4 TestMatrix4A = Matrix4().identity().setElement(3, 2, 50.0f).setElement(1, 3, 53.0f);
        Matrix4 TestMatrix4B = Matrix4().identity().setElement(3, 2, 100.0f).setElement(1, 3, 14.0f);

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
        Matrix4 TestMatrix4A = Matrix4().identity();
        Matrix4 TestMatrix4B = Matrix4().identity();

        Matrix4 TestMatrixC = TestMatrix4A - TestMatrix4B;
        float TestLast = TestMatrixC.getElement(3, 3);
        float TestFirst = TestMatrixC.getElement(0, 0);
        assert(TestLast == 0.00f);
        assert(TestFirst == 0.00f);
    }
    {
        Matrix4 TestMatrix4A = Matrix4().identity().setElement(3, 2, 50.0f).setElement(1, 3, 53.0f);
        Matrix4 TestMatrix4B = Matrix4().identity().setElement(1, 3, 14.0f).setElement(3, 2, 100.0f);;

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

void TestMatrix4Value(void)
{
    Matrix4 TestMatrix4A = Matrix4().value(10.0f);
    float TestOne = TestMatrix4A.getElement(0, 0);
    float TestTwo = TestMatrix4A.getElement(1, 1);
    float TestThree = TestMatrix4A.getElement(2, 2);
    float TestFour = TestMatrix4A.getElement(3, 3);
    assert(floatEqual(TestOne, 10.0f));
    assert(floatEqual(TestTwo, 10.0f));
    assert(floatEqual(TestThree, 10.0f));
    assert(floatEqual(TestFour, 1.0f));
}

void TestMatrix4Identity(void)
{
    Matrix4 Identity = Matrix4().identity();
    float TestOne = Identity.getElement(0, 0);
    float TestTwo = Identity.getElement(1, 1);
    float TestThree = Identity.getElement(2, 2);
    float TestFour = Identity.getElement(3, 3);
    assert(floatEqual(TestOne, 1.0f));
    assert(floatEqual(TestTwo, 1.0f));
    assert(floatEqual(TestThree, 1.0f));
    assert(floatEqual(TestFour, 1.0f));
}

void TestMatrixTranspose(void)
{
    // .value() places a specified value in (0,0) (1,1) (2,2) except (3,3)
    Matrix4 TestMatrixA = Matrix4().value(10.0f);
    // Transpose transposes it ;)
    TestMatrixA = TestMatrixA.setElement(1, 0, 5.0f).setElement(2, 0, 6.0f).setElement(3, 0, 7.0f).transpose();
    float TestOne = TestMatrixA.getElement(0, 0);
    float TestTwo = TestMatrixA.getElement(0, 1);
    float TestThree = TestMatrixA.getElement(0, 2);
    float TestFour = TestMatrixA.getElement(0, 3);
    assert(floatEqual(TestOne, 10.0f));
    assert(floatEqual(TestTwo, 5.0f));
    assert(floatEqual(TestThree, 6.0f));
    assert(floatEqual(TestFour, 7.0f));
}

void TestMatrix4Copy(void)
{
    Matrix4 Original = Matrix4().value(10.0f);
    Matrix4 Copy = Original.copy();
    assert(Original == Copy);
}

void TestMatrix4Scale(void)
{
    Matrix4 result = Matrix4().scale(Vector4(2.0f, 2.0f, 2.0f, Vector4Type::Point));
    float TestOne = result.getElement(0, 0);
    float TestTwo = result.getElement(1, 1);
    float TestThree = result.getElement(2, 2);
    float TestFour = result.getElement(3, 3);
    assert(floatEqual(TestOne, 2.0f));
    assert(floatEqual(TestTwo, 2.0f));
    assert(floatEqual(TestThree, 2.0f));
    assert(floatEqual(TestFour, 1.0f));
}

void TestMatrix4RotateDirection(void)
{
    {
        // Rotated 90 degrees about X
        Matrix4 RotateX = Matrix4().rotate_x(90.0f);
        Vector4 Direction = Vector4(0.0f, 2.0f, 0.0f, Vector4Type::Direction);
        Vector4 RotatedVector4 = RotateX.transform(Direction);
        // Y will go to Z
        Vector4 Expected = Vector4(0.0f, 0.0f, 2.0f, Vector4Type::Direction);
        assert(almostEqual(Expected.getX(), RotatedVector4.getX()));
        assert(almostEqual(Expected.getY(), RotatedVector4.getY()));
        assert(almostEqual(Expected.getZ(), RotatedVector4.getZ()));
        assert(almostEqual(Expected.getW(), RotatedVector4.getW()));
    }
    {
        // Rotated 90 degrees about Y
        Matrix4 RotateY = Matrix4().rotate_y(90.0f);
        Vector4 Direction = Vector4(0.0f, 0.0f, 2.0f, Vector4Type::Direction);
        Vector4 RotatedVector4 = RotateY.transform(Direction);
        // Z will go to X
        Vector4 Expected = Vector4(2.0f, 0.0f, 0.0f, Vector4Type::Direction);
        assert(almostEqual(Expected.getX(), RotatedVector4.getX()));
        assert(almostEqual(Expected.getY(), RotatedVector4.getY()));
        assert(almostEqual(Expected.getZ(), RotatedVector4.getZ()));
        assert(almostEqual(Expected.getW(), RotatedVector4.getW()));
    }
    {
        // Rotated 90 degrees about Z
        Matrix4 RotateZ = Matrix4().rotate_z(90.0f);
        Vector4 Direction = Vector4(2.0f, 0.0f, 0.0f, Vector4Type::Direction);
        Vector4 RotatedVector4 = RotateZ.transform(Direction);
        // X will go to Y
        Vector4 Expected = Vector4(0.0f, 2.0f, 0.0f, Vector4Type::Direction);
        assert(almostEqual(Expected.getX(), RotatedVector4.getX()));
        assert(almostEqual(Expected.getY(), RotatedVector4.getY()));
        assert(almostEqual(Expected.getZ(), RotatedVector4.getZ()));
        assert(almostEqual(Expected.getW(), RotatedVector4.getW()));
    }
}

void TestMatrix4Translation(void)
{
    Vector4 Add = Vector4(5.0f, 5.0f, 5.0f, Vector4Type::Point);
    Vector4 Point = Vector4(10.0f, 20.f, 30.0f, Vector4Type::Point);
    Matrix4 ScaleMatrix = Matrix4().scale(Vector4(2.0f, 2.0f, 2.0f, Vector4Type::Point));
    Matrix4 RotationMatrix = Matrix4().rotate_x(90.0f);
    Matrix4 Translation = Matrix4().translate(Add);
    Matrix4 ModelMatrix = Translation * RotationMatrix * ScaleMatrix;
    Vector4 TransformedVector4 = ModelMatrix.transform(Point);
    TransformedVector4.print();
    // Expected Vector4
    Vector4 Expected = Vector4(25.00f, -55.00f, 45.00f, Vector4Type::Point);
    Expected.print();
    assert(floatEqual(Expected.getX(), TransformedVector4.getX()));
    assert(floatEqual(Expected.getY(), TransformedVector4.getY()));
    assert(floatEqual(Expected.getZ(), TransformedVector4.getZ()));
    assert(floatEqual(Expected.getW(), TransformedVector4.getW()));
}

typedef ARRAY(TestCaseMatrix4) TestCases;
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
    array_new(&Tests, TestCaseMatrix4);

    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4GetElement", TestMatrix4GetElement));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4SetElement", TestMatrix4SetElement));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4Add", TestMatrix4Add));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4Sub", TestMatrix4Sub));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4Mult", TestMatrix4Mult));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4Value", TestMatrix4Value));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4Identity", TestMatrix4Identity));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrixTranspose", TestMatrixTranspose));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4Copy", TestMatrix4Copy));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4Scale", TestMatrix4Scale));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4RotateDirection", TestMatrix4RotateDirection));
    array_append(TestCaseMatrix4, &Tests, TestCaseMatrix4("TestMatrix4Translation",TestMatrix4Translation));
    RunAllTestCases(&Tests);
    return 0;
}
