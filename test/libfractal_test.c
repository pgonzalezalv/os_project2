#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <CUnit/CUnit.h>

#include "../libfractal/fractal.h"

extern char *name;
extern int width;
extern int height;
extern double a;
extern double b;


void test_libfractal_ptr_not_null() {
	fractal_t *ptr = fractal_new(name, width, height, a, b);
	CU_ASSERT_PTR_NOT_NULL(ptr);
	fractal_free(ptr);
}

void test_libfractal_ptr_value_not_null() {
	fractal_t *ptr = fractal_new(name, width, height, a, b);
	CU_ASSERT_PTR_NOT_NULL(ptr->value);
	fractal_free(ptr);
}

void test_libfractal_get_name() {
	fractal_t *ptr = fractal_new("CUnit", width, height, a, b);
	CU_ASSERT_EQUAL(fractal_get_name(ptr), "CUnit");
	fractal_free(ptr);
}

void test_libfractal_get_width() {
	fractal_t *ptr = fractal_new(name, 42, height, a, b);
	CU_ASSERT_EQUAL(fractal_get_width(ptr), 42);
	fractal_free(ptr);
}

void test_libfractal_get_height() {
	fractal_t *ptr = fractal_new(name, width, 42, a, b);
	CU_ASSERT_EQUAL(fractal_get_height(ptr), 42);
	fractal_free(ptr);
}

void test_libfractal_get_a() {
	fractal_t *ptr = fractal_new(name, width, height, 42.0, b);
	CU_ASSERT_EQUAL(fractal_get_a(ptr), 42.0);
	fractal_free(ptr);
}

void test_libfractal_get_b() {
	fractal_t *ptr = fractal_new(name, width, height, a, 42.0);
	CU_ASSERT_EQUAL(fractal_get_b(ptr), 42.0);
	fractal_free(ptr);
}

int setup(void) {
	*name = "CUnit";
	width = 0;
	height = 0;
	a = 0.0;
	b = 0.0;
	return 0;
}

int teardown(void) {
	return 0;
}

int main(int argc, char const *argv[]) {
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Suite de tests : libfractal", setup, teardown);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "Name", test_libfractal_ptr_not_null)) ||
			(NULL == CU_add_test(pSuite, "Name", test_libfractal_ptr_value_not_null)) ||
			(NULL == CU_add_test(pSuite, "Name", test_libfractal_get_name)) ||
			(NULL == CU_add_test(pSuite, "Name", test_libfractal_get_width)) ||
			(NULL == CU_add_test(pSuite, "Name", test_libfractal_get_height)) ||
			(NULL == CU_add_test(pSuite, "Name", test_libfractal_get_a)) ||
			(NULL == CU_add_test(pSuite, "Name", test_libfractal_get_b))) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	CU_basic_run_tests();
	CU_basic_show_failures(CU_get_failure_list());
	CU_cleanup_registry();
	return 0;
}
