#ifndef TEST_STRING_H
#define TEST_STRING_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_strerror.h"
#include "../s21_string.h"

Suite *memchr_suite();
Suite *memcmp_suite();
Suite *memcpy_suite();
Suite *memset_suite();
Suite *strncat_suite();
Suite *strchr_suite();
Suite *strncmp_suite();
Suite *strncpy_suite();
Suite *strcspn_suite();
Suite *strerror_suite();
Suite *strlen_suite();
Suite *strpbrk_suite();
Suite *strrchr_suite();
Suite *strstr_suite();
Suite *strtok_suite();
Suite *sprintf_suite();

Suite *insert_suite();
Suite *to_upper_suite();
Suite *to_lower_suite();
Suite *trim_suite();

Suite *strcat_suite();

#endif  // S21_STRING_TEST_H