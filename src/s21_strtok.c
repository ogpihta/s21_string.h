#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last_pos = s21_NULL;
  char *start = s21_NULL;

  if (str == s21_NULL) {
    str = last_pos;
  }

  while (str && *str && s21_strchr(delim, *str)) {
    str++;
  }
  if (str && *str) {
    start = str;

    while (*str && !s21_strchr(delim, *str)) {
      str++;
    }

    if (*str) {
      *str = '\0';
      last_pos = str + 1;
    } else {
      last_pos = s21_NULL;
    }
  } else {
    last_pos = s21_NULL;
  }
  return start;
}