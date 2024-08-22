#include "s21_string.h"
char *s21_strstr(const char *haystack, const char *needle) {
  char *str = s21_NULL;       // смотри строчку №7
  if (needle[0] == '\0')      // смотри строчку №6
    return (char *)haystack;  // некорректные данные
  for (int i = 0; haystack[i] != '\0'; i++) {
    if (haystack[i] == needle[0]) {  // если i-ый символ строки haystack равен
                                     //  0-му символу строки needle
      for (int j = 0;; j++) {  // сравниваем последующие символы haystack с
                               // символами из needle
        if (needle[j] ==
            '\0') {  // если достигли конца needle значит есть совпадение
          str = (char *)&haystack[i];  // передаем в возвращаемое значение
                                       // адрес начала совпадения
          break;
        }
        if (needle[j] != haystack[i + j])  // если есть отличие --> выходим
          break;
        if (haystack[i + j] == '\0')  // если достигаем конца haystack, а
                                      // needle еще остался - лив
          break;
      }
    }
    if (str)  // если возвращаемое значение str не равно s21_NULL --> есть
              // совпадение --> выходим
      break;
  }
  return (str);
}