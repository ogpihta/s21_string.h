#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *str_start = str;  // начальный адресс
  va_list args;
  va_start(args, format);
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      output_specs specs = format_string_parser(&format, &args);
      str = input_arg_in_str(&str, &specs, &args, str_start);
      if (!str) break;
    } else {
      *str = *format;
      format++;
      str++;
    }
  }
  va_end(args);
  s21_size_t length = 0;
  if (str) {
    *str = '\0';
    length = str - str_start;  // разница адресов - колличество действительно
                               // напечатанных символов
  }
  return (int)length;
}

output_specs format_string_parser(const char **format, va_list *args) {
  output_specs specs = {0};

  get_flags(&specs, format);      // флаги
  get_width(&specs, format);      // ширина
  get_accurency(&specs, format);  // точность
  get_lenth(&specs, format);      // длина(модификкатор)
  if (s21_strchr("cdieEfgGosuxXpn%", **format)) {
    specs.spec = **format;
    (*format)++;
  } else {
    exit(1);
  }

  if (specs.width_from_args) specs.width = va_arg(*args, s21_size_t);
  if (specs.accuracy_from_args) specs.accuracy = va_arg(*args, s21_size_t);
  return specs;
}

void get_flags(output_specs *specs, const char **format) {
  while (s21_strchr("-+ #0", **format)) {
    if (**format == '-')
      specs->minus = true;
    else if (**format == '+')
      specs->plus = true;
    else if (**format == ' ')
      specs->space = true;
    else if (**format == '#')
      specs->sharp = true;
    else if (**format == '0')
      specs->zero = true;
    (*format)++;  // обращение к адресу: переходим на след. позицию
  }
  // корректировка сочетанности
  if (specs->plus &&
      specs->space)  // если одновременно + и пробел --> пробел игнорируется
    specs->space = false;
  if (specs->zero && specs->minus)  // если одновременно - и 0 --> 0
                                    // игнорируется
    specs->zero = false;
}

void get_width(output_specs *specs, const char **format) {
  if (**format != '*') {
    while (**format >= '0' &&
           **format <=
               '9') {  // если есть число или * устанавливаем занчение точности.
      specs->width *=
          10;  // елси нет ни числа, ни звезды - точность всё ещё ноль
      specs->width += **format - '0';
      (*format)++;
    }
  } else {
    specs->width_from_args = true;
    (*format)++;
  }
}

void get_accurency(output_specs *specs, const char **format) {
  if (**format == '.') {
    specs->has_accuracy = true;
    (*format)++;
    if (**format != '*') {
      while (**format >= '0' && **format <= '9') {
        specs->accuracy *= 10;
        specs->accuracy += **format - '0';
        (*format)++;
      }
    } else {
      specs->accuracy_from_args = true;
      (*format)++;
    }
  }
}

void get_lenth(output_specs *specs, const char **format) {
  if (**format == 'h') {
    specs->h = true;
    (*format)++;
  } else if (**format == 'l') {
    specs->l = true;
    (*format)++;
  } else if (**format == 'L') {
    specs->L = true;
    (*format)++;
  }
}

char *input_arg_in_str(char **str, output_specs *specs, va_list *arguments,
                       char *str_start) {
  if (specs->spec == 'd' ||
      specs->spec == 'i')  // в printf они буквально одинаковы
    *str = input_decimal(str, specs, arguments);
  if (specs->spec == 'f') *str = input_float(str, specs, arguments);
  if (specs->spec == 'c') *str = input_char(str, specs, arguments);
  if (specs->spec == '%') *str = input_char(str, specs, arguments);
  if (specs->spec == 'n') {
    input_quality(arguments, str_start);
  }
  if (specs->spec == 'u' || specs->spec == 'o' || specs->spec == 'x' ||
      specs->spec == 'X' || specs->spec == 'p') {  // беззнаковые в разных СС
    *str = input_unsigned(str, specs, arguments);
  }
  if (specs->spec == 's') {
    *str = input_string(*str, specs, arguments);
  }
  if (specs->spec == 'e' || specs->spec == 'E') {
    *str = input_scientific_notation(str, specs, arguments);
  }
  if (specs->spec == 'g' || specs->spec == 'G') {
    *str = input_shortest_record(str, specs, arguments);
  }
  if (*str) **str = '\0';
  return *str;
}

char *input_decimal(char **str, output_specs *specs, va_list *arguments) {
  long int num = 0;
  if (specs->l)
    num = (long int)va_arg(*arguments, long int);
  else if (specs->h)
    num = (short int)va_arg(*arguments,
                            int);  // ругается компилятор на этот short
  else
    num = (int)va_arg(*arguments, int);
  // }
  char *str_number_buff = NULL;
  s21_size_t weight_number = get_weight_of_number(num, specs);
  str_number_buff = (char *)calloc((weight_number + 1), sizeof(char));
  if (!str_number_buff)  // ошибка выделения памяти !
    return s21_NULL;  // дальнейшее выполнение программы не имеет смысла
  str_number_buff[weight_number] = '\0';
  char *start_of_str_buff = str_number_buff;
  str_number_buff = fill_buff_with_number(str_number_buff, num, specs);
  *str = s21_strncat(*str, start_of_str_buff, weight_number + 1);
  free(start_of_str_buff);

  return *str + weight_number;
}

s21_size_t get_weight_of_number(long int num, output_specs *specs) {
  s21_size_t result = 0;

  result = get_digits_quality(num);

  if (specs->accuracy >
      result)  // указывает на минимальное количество символов,
               // необходимыз для отображения типов d, i, ...
               // (остальное пространство заполняется нулями)
    result = specs->accuracy;

  if (specs->space || specs->plus ||
      num < 0)  // дополнительное место для пробела или знака
    result++;

  if (specs->width >
      result)  // указывает минимальную ширину поля (включая знак для чисел)
    result = specs->width;
  return result;
}

char *fill_buff_with_number(char *str_number_buff, long num,
                            output_specs *specs) {
  bool is_negative = false;
  if (num < 0) {
    num = -num;
    is_negative = true;
  }
  if (specs->minus) {  // заполнение от левого края (есть флаг -)
    str_number_buff = put_char_of_sign(str_number_buff, specs, is_negative);
    str_number_buff = put_number(str_number_buff, num, specs);
    str_number_buff = put_spaces_with_minus(str_number_buff);
  } else {  // заполнение от правого края (стандарт) //ERR
    str_number_buff =
        put_spaces_without_minus(str_number_buff, specs, is_negative, num);
    str_number_buff = put_char_of_sign(str_number_buff, specs, is_negative);
    str_number_buff = put_number(str_number_buff, num, specs);
  }
  return str_number_buff;
}

char *put_char_of_sign(char *str, output_specs *specs, bool is_negative) {
  if (specs->space) {
    if (is_negative)
      *str = '-';
    else
      *str = ' ';
    // *str++;
  } else if (specs->plus) {
    if (is_negative)
      *str = '-';
    else
      *str = '+';
    // *str++;
  } else {
    if (is_negative) {
      *str = '-';
      // *str++;
    }
  }
  if (specs->space || specs->plus || is_negative) str++;
  return str;  // иначе ошибка expression result unused
}

char *put_number(char *str, long num, output_specs *specs) {
  s21_size_t digits_quality = get_digits_quality(num);
  if (specs->accuracy > digits_quality &&
      (specs->spec == 'd' || specs->spec == 'i')) {
    while (specs->accuracy - digits_quality != 0) {
      *str = '0';
      str++;
      specs->accuracy--;
    }
  }
  if (num == 0) {
    *str = '0';
    str++;
  } else {
    while (digits_quality) {
      *str =
          (num / (long int)pow(
                     (double)10,
                     (double)(digits_quality == 1 ? 0 : digits_quality - 1))) +
          '0';
      num %= (long int)pow(
          (double)10, (double)(digits_quality == 1 ? 0 : digits_quality - 1));
      digits_quality--;
      str++;
    }
  }
  return str;
}

s21_size_t get_digits_quality(long num) {
  s21_size_t result = 0;

  if (num < 0) num = -num;

  if (num == 0)
    result = 1;
  else {
    while (num != 0) {  // кол-во цифер в числе
      num /= 10;
      result++;
    }
  }
  return result;
}

char *put_spaces_with_minus(char *str) {
  s21_size_t length = s21_strlen(str);

  while (length) {
    *str = ' ';
    str++;
    length--;
  }
  return str;
}

char *put_spaces_without_minus(char *str, output_specs *specs, bool minus,
                               long integer_part_of_num) {
  bool place_for_sign = false;
  s21_size_t place_for_int_part_of_num =
      get_digits_quality(integer_part_of_num);

  int space_for_dot =
      (specs->accuracy && specs->has_accuracy &&
       (specs->spec == 'f' || specs->spec == 'e' || specs->spec == 'E'))
          ? 1
          : 0;

  if (specs->plus || specs->space || minus) place_for_sign = true;
  int space_for_sign = place_for_sign ? 1 : 0;
  int space_for_sharp = 0;

  if (specs->sharp) {
    if (specs->spec == 'x' || specs->spec == 'X') space_for_sharp = 2;
    if (specs->spec == 'o') space_for_sharp = 1;
  }

  int space_for_pow = 0;
  if (specs->spec == 'e' || specs->spec == 'E') {
    space_for_pow = 4;
  } else {
    space_for_pow = 0;
  }

  while (specs->width >
         (specs->accuracy + space_for_dot + space_for_sign +
          place_for_int_part_of_num + space_for_sharp + space_for_pow)) {
    if (specs->zero && !specs->has_accuracy)
      *str = '0';
    else
      *str = ' ';
    str++;
    specs->width--;
  }
  return str;
}

char *input_float(char **str, output_specs *specs, va_list *arguments) {
  double num = 0;
  if (specs->L)
    num = (double)va_arg(*arguments, long double);
  else
    num = (double)va_arg(*arguments, double);

  s21_size_t weight_of_number =
      get_weight_of_float_number((long double)num, specs);

  char *buff = (char *)calloc((weight_of_number + 1), sizeof(char));
  if (!buff) return s21_NULL;
  buff[weight_of_number] = '\0';
  char *start_of_buff = buff;

  fill_buff_with_float_number(specs, buff, num);

  *str = s21_strncat(*str, start_of_buff, weight_of_number);
  free(buff);

  return *str + weight_of_number;
}

void fill_buff_with_float_number(output_specs *specs, char *buff,
                                 long double num) {
  bool is_negative = false;

  if (num < 0) {
    num = -num;
    is_negative = true;
  }

  if (specs->minus) {  //
    buff = put_char_of_sign(buff, specs, is_negative);
    buff = put_float_number(buff, num, specs);
    buff = put_spaces_with_minus(buff);
  } else {
    if (specs->zero) {
      buff = put_char_of_sign(buff, specs, is_negative);
      buff = put_float_width_without_minus(buff, specs, is_negative, (long)num);
    } else {
      buff = put_spaces_without_minus(buff, specs, is_negative, (long)num);
      buff = put_char_of_sign(buff, specs, is_negative);
    }
    buff = put_float_number(buff, num, specs);
  }
}

char *put_float_number(char *buff, long double num, output_specs *specs) {
  double integer = 0;
  double fractional = modf(num, &integer);
  s21_size_t buff_ac = specs->accuracy;
  // printf("put_float_number arguments is %Lf\n", num);
  // printf("put_float_number integer part is %lf\n", integer);
  // printf("put_float_number fractional is %lf\n", fractional);

  if (fractional + (double)0.000000000000001 >=
      1) {  // костыль, связанный с особенностями работы modf и хранением вещ
            // чсел в памяти компьютера
    fractional = 0;
    integer += 1;
  }
  while (buff_ac) {
    fractional *= 10;
    buff_ac--;
  }
  fractional = round(fractional);
  if (fractional == 1) integer++;
  // printf("put_float_number fractional after round is %lf\n", fractional);
  buff = put_number(buff, (long)integer, specs);

  if (specs->accuracy) {
    *buff = '.';
    buff++;
    if (fractional ==
        0) {  // елси пространство под точность нужно заполнить нулями
      while (specs->accuracy) {
        *buff = '0';
        buff++;
        specs->accuracy--;
      }
    } else {  // елси после точки не только нули
      buff = put_number(buff, (long)fractional, specs);
    }
  }
  if (specs->spec == 'E' || specs->spec == 'e') buff = put_linter(buff, specs);
  return buff;
}

s21_size_t get_weight_of_float_number(long double num, output_specs *specs) {
  s21_size_t result = 0;
  bool is_negative = false;
  if (num < 0) {  // если отрицательное
    num = -num;
    is_negative = true;
  }
  if (!specs->has_accuracy)  // если точность не указана никакая -- делаем
                             // стандартной
    specs->accuracy = 6;
  if (specs->spec == 'g' ||
      specs->spec == 'G') {  // костыль для g --> если не задана точность не
                             // выводить ненужные нули
    long double buff = num * pow((double)10, (double)(int)specs->accuracy);
    buff = round(buff);
    while ((long int)buff % 10 == 0 && specs->accuracy != 0) {
      specs->accuracy -= 1;
      buff /= 10;
    }
  }
  if (num == 0)  // если ноль - выделяем под него память
    result += 1;
  else
    result +=
        get_digits_quality((long)num);  // под колличество символов целой части

  if (specs->space || specs->plus ||
      is_negative)  // дополнительное место для пробела или знака
    result += 1;

  if (specs->spec == 'e' || specs->spec == 'E' || specs->spec == 'z' ||
      specs->spec == 'Z') {
    result += 4;  // доп место для степени
  }

  if (specs->accuracy)              // если точность не 0
    result += specs->accuracy + 1;  // под символы точности и точку

  if (specs->width > result)  // если указана ширина и она больше текщего
                              // размера
    result = specs->width;
  return result;
}

char *input_char(char **str, output_specs *specs, va_list *arguments) {
  int symbol = 0;
  if (specs->spec == '%')
    symbol = '%';
  else
    symbol = (int)va_arg(*arguments, int);
  if (symbol > 127) {
    return s21_NULL;  // выход неправильный символ
  }
  if (specs->minus) {  // если есть флаг -
    *str = put_symbol(
        str, symbol);  // Используем *str для изменения значения через указатель
    *str = fill_the_width_for_char(
        str, specs);  // Аналогично для fill_the_width_for_char
  } else {
    *str = fill_the_width_for_char(
        str, specs);  // Аналогично для fill_the_width_for_char
    *str = put_symbol(
        str, symbol);  // Используем *str для изменения значения через указатель
  }
  *(*str) = '\0';  // нулевой символ в конец строки

  return *str;
}

char *put_symbol(char **str, int symbol) {
  **str = (char)symbol;  // ставим символ
  (*str)++;
  return *str;
}

char *fill_the_width_for_char(char **str, output_specs *specs) {
  if (specs->width != 0) {
    while ((specs->width - 1) > 0) {  // заполняем ширину
      **str = ' ';
      (*str)++;
      specs->width--;
    }
  }
  return *str;
}

char *put_float_width_without_minus(char *str, output_specs *specs,
                                    bool is_negative, long num) {
  int space_for_sign = 0;
  s21_size_t place_for_int_part_of_num = get_digits_quality(num);
  int space_for_dot =
      (specs->accuracy && specs->has_accuracy &&
       (specs->spec == 'f' || specs->spec == 'e' || specs->spec == 'E'))
          ? 1
          : 0;
  int space_for_pow = 0;
  if (specs->spec == 'e' || specs->spec == 'E') {
    space_for_pow = 4;
  } else {
    space_for_pow = 0;
  }

  if (specs->plus || specs->space || is_negative) space_for_sign = 1;

  while (specs->width > (specs->accuracy + space_for_dot + space_for_sign +
                         place_for_int_part_of_num + space_for_pow)) {
    *str = '0';
    str++;
    specs->width--;
  }
  return str;
}

char *input_unsigned(char **str, output_specs *specs, va_list *arguments) {
  unsigned long num = 0;
  if (specs->spec == 'p') {
    specs->spec = 'x';
    specs->l = true;
    specs->sharp = true;
  }
  if (specs->l)
    num = (unsigned long)va_arg(*arguments, unsigned long);
  else if (specs->h)
    num = (unsigned short)va_arg(*arguments, unsigned int);
  else
    num = (unsigned int)va_arg(*arguments, unsigned int);

  if (specs->spec == 'x' || specs->spec == 'X')  // определяем основание сс
    specs->base_of_notation = 16;
  if (specs->spec == 'o') specs->base_of_notation = 8;
  if (specs->spec == 'u') specs->base_of_notation = 10;

  s21_size_t weight_of_number = get_weight_of_unsigned_number(num, specs);

  char *buff = (char *)calloc((weight_of_number + 1), sizeof(char));
  if (!buff) {
    return s21_NULL;
  }
  buff[weight_of_number] = '\0';
  char *start_of_buff = buff;

  fill_buff_with_unsigned_number(specs, buff, num);
  *str = s21_strncat(*str, start_of_buff, weight_of_number);
  free(buff);

  return *str + weight_of_number;
}

s21_size_t get_weight_of_unsigned_number(unsigned long int num,
                                         output_specs *specs) {
  s21_size_t result = 0;
  if (num == 0)
    result = 1;
  else
    result = get_dif_notation_digits_quality(num, specs->base_of_notation);

  if (specs->accuracy >
      result)  // указывает на минимальное количество символов,
               // необходимы для отображения типов d, i, ...
               // (остальное пространство заполняется нулями)
    result = specs->accuracy;

  if (specs->sharp) {  // елси есть шарп --> выделяем место для литерала
    if (specs->spec == 'x' || specs->spec == 'X') result += 2;
    if (specs->spec == 'o') result += 1;
  }

  if (specs->width > result)  // указывает минимальную ширину поля
    result = specs->width;

  return result;
}

s21_size_t get_dif_notation_digits_quality(unsigned long int num, int base) {
  s21_size_t result = 0;

  if (num == 0)
    result = 1;
  else {
    while (num) {  // кол-во цифер в числе
      num /= base;
      result++;
    }
  }

  return result;
}

void fill_buff_with_unsigned_number(output_specs *specs, char *buff,
                                    unsigned long num) {
  if (specs->minus) {
    buff = put_unsigned_number(buff, num, specs);
    buff = put_spaces_with_minus(buff);
  } else {
    buff = put_spaces_without_minus(buff, specs, false, (long)num);
    buff = put_unsigned_number(buff, num, specs);
  }
}

char *put_unsigned_number(char *buff, unsigned long num, output_specs *specs) {
  s21_size_t digits_quality =
      get_dif_notation_digits_quality(num, specs->base_of_notation);
  if (specs->sharp) {  // елси есть шарп --> ставим соответствующие литералы
    if (specs->spec == 'x' || specs->spec == 'X') {
      *buff = '0';
      buff++;
      if (specs->spec == 'X')
        *buff = 'X';
      else
        *buff = 'x';
      buff++;
    }
    if (specs->spec == 'o') {
      *buff = '0';
      buff++;
    }
  }
  if (specs->accuracy) {
    s21_size_t acc = specs->accuracy;
    while (acc > digits_quality) {
      *buff = '0';
      buff++;
      acc--;
    }
  }
  while (digits_quality) {
    unsigned long cur_digit =
        (num / (unsigned long)pow(
                   (double)specs->base_of_notation,
                   (double)(digits_quality == 1 ? 0 : digits_quality - 1)));
    if (cur_digit >= 10) {  // если буква
      *buff = 65 + (cur_digit - 10);
      if ((specs->spec == 'x' || specs->spec == 'o') && *buff >= 'A' &&
          *buff <= 'Z') {
        *buff = *buff - ('A' - 'a');
      }
    } else  // елси цифра
      *buff = '0' + cur_digit;
    num %= (unsigned long)pow(
        (double)specs->base_of_notation,
        (double)(digits_quality == 1 ? 0 : digits_quality - 1));
    digits_quality--;
    buff++;
  }
  return buff;
}

char *input_string(char *str, output_specs *specs, va_list *arguments) {
  char *str_to_input = (char *)va_arg(*arguments, char *);

  if (*str_to_input == '\0') return str;

  if (specs->minus) {
    str = put_string_to_str(str, str_to_input, specs);
    str = put_width_with_string(str, str_to_input, specs);
  } else {
    str = put_width_with_string(str, str_to_input, specs);
    str = put_string_to_str(str, str_to_input, specs);
  }
  return str;
}

char *put_string_to_str(char *str, char *str_to_input, output_specs *specs) {
  s21_size_t acc = specs->accuracy;
  while (*str_to_input != '\0') {
    if (specs->has_accuracy) {
      if (!acc)
        break;
      else
        acc--;
    }
    if (!str)
      return s21_NULL;
    else {
      *str = *str_to_input;
      str++;
      str_to_input++;
    }
  }
  return str;
}

char *put_width_with_string(char *str, char *str_to_string,
                            output_specs *specs) {
  s21_size_t lenth = s21_strlen(str_to_string);
  s21_size_t real_lenth = specs->has_accuracy ? specs->accuracy : lenth;
  while (specs->width > real_lenth) {
    *str = ' ';
    str++;
    specs->width--;
  }
  return str;
}

char *input_scientific_notation(char **str, output_specs *specs,
                                va_list *arguments) {
  long double num = 0;
  bool is_negative = false;

  if (specs->L) {
    num = (long double)va_arg(*arguments, long double);
  } else {
    num = (double)va_arg(*arguments, double);
  }

  if (num < 0) {
    num = -num;
    is_negative = true;
  }

  num = get_power_and_mantissa(num, specs);

  if (is_negative) num = -num;
  s21_size_t weight = get_weight_of_float_number(num, specs);

  char *buff = (char *)calloc(weight + 1, sizeof(char));
  char *start_of_buff = buff;
  if (!buff) return s21_NULL;
  buff[weight] = '\0';

  fill_buff_with_float_number(specs, buff, num);

  *str = s21_strncat(*str, start_of_buff, weight);
  free(start_of_buff);
  return *str + weight;
}

char *put_linter(char *buff, output_specs *specs) {
  *buff = specs->spec;
  buff++;

  if (specs->pow_val < 0) {
    *buff = '-';
    specs->pow_val = -specs->pow_val;
  } else
    *buff = '+';
  buff++;

  if (specs->pow_val >= 10)
    *buff = specs->pow_val / 10 + '0';
  else
    *buff = '0';
  buff++;

  *buff = specs->pow_val % 10 + '0';
  buff++;
  return buff;
}

void input_quality(va_list *arguments, char *str_start) {
  s21_size_t length = s21_strlen(str_start);

  int *ptr_to_int = (int *)va_arg(*arguments, int *);

  *ptr_to_int = (int)length;
}

long double get_power_and_mantissa(long double num, output_specs *specs) {
  bool pow_is_negative = false;
  if (num == 0)
    specs->pow_val = 0;
  else {
    while (num >= 10 ||
           num < 1) {  // проверка, что перед запятой осталось только одно число
      if (num < 1) {
        num *= 10;
        pow_is_negative = true;
      }
      if (num > 10) {
        num /= 10;
        pow_is_negative = false;
      }
      specs->pow_val++;
    }

    if (pow_is_negative) specs->pow_val = -specs->pow_val;
  }
  return num;
}

char *input_shortest_record(char **str, output_specs *specs,
                            va_list *arguments) {
  long double num = 0;
  bool is_negative = false;
  if (specs->L) {
    num = (long double)va_arg(*arguments, long double);
  } else {
    num = (double)va_arg(*arguments, double);
  }
  if (num < 0) {
    num = -num;
    is_negative = true;
  }
  long double num_cpy = get_power_and_mantissa(num, specs);
  s21_size_t acc = 0;
  if (specs->has_accuracy && specs->accuracy) {
    acc = specs->accuracy;
  } else if (specs->has_accuracy && specs->accuracy == 0) {
    acc = 1;
    specs->accuracy = 1;
  } else if (!specs->has_accuracy) {
    specs->has_accuracy = true;
    specs->accuracy = 6;
    acc = specs->accuracy;
  }
  s21_size_t weight =
      get_weight_from_shortest(specs, acc, is_negative, num, num_cpy);
  char *buff = (char *)calloc(weight + 1, sizeof(char));
  if (!buff) return s21_NULL;
  char *start_of_buff = buff;
  buff[weight] = '\0';
  if (specs->spec == 'f')
    num = is_negative ? -num : num;
  else if (specs->spec == 'e' || specs->spec == 'E')
    num = is_negative ? -num_cpy : num_cpy;
  fill_buff_with_float_number(specs, start_of_buff, num);
  *str = s21_strncat(*str, start_of_buff, weight);
  free(start_of_buff);

  return (*str + weight);
}

s21_size_t get_weight_from_shortest(output_specs *specs, s21_size_t acc,
                                    bool is_negative, long double num,
                                    long double num_cpy) {
  s21_size_t weight = 0;
  if (((long int)acc > (long int)specs->pow_val && specs->pow_val >= -4) ||
      specs->pow_val == 0) {
    specs->accuracy = acc - 1 - specs->pow_val;
    weight = get_weight_of_float_number(is_negative ? -num : num, specs);
    specs->spec = 'f';
  } else {
    specs->accuracy = acc - 1;
    specs->spec = specs->spec == 'g' ? 'z' : 'Z';
    weight =
        get_weight_of_float_number(is_negative ? -num_cpy : num_cpy, specs);
    specs->spec = specs->spec == 'z' ? 'e' : 'E';
  }

  return weight;
}
