/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Simulation based on qemu_cortex_m3
 */

#include <stdio.h>
#include <math.h>
#include <zephyr/kernel.h>
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

void small_array(Methods m)
{
	float arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
	int n = sizeof(arr) / sizeof(arr[0]) - 1;
	float a = 0.0;
	float b = 4.0;
	float expected = 12.0;
	float result = callback(m, arr, n, a, b);

	int precision = (int)1e4;
	int int_value = (int)(fabs(result - expected) * precision);
	printf("small_array Accuracy: %d.%04d\n", int_value / precision, int_value % precision);
}

void exp_function(Methods m)
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

	int precision = (int)1e4;
	int int_value = (int)(fabs(result - expected) * precision);
	printf("exp_function Accuracy: %d.%04d\n", int_value / precision, int_value % precision);
}

void sin_function(Methods m)
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

	int precision = (int)1e4;
	int int_value = (int)(fabs(result - expected) * precision);
	printf("sin_function Accuracy: %d.%04d\n", int_value / precision, int_value % precision);
}

void quadratic_function(Methods m)
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

	int precision = (int)1e4;
	int int_value = (int)(fabs(result - expected) * precision);
	printf("quadratic_function Accuracy: %d.%04d\n", int_value / precision, int_value % precision);
}

/**
 * @brief Test Asserts
 *
 * This test verifies various assert macros provided by ztest.
 *
 */
void midpoint_tests_small_array()
{
	small_array(MIDPOINT);
}

void midpoint_tests_exp_function()
{
	exp_function(MIDPOINT);
}

void midpoint_tests_sin_function()
{
	sin_function(MIDPOINT);
}

void midpoint_tests_quadratic_function()
{
	quadratic_function(MIDPOINT);
}

/* */
/*					Trapizoidal					*/
/* */

void trapizoidal_tests_small_array()
{
	small_array(TRAPEZOIDAL);
}

void trapizoidal_tests_exp_function()
{
	exp_function(TRAPEZOIDAL);
}

void trapizoidal_tests_sin_function()
{
	sin_function(TRAPEZOIDAL);
}

void trapizoidal_tests_quadratic_function()
{
	quadratic_function(TRAPEZOIDAL);
}

/* */
/*					  Simpson					*/
/* */

void simpsons_tests_small_array()
{
	small_array(SIMPSONS);
}

void simpsons_tests_exp_function()
{
	exp_function(SIMPSONS);
}

void simpsons_tests_sin_function()
{
	sin_function(SIMPSONS);
}

void simpsons_tests_quadratic_function()
{
	quadratic_function(SIMPSONS);
}

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD);

	printf("midpoint\n");
	midpoint_tests_small_array();
	midpoint_tests_exp_function();
	midpoint_tests_sin_function();
	midpoint_tests_quadratic_function();
	printf("trapizoidal\n");
	trapizoidal_tests_small_array();
	trapizoidal_tests_exp_function();
	trapizoidal_tests_sin_function();
	trapizoidal_tests_quadratic_function();
	printf("simpsons\n");
	simpsons_tests_small_array();
	simpsons_tests_exp_function();
	simpsons_tests_sin_function();
	simpsons_tests_quadratic_function();
	return 0;
}
