#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *res = s21_NULL;
  if (str == s21_NULL) {
    return s21_NULL;  // некорректные данные
  }

  char *lower_str = calloc((int)s21_strlen(str) + 1, sizeof(char));
  if (lower_str == s21_NULL) {
    return s21_NULL;  // некорректные данные
  }

  const char *src = str;
  char *dest = lower_str;

  while (*src) {
    char ch = *src;
    if (ch >= 'A' && ch <= 'Z') {
      *dest = ch - ('A' - 'a');
    } else {
      *dest = ch;
    }
    src++;
    dest++;
  }
  *dest = '\0';
  res = (void *)lower_str;
  return res;
}