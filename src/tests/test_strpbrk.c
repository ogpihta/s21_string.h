#include "test_string.h"

START_TEST(_default_with_match) {
  char str1[] = "kitties !!";
  char str2[] = "puppy";

  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(_default_without_match) {
  char str1[] = "kitties !!";
  char str2[] = "pupupu";

  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(_void_str1) {
  char str1[] = " ";
  char str2[] = "meow";

  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(_void_str2) {
  char str1[] = "meow";
  char str2[] = " ";

  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(_void_all) {
  char str1[] = " ";
  char str2[] = " ";

  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(_zero_str1) {
  char str1[] = "\0";
  char str2[] = "kitty";

  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(_zero_str2) {
  char str1[] = "meow";
  char str2[] = "\0";

  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

START_TEST(_zero_all) {
  char str1[] = "meow";
  char str2[] = "\0";

  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
}
END_TEST

Suite *strpbrk_suite() {
  Suite *s = suite_create("Tests for strpbrk");
  TCase *tc = tcase_create("Tests for strpbrk");

  tcase_add_test(tc, _default_with_match);
  tcase_add_test(tc, _default_without_match);
  tcase_add_test(tc, _void_str1);
  tcase_add_test(tc, _void_str2);
  tcase_add_test(tc, _void_all);
  tcase_add_test(tc, _zero_str1);
  tcase_add_test(tc, _zero_str2);
  tcase_add_test(tc, _zero_all);

  suite_add_tcase(s, tc);

  return s;
}
