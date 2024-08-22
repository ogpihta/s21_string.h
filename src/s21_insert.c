#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = s21_NULL;
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (src == s21_NULL || str == s21_NULL || start_index > src_len) {
    return res;  // некорректные значения
  }

  char *new_str = calloc(src_len + str_len + 1, sizeof(char));
  if (new_str == s21_NULL) {
    return res;  // некорректная отработка маллока
  }

  s21_strncpy(new_str, src, start_index);
  s21_strcat(new_str, str);
  s21_strcat(new_str, src + start_index);

  res = (void *)new_str;
  return res;
}