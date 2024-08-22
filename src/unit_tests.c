#include "tests/test_string.h"

void run_tests() {
  int count_of_tests = 21;
  Suite *suite = NULL;
  SRunner *sRunner = NULL;
  Suite *suite_array[] = {memchr_suite(),   memcmp_suite(),   strstr_suite(),
                          memcpy_suite(),   memset_suite(),   strncat_suite(),
                          strchr_suite(),   strncpy_suite(),  strerror_suite(),
                          strlen_suite(),   strrchr_suite(),  strpbrk_suite(),
                          strtok_suite(),   strncmp_suite(),  strcspn_suite(),
                          to_upper_suite(), to_lower_suite(), strcat_suite(),
                          trim_suite(),     insert_suite(),   sprintf_suite()};

  for (int i = 0; i < count_of_tests; i++) {
    suite = suite_array[i];
    sRunner = srunner_create(suite);
    srunner_set_fork_status(sRunner, CK_NOFORK);

    srunner_run_all(sRunner, CK_NORMAL);
    srunner_free(sRunner);

    suite = NULL;
    sRunner = NULL;
    putchar('\n');
  };
}

int main() { run_tests(); }