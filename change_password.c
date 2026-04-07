#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 5000


void password_change(int user_level) {
  system("cls");
  if (user_level <= 0) {
    printf("Sorry, this option is not applicable for the guest.\n");
    delay(1);
    return;
  }
  printf("Enter old password: ");
  fflush(stdin);

  char tmp[30];
  long long int a, b;
  gets(tmp);
  a = HASH(tmp);

  FILE *fp;
  if (user_level == 2)
    fp = fopen("admin_pass.txt", "r");
  if (user_level == 1)
    fp = fopen("part_pass.txt", "r");

  fscanf(fp, "%lld", &b);
  fclose (fp);

  if (a == b) {
    printf ("                         \x1b[32m*** Password matched ***\x1b[0m\n");
    setpass(user_level);
  } else {
    printf ("                          \x1b[31m*** Wrong password ***\x1b[0m\n");
    printf ("                            *** Try Again ***\n");
  }
  delay(1);
}
