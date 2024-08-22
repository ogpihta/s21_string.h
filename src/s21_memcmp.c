#include "s21_string.h"

/*Сравнивает первые n байтов str1 и str2.*/

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int count_dif = 0;
  unsigned char *s1 = (unsigned char *)str1;
  unsigned char *s2 = (unsigned char *)str2;
  for (s21_size_t i = 0; i < n && count_dif == 0; i++) {
    count_dif = *s1 - *s2;
    s1++;
    s2++;
  }
  return count_dif;
}
