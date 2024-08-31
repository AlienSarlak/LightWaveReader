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

void midpoint_tests()
{
	printf("midpoint_tests\n");
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
	float result = midpoint(arr, n, a, b);

	int int_value = (int)(expected * 1000);
	printf("Expected Value: %d.%02d\n", int_value / 1000, int_value % 1000);
	int_value = (int)(result * 1000);
	printf("Result Value: %d.%02d\n", int_value / 1000, int_value % 1000);
}

void test_sin_function()
{
	printf("test_sin_function\n");

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
	float result = midpoint(arr, n, a, b);

	int int_value = (int)(expected * 1000);
	printf("Expected Value: %d.%02d\n", int_value / 1000, int_value % 1000);
	int_value = (int)(result * 1000);
	printf("Result Value: %d.%02d\n", int_value / 1000, int_value % 1000);
}

void test_quadratic_function()
{
	printf("test_quadratic_function\n");
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
	float result = midpoint(arr, n, a, b);

	int int_value = (int)(expected * 1000);
	printf("Expected Value: %d.%02d\n", int_value / 1000, int_value % 1000);
	int_value = (int)(result * 1000);
	printf("Result Value: %d.%02d\n", int_value / 1000, int_value % 1000);
}

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD);

	test_quadratic_function();

	return 0;
}
