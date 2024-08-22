#include "s21_string.h"

/*Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
 * байтах строки, на которую указывает аргумент str.*/

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;
  unsigned char *match = s21_NULL;
  for (s21_size_t i = 0; i < n && s; i++) {
    if (s[i] == c) {
      match = (void *)&s[i];
      break;
    }
  }
  return match;
}
