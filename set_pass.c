#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 5000

void setpass(int user_level) {
  printf ("                       \x1b[6m*** ENTER A NEW PASSWORD...***\x1b[0m\n");
  FILE *f_pointer;
  if (user_level == 2)
    f_pointer = fopen("admin_pass.txt", "w+");
  if (user_level == 1)
    f_pointer = fopen("part_pass.txt", "w+");

  if (f_pointer == NULL) {
    printf("Password set failed.\n");
    exit(1);
  }
  fflush(stdin);

  char s[30];
  gets(s);
  int h_val = HASH(s);
  fprintf(f_pointer, "%d", h_val);
  printf ("                     \x1b[6m*** Password set successfully! ***\x1b[0m\n");
  fclose(f_pointer);
}
