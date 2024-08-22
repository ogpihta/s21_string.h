#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  s21_size_t start = 0;
  s21_size_t end = s21_strlen(src);

  if (src == s21_NULL || trim_chars == s21_NULL) {
    return res;  // некорректные данные
  }
  while (start < end && s21_strchr(trim_chars, src[start]) != s21_NULL) {
    start++;
  }
  while (end > start && s21_strchr(trim_chars, src[end - 1]) != s21_NULL) {
    end--;
  }

  s21_size_t new_len = end - start;

  char *trimmed_str = calloc(new_len + 1, sizeof(char));
  if (trimmed_str == s21_NULL) {
    return res;  // некорректная отработка
  }
  s21_strncpy(trimmed_str, src + start, new_len);

  trimmed_str[new_len] = '\0';
  res = (void *)trimmed_str;
  return res;
}