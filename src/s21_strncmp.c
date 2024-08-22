#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t i;
  int result = 0;

  for (i = 0; i < n; i++) {
    if (str1[i] != str2[i]) {
      result = (unsigned char)str1[i] - (unsigned char)str2[i];
      break;
    }
    if (str1[i] == '\0') {
      break;
    }
  }

  return result;
}