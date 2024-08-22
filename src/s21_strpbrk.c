#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *return_pointer = s21_NULL;

  for (int i = 0; str1[i] != '\0'; i++) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        return_pointer = (char *)&str1[i];
        break;
      }
    }
    if (return_pointer) break;
  }

  return return_pointer;
}