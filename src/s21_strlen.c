#include "s21_string.h"

s21_size_t s21_strlen(const char *string) {
  s21_size_t length = 0;

  while (string[length] != '\0') length++;

  return length;
}