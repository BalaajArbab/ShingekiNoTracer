#include <gtest/gtest.h>

#include <Math/Vector3.h>


class Vector3Test : public ::testing::Test
{
protected:
	Vector3 v0{ 0, 0, 0 };
	Vector3 v1{ 1.0, 1.0, 1.0 };
	Vector3 v1_b{ 1.0, 1.0, 1.0 };
	Vector3 v2{ -2.0, -2.0, -2.0 };
	Vector3 v3{ 5.5, -5.5, 0 };
	
};

TEST_F(Vector3Test, VectorEquality) 
{

	for (int i = 0; i < 3; ++i)
	{
		EXPECT_DOUBLE_EQ(v1[i], v1[i]);
	}

	for (int i = 0; i < 3; ++i)
	{
		EXPECT_DOUBLE_EQ(v1[i], v1_b[i]);
	}

	for (int i = 0; i < 3; ++i)
	{
		EXPECT_DOUBLE_EQ(v3[i], v3[i]);
	}

	EXPECT_DOUBLE_EQ(v1.X(), v1_b.X());
	EXPECT_DOUBLE_EQ(v1.Y(), v1_b.Y());
	EXPECT_DOUBLE_EQ(v1.Z(), v1_b.Z());

}

TEST_F(Vector3Test, VectorUnaryMinus)
{
	Vector3 t1{ -1.0, -1.0, -1.0 };
	Vector3 minusV1 = -v1;
	EXPECT_DOUBLE_EQ(minusV1.X(), t1.X());
	EXPECT_DOUBLE_EQ(minusV1.Y(), t1.Y());
	EXPECT_DOUBLE_EQ(minusV1.Z(), t1.Z());

	Vector3 t2{ 2.0, 2.0, 2.0 };
	Vector3 minusV2 = -v2;
	EXPECT_DOUBLE_EQ(minusV2.X(), t2.X());
	EXPECT_DOUBLE_EQ(minusV2.Y(), t2.Y());
	EXPECT_DOUBLE_EQ(minusV2.Z(), t2.Z());
}

TEST_F(Vector3Test, VectorSubscript)
{
	v1[0] = 5;
	v1[1] = -15;
	v1[2] = 0;
	EXPECT_DOUBLE_EQ(v1.X(), 5);
	EXPECT_DOUBLE_EQ(v1.Y(), -15);
	EXPECT_DOUBLE_EQ(v1.Z(), 0);
}

TEST_F(Vector3Test, VectorPlusEquals)
{
	v1 += v0;
	EXPECT_DOUBLE_EQ(v1.X(), 1);
	EXPECT_DOUBLE_EQ(v1.Y(), 1);
	EXPECT_DOUBLE_EQ(v1.Z(), 1);

	v1 += v2;
	Vector3 t1{ -1.0, -1.0, -1.0 };
	EXPECT_DOUBLE_EQ(v1.X(), -1.0);
	EXPECT_DOUBLE_EQ(v1.Y(), -1.0);
	EXPECT_DOUBLE_EQ(v1.Z(), -1.0);

	v3 += v3;
	EXPECT_DOUBLE_EQ(v3.X(), 11.0);
	EXPECT_DOUBLE_EQ(v3.Y(), -11.0);
	EXPECT_DOUBLE_EQ(v3.Z(), 0);

}

TEST_F(Vector3Test, VectorMultiplyEquals)
{
	v1 *= 0;
	EXPECT_DOUBLE_EQ(v1.X(), 0);
	EXPECT_DOUBLE_EQ(v1.Y(), 0);
	EXPECT_DOUBLE_EQ(v1.Z(), 0);

	Vector3 t1 = v3;
	v3 *= 3;
	EXPECT_DOUBLE_EQ(v3.X(), 16.5);
	EXPECT_DOUBLE_EQ(v3.Y(), -16.5);
	EXPECT_DOUBLE_EQ(v3.Z(), 0);
}

TEST_F(Vector3Test, VectorDivideEquals)
{
	v1 /= 5;
	EXPECT_DOUBLE_EQ(v1.X(), 0.2);
	EXPECT_DOUBLE_EQ(v1.Y(), 0.2);
	EXPECT_DOUBLE_EQ(v1.Z(), 0.2);

	v2 /= 4;
	EXPECT_DOUBLE_EQ(v2.X(), -0.5);
	EXPECT_DOUBLE_EQ(v2.Y(), -0.5);
	EXPECT_DOUBLE_EQ(v2.Z(), -0.5);
}

TEST_F(Vector3Test, VectorMagnitude)
{
	EXPECT_DOUBLE_EQ(v0.Magnitude(), 0.0);
	EXPECT_DOUBLE_EQ(v1.Magnitude(), 1.7320508075688772);
	EXPECT_DOUBLE_EQ(v2.Magnitude(), 3.4641016151377544);
}

TEST_F(Vector3Test, VectorMagnitudeSquared)
{
	EXPECT_DOUBLE_EQ(v0.MagnitudeSquared(), 0.0);
	EXPECT_DOUBLE_EQ(v1.MagnitudeSquared(), 3);
	EXPECT_DOUBLE_EQ(v2.MagnitudeSquared(), 12);
}

TEST_F(Vector3Test, VectorZeroCheck)
{
	Vector3 t{ 0.000000001, 0.000000001, 0.000000001 };

	EXPECT_TRUE(t.NearZero());
}

TEST_F(Vector3Test, VectorAddition)
{
	Vector3 add1 = v1 + v0;
	EXPECT_DOUBLE_EQ(add1.X(), 1);
	EXPECT_DOUBLE_EQ(add1.Y(), 1);
	EXPECT_DOUBLE_EQ(add1.Z(), 1);

	Vector3 add2 = v1 + v3;
	EXPECT_DOUBLE_EQ(add2.X(), 6.5);
	EXPECT_DOUBLE_EQ(add2.Y(), -4.5);
	EXPECT_DOUBLE_EQ(add2.Z(), 1);

	Vector3 add3 = v2 + v2;
	EXPECT_DOUBLE_EQ(add3.X(),-4.0);
	EXPECT_DOUBLE_EQ(add3.Y(), -4.0);
	EXPECT_DOUBLE_EQ(add3.Z(),-4.0);
}

TEST_F(Vector3Test, VectorSubtraction)
{
	Vector3 sub1 = v1 - v0;
	EXPECT_DOUBLE_EQ(sub1.X(), 1);
	EXPECT_DOUBLE_EQ(sub1.Y(), 1);
	EXPECT_DOUBLE_EQ(sub1.Z(), 1);

	Vector3 sub2 = v1 - v3;
	EXPECT_DOUBLE_EQ(sub2.X(),-4.5);
	EXPECT_DOUBLE_EQ(sub2.Y(), 6.5);
	EXPECT_DOUBLE_EQ(sub2.Z(), 1);

	Vector3 sub3 = v2 - v2;
	EXPECT_DOUBLE_EQ(sub3.X(), 0.0);
	EXPECT_DOUBLE_EQ(sub3.Y(), 0.0);
	EXPECT_DOUBLE_EQ(sub3.Z(), 0.0);
}

TEST_F(Vector3Test, VectorToVectorMultiplication)
{
	Vector3 mul1 = v1 * v0;
	EXPECT_DOUBLE_EQ(mul1.X(), 0.0);
	EXPECT_DOUBLE_EQ(mul1.Y(), 0.0);
	EXPECT_DOUBLE_EQ(mul1.Z(), 0.0);

	Vector3 mul2 = v1 * v3;
	EXPECT_DOUBLE_EQ(mul2.X(), 5.5);
	EXPECT_DOUBLE_EQ(mul2.Y(), -5.5);
	EXPECT_DOUBLE_EQ(mul2.Z(), 0);

	Vector3 mul3 = v2 * v2;
	EXPECT_DOUBLE_EQ(mul3.X(), 4.0);
	EXPECT_DOUBLE_EQ(mul3.Y(), 4.0);
	EXPECT_DOUBLE_EQ(mul3.Z(), 4.0);
}

TEST_F(Vector3Test, VectorScalarMultiplication)
{
	Vector3 mul1 = v1 * 5;
	EXPECT_DOUBLE_EQ(mul1.X(), 5.0);
	EXPECT_DOUBLE_EQ(mul1.Y(), 5.0);
	EXPECT_DOUBLE_EQ(mul1.Z(), 5.0);

	Vector3 mul2 = -10 * v1;
	EXPECT_DOUBLE_EQ(mul2.X(), -10.0);
	EXPECT_DOUBLE_EQ(mul2.Y(), -10.0);
	EXPECT_DOUBLE_EQ(mul2.Z(), -10.0);

	Vector3 mul3 = v2 * 2;
	EXPECT_DOUBLE_EQ(mul3.X(), -4.0);
	EXPECT_DOUBLE_EQ(mul3.Y(), -4.0);
	EXPECT_DOUBLE_EQ(mul3.Z(), -4.0);
}

TEST_F(Vector3Test, VectorScalarDivision)
{
	Vector3 mul1 = v1 / 5;
	EXPECT_DOUBLE_EQ(mul1.X(), 0.2);
	EXPECT_DOUBLE_EQ(mul1.Y(), 0.2);
	EXPECT_DOUBLE_EQ(mul1.Z(), 0.2);

	Vector3 mul2 = v1 / -10;
	EXPECT_DOUBLE_EQ(mul2.X(), -0.1);
	EXPECT_DOUBLE_EQ(mul2.Y(), -0.1);
	EXPECT_DOUBLE_EQ(mul2.Z(), -0.1);

	Vector3 mul3 = v2 / 2;
	EXPECT_DOUBLE_EQ(mul3.X(), -1.0);
	EXPECT_DOUBLE_EQ(mul3.Y(), -1.0);
	EXPECT_DOUBLE_EQ(mul3.Z(), -1.0);
}

TEST_F(Vector3Test, VectorDotProduct)
{
	double dot1 = DotProduct(v1, v1);
	EXPECT_DOUBLE_EQ(dot1, 3.0);

	double dot2 = DotProduct(v2, v2);
	EXPECT_DOUBLE_EQ(dot2, 12.0);

	double dot3 = DotProduct(v1, v2);
	EXPECT_DOUBLE_EQ(dot3, -6.0);

	double dot4 = DotProduct(v2, v3);
	EXPECT_DOUBLE_EQ(dot4, 0.0);
}

TEST_F(Vector3Test, VectorCrossProduct)
{
	Vector3 cross1 = CrossProduct(v1, v1);
	EXPECT_DOUBLE_EQ(cross1.X(), 0.0);
	EXPECT_DOUBLE_EQ(cross1.Y(), 0.0);
	EXPECT_DOUBLE_EQ(cross1.Z(), 0.0);

	Vector3 cross2 = CrossProduct(v1, v3);
	Vector3 exp2{ 5.5, 5.5, -11 };
	EXPECT_DOUBLE_EQ(cross2.X(), 5.5);
	EXPECT_DOUBLE_EQ(cross2.Y(), 5.5);
	EXPECT_DOUBLE_EQ(cross2.Z(), -11.0);
}

TEST_F(Vector3Test, VectorUnitVector)
{
	EXPECT_DOUBLE_EQ(UnitVector(v1).Magnitude(), 1.0);
	EXPECT_DOUBLE_EQ(UnitVector(v2).Magnitude(), 1.0);
	EXPECT_DOUBLE_EQ(UnitVector(v3).Magnitude(), 1.0);
}

TEST_F(Vector3Test, ColourUnitVector)
{
	Colour clamped = Clamp(v3);

	EXPECT_DOUBLE_EQ(clamped.X(), 1.0);
	EXPECT_DOUBLE_EQ(clamped.Y(), 0.0);
	EXPECT_DOUBLE_EQ(clamped.Z(), 0.0);
}