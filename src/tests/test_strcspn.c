#include "test_string.h"

START_TEST(_default_1) {
  char str1[] = " kittens !!";
  char str2[] = " meow ";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(_default_2) {
  char str1[] = " kittens !!";
  char str2[] = "!! meow ";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(_default_3) {
  char str1[] = " kittens !!";
  char str2[] = " turtles ";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(_same_str) {
  char str1[] = "meow";
  char str2[] = "meow";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(_void_str1) {
  char str1[] = "";
  char str2[] = "meow";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(_void_str2) {
  char str1[] = "kitty!";
  char str2[] = "";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(_void_all) {
  char str1[] = "";
  char str2[] = "";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(_zero_all) {
  char str1[] = "\0";
  char str2[] = "\0";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(_zero_str1) {
  char str1[] = "\0";
  char str2[] = "kittens are Very cute! <333";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(_zero_str2) {
  char str1[] = "kittens are Very cute! <333";
  char str2[] = "\0";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(_with_all_letters) {
  char str1[] = "The five boxing wizards jump quickly";
  char str2[] = "The quick brown fox jumps over the lazy dog";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

START_TEST(_with_num_and_sym) {
  char str1[] = "1!2@3#4$5%6^7&8*9(0_)";
  char str2[] = "(_0)9*8&7^6%5$4#3@2!1";

  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
}
END_TEST

Suite *strcspn_suite() {
  Suite *s = suite_create("Tests for strcspn");
  TCase *tc = tcase_create("Tests for strcspn");

  tcase_add_test(tc, _default_1);
  tcase_add_test(tc, _default_2);
  tcase_add_test(tc, _default_3);
  tcase_add_test(tc, _same_str);
  tcase_add_test(tc, _void_str1);
  tcase_add_test(tc, _void_str2);
  tcase_add_test(tc, _void_all);
  tcase_add_test(tc, _zero_all);
  tcase_add_test(tc, _zero_str1);
  tcase_add_test(tc, _zero_str2);
  tcase_add_test(tc, _with_all_letters);
  tcase_add_test(tc, _with_num_and_sym);

  suite_add_tcase(s, tc);

  return s;
}
