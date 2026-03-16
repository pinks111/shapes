#include <iostream>
#include <gtest/gtest.h>
#include "../Source/Matrix.h"

TEST (Matrix, CreateSquare)
{
	const size_t R = 128;
	const size_t C = 128;
	Matrix m(R, C);
	for (size_t r = 0; r < R; ++r)
		for (size_t c = 0; c < C; ++c)
			ASSERT_FALSE (m.get(r, c));
}

TEST (Matrix, CreateRow)
{
	const size_t C = 128;
	Matrix m(1, C);
	for (size_t c = 0; c < C; ++c)
		ASSERT_FALSE (m.get(0, c));

}

TEST (Matrix, CreateCol)
{
	const size_t R = 128;
	Matrix m(R, 1);
	for (size_t r = 0; r < R; ++r)
		ASSERT_FALSE (m.get(r, 0));
}

TEST (Matrix, SetGetSquare)
{
	const size_t R = 128;
	const size_t C = 128;
	Matrix m(R, C);
	for (size_t r = 0; r < R; ++r)
		for (size_t c = 0; c < C; ++c)
		{
			auto val = static_cast<bool>((r + c) % 2);
			m.set(r, c, val);
			ASSERT_FALSE (m.get(r, c) != val);
		}
}

TEST (Matrix, GetIncorrect)
{
	const size_t R = 128;
	const size_t C = 128;
	Matrix m(R, C);
	ASSERT_THROW (m.get(129, 1), std::out_of_range);
}
