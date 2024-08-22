#include "s21_strerror.h"

/*Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
указатель на строку с сообщением об ошибке. Нужно объявить макросы, содержащие
массивы сообщений об ошибке для операционных систем mac и linux. Описания ошибок
есть в оригинальной библиотеке. Проверка текущей ОС осуществляется с помощью
директив.*/

char *s21_strerror(int errnum) {
  static char *errors_arr[SIZE_OF_ERRORLIST] = ERRORLIST;
  char *error = s21_NULL;
  int is_minus_flag = 0;
  char incorr_errnum[15];  // делаем строку, куда запишем число, переделанную
                           // в чар
  char result_error[1024] = UNKNOWN;
  if (errnum >= 0 && errnum < SIZE_OF_ERRORLIST) {
    error = errors_arr[errnum];
  } else {
    int quality_of_numbers = 0;  // колличество цифер в числе
    int buff = errnum;           // буффер числа

    if (buff < 0) {
      buff *= -1;
      is_minus_flag = 1;
    }

    while (buff != 0) {
      incorr_errnum[quality_of_numbers] = (buff % 10) + '0';
      quality_of_numbers++;
      buff /= 10;  // отрезаем по одной цифре с конца чтобы посчитать кол-во
                   // цифер в числе
    }
    if (is_minus_flag) result_error[s21_strlen(result_error)] = '-';
    result_error[s21_strlen(result_error) + 1] = '\0';
    for (int i = quality_of_numbers - 1; i >= 0; i--) {
      int j = s21_strlen(result_error);
      result_error[j] = incorr_errnum[i];
      result_error[j + 1] = '\0';
    }
    error = result_error;
  }

  return error;
}
