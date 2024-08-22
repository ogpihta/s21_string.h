#include "test_string.h"

START_TEST(_default) {
  char str1[] = "kitty! kitties! kittens!";
  char str2[] = "kitty! kitties! kittens!";
  char delim[] = "!";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  while (expected != s21_NULL || result != s21_NULL) {
    ck_assert_str_eq(expected, result);
    expected = strtok(s21_NULL, delim);
    result = s21_strtok(s21_NULL, delim);
  }
}
END_TEST

START_TEST(_default_2) {
  char str1[] = "kittens are Very cute! <333 ";
  char str2[] = "kittens are Very cute! <333 ";
  char delim[] = " ";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  while (expected != s21_NULL || result != s21_NULL) {
    ck_assert_str_eq(expected, result);
    expected = strtok(s21_NULL, delim);
    result = s21_strtok(s21_NULL, delim);
  }
}
END_TEST

START_TEST(_without_delim_in_str) {
  char str1[] = "kitty_kitty kittens";
  char str2[] = "kitty_kitty kittens";
  char delim[] = "!";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  while (expected != s21_NULL || result != s21_NULL) {
    ck_assert_str_eq(expected, result);
    expected = strtok(s21_NULL, delim);
    result = s21_strtok(s21_NULL, delim);
  }
}
END_TEST

START_TEST(_void_delim) {
  char str1[] = "kitty kitty kittens";
  char str2[] = "kitty kitty kittens";
  char delim[] = "";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  while (expected != s21_NULL || result != s21_NULL) {
    ck_assert_str_eq(expected, result);
    expected = strtok(s21_NULL, delim);
    result = s21_strtok(s21_NULL, delim);
  }
}
END_TEST

START_TEST(_void_str) {
  char str1[] = "";
  char str2[] = "";
  char delim[] = "_";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  while (expected != s21_NULL || result != s21_NULL) {
    ck_assert_str_eq(expected, result);
    expected = strtok(s21_NULL, delim);
    result = s21_strtok(s21_NULL, delim);
  }
}
END_TEST

START_TEST(_hard_delim) {
  char str1[] = "kittens are Very_cute! <333 ";
  char str2[] = "kittens are Very_cute! <333 ";
  char delim[] = "_!<";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  while (expected != s21_NULL || result != s21_NULL) {
    ck_assert_str_eq(expected, result);
    expected = strtok(s21_NULL, delim);
    result = s21_strtok(s21_NULL, delim);
  }
}
END_TEST

START_TEST(_hard_delim_2) {
  char str1[] = "kittens^^ are Very_cute! <333 ";
  char str2[] = "kittens^^ are Very_cute! <333 ";
  char delim[] = "!_^^<";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  while (expected != s21_NULL || result != s21_NULL) {
    ck_assert_str_eq(expected, result);
    expected = strtok(s21_NULL, delim);
    result = s21_strtok(s21_NULL, delim);
  }
}
END_TEST

Suite *strtok_suite() {
  Suite *s = suite_create("Tests for strtok");
  TCase *tc = tcase_create("Tests for strtok");

  tcase_add_test(tc, _default);
  tcase_add_test(tc, _default_2);
  tcase_add_test(tc, _without_delim_in_str);
  tcase_add_test(tc, _void_delim);
  tcase_add_test(tc, _void_str);
  tcase_add_test(tc, _hard_delim);
  tcase_add_test(tc, _hard_delim_2);

  suite_add_tcase(s, tc);

  return s;
}
