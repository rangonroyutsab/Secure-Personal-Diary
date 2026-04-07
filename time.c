#include <time.h>

void delay (int number_of_seconds) {
  int milli_seconds  = 1000 * number_of_seconds;
  clock_t start_time = clock ();
  while (clock () < start_time + milli_seconds);
}

void show_Time () {
  time_t current_time = time (NULL);

  char date_string[20];
  strftime (date_string, 20, "%d-%m-%Y", localtime (&current_time));

  char time_string[10];
  strftime (time_string, 10, "%I:%M %p", localtime (&current_time));

  printf ("*******************************************************************************\n");
  printf ("\x1b[47m\x1b[30mThe current date is: %s                                                \x1b[0m\n", date_string);
  printf ("\x1b[47m\x1b[30mThe current time is: %s                                                  \x1b[0m\n", time_string);
  printf ("*******************************************************************************\n\n");
}
