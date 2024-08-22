#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *s1;
  const char *s2;

  for (s1 = str1; *s1 != '\0'; s1++) {
    for (s2 = str2; *s2 != '\0'; s2++) {
      if (*s1 == *s2) {
        return (s21_size_t)(s1 - str1);
      }
    }
  }
  return (s21_size_t)(s1 - str1);
}