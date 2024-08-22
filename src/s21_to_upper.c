#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  if (str == s21_NULL) {
    return res;  // некорректные данные
  }

  char *upper_str = calloc((int)s21_strlen(str) + 1, sizeof(char));
  if (upper_str == s21_NULL) {
    return res;  // некорректные данные
  }

  const char *src = str;
  char *dest = upper_str;

  while (*src) {
    char ch = *src;
    if (ch >= 'a' && ch <= 'z') {
      *dest = ch - ('a' - 'A');
    } else {
      *dest = ch;
    }
    src++;
    dest++;
  }
  *dest = '\0';
  res = (void *)upper_str;
  return res;
}
