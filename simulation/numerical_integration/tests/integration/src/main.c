/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/ztest.h>
#include <stdio.h>
#include <math.h>
#include <integration.h>

#define M_PI 3.14159265358979323846	  /* pi */
#define M_PI_2 1.57079632679489661923 /* pi/2 */
#define M_PI_4 0.78539816339744830962 /* pi/4 */

typedef enum EMethods
{
	MIDPOINT = 0,
	TRAPEZOIDAL,
	SIMPSONS,
	EMethods_Length
} Methods;

/**
 *
 */
float callback(Methods m, float arr[], int n, float a, float b)
{
	float result = -NAN;
	switch (m)
	{
	case MIDPOINT:
		result = midpoint(arr, n, a, b);
		break;
	case TRAPEZOIDAL:
		result = trapezoidal(arr, n, a, b);
		break;
	case SIMPSONS:
		result = simpsons(arr, n, a, b);
		break;
	default:
		break;
	}
	return result;
}

float small_array(Methods m)
{
	float arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
	int n = sizeof(arr) / sizeof(arr[0]) - 1;
	float a = 0.0;
	float b = 4.0;
	float expected = 12.0;
	float result = callback(m, arr, n, a, b);

	int int_value = (int)(expected * 1000);
	printf("Expected Value: %d.%02d\n", int_value / 1000, int_value % 1000);
	int_value = (int)(result * 1000);
	printf("Result Value: %d.%02d\n", int_value / 1000, int_value % 1000);
	zassert_true(fabs(result - expected) < 1e-6, "Test failed: expected is not equal to the result");
}

float exp_function(Methods m)
{
	float a = 0.0F;
	float b = 2.0F;
	int n = 200;

	float arr[200] = {0.0F};

	float step = (b - a) / n;
	for (int i = 0; i < n; ++i)
	{
		float x = a + i * step;
		arr[i] = expf(x);
	}

	float expected = expf(b) - expf(a);
	float result = callback(m, arr, n, a, b);
	zassert_true(fabs(result - expected) < 5e-2, "Test failed: expected is not equal to the result");
}

float sin_function(Methods m)
{
	float a = 0.0F;
	float b = M_PI_4;
	int n = 200;

	float arr[200] = {0.0F};

	float step = (b - a) / n;
	for (int i = 0; i < n; ++i)
	{
		float x = a + i * step;
		arr[i] = sinf(x);
	}

	float expected = -cosf(b) + cosf(a);
	float result = callback(m, arr, n, a, b);
	zassert_true(fabs(result - expected) < 5e-2, "Test failed: expected is not equal to the result");
}

float quadratic_function(Methods m)
{
	/*
	x=x^2 + 5x + 9
	 */
	float a = 0.0F;
	float b = 1.0F;
	int n = 200;

	float arr[200] = {0.0F};

	float step = (b - a) / n;
	for (int i = 0; i < n; ++i)
	{
		float x = a + i * step;
		arr[i] = powf(x, 2) + (5 * x) + 9;
	}

	float expected = ((powf(b, 3) / 3.0F) + (5.0F * powf(b, 2) / 2.0F) + (9.0F * b)) -
					 ((powf(a, 3) / 3.0F) + (5.0F * powf(a, 2) / 2.0F) + (9.0F * a));
	float result = callback(m, arr, n, a, b);
	zassert_true(fabs(result - expected) < 5e-2, "Test failed: expected is not equal to the result");
}

ZTEST_SUITE(midpoint_tests, NULL, NULL, NULL, NULL, NULL);

/**
 * @brief Test Asserts
 *
 * This test verifies various assert macros provided by ztest.
 *
 */
ZTEST(midpoint_tests, test_assert)
{
	zassert_true(1, "1 was false");
	zassert_false(0, "0 was true");
	zassert_is_null(NULL, "NULL was not NULL");
	zassert_not_null("foo", "\"foo\" was NULL");
	zassert_equal(1, 1, "1 was not equal to 1");
	zassert_equal_ptr(NULL, NULL, "NULL was not equal to NULL");
}

ZTEST(midpoint_tests, test_small_array)
{
	small_array(MIDPOINT);
}

ZTEST(midpoint_tests, test_exp_function)
{
	exp_function(MIDPOINT);
}

ZTEST(midpoint_tests, test_sin_function)
{
	sin_function(MIDPOINT);
}

ZTEST(midpoint_tests, test_quadratic_function)
{
	quadratic_function(MIDPOINT);
}

/* */
/*					TRAPIZOIDALal					*/
/* */

ZTEST_SUITE(TRAPIZOIDALal_tests, NULL, NULL, NULL, NULL, NULL);

ZTEST(TRAPIZOIDALal_tests, test_small_array)
{
	small_array(TRAPEZOIDAL);
}

ZTEST(TRAPIZOIDALal_tests, test_exp_function)
{
	exp_function(TRAPEZOIDAL);
}

ZTEST(TRAPIZOIDALal_tests, test_sin_function)
{
	sin_function(TRAPEZOIDAL);
}

ZTEST(TRAPIZOIDALal_tests, test_quadratic_function)
{
	quadratic_function(TRAPEZOIDAL);
}

/* */
/*					  Simpson					*/
/* */

ZTEST_SUITE(simpson_tests, NULL, NULL, NULL, NULL, NULL);

ZTEST(simpson_tests, test_small_array)
{
	small_array(SIMPSONS);
}

ZTEST(simpson_tests, test_exp_function)
{
	exp_function(SIMPSONS);
}

ZTEST(simpson_tests, test_sin_function)
{
	sin_function(SIMPSONS);
}

ZTEST(simpson_tests, test_quadratic_function)
{
	quadratic_function(SIMPSONS);
}
