#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fucntion_prototypes.h"
#include "diary.h"

#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 500

typedef long long int LL;

int user_level = 0;

void menu () {
  int flag = 1, choice;
  char ch;
  while (flag) {
    system ("cls");
    show_Time ();
    printf ("Current User: \n");
    printf ("########################\n");

    switch (user_level) {
    case 0:
      printf ("#        \x1b[32mGuest\x1b[0m         #\n");
      break;
    case 1:
      printf ("#     \x1b[33mLife Partner\x1b[0m     #\n");
      break;
    case 2:
      printf ("#        \x1b[36mAdmin\x1b[0m         #\n");
      break;
    }
    printf ("########################\n");
    printf ("\n");
    show_today_record(user_level);
    printf ("\n");
    printf (">> \x1b[1mMENU\x1b[0m << \n");
    printf ("1. Add Record\n");
    printf ("2. View Record\n");
    printf ("3. Modify Record\n");
    printf ("4. Delete Record\n");
    printf ("5. Change Password\n");
    printf ("6. Log Out\n");
    printf (">> Enter your choice: ");

    ch     = _getch ();
    choice = ch - '0';
    printf ("%d\n", choice);

    switch (choice) {
    case 1: {
      add_record (user_level);
      printf ("Press any key to continue.\n");
      getch ();
      break;
    }
    case 2: {
      view_record (user_level);
      printf ("Press any key to continue.\n");
      getch ();
      break;
    }
    case 3: {
      modify_record (user_level);
      printf ("Press any key to continue.\n");
      getch ();
      break;
    }
    case 4: {
      delete_record (user_level);
      printf ("Press any key to continue.\n");
      getch ();
      break;
    }
    case 5: {
      password_change (user_level);
      printf ("Press any key to continue.\n");
      getch ();
      break;
    }
    case 6: {
      flag       = 0;
      user_level = 0;
      printf ("Logging out...\n");
      delay (1);
      break;
    }
    default: {
      printf ("Please enter a valid choice.\n");
      delay (1);
      break;
    }
    }
  }
}

int main () {
  int f = 1;
again:
  while (f) {
    system ("cls");
    char s[100];
    char ch;
    int choice, j;
    long long int a, b;

    printf ("*******************************************************************************\n");
    printf ("******************** \x1b[46m\x1b[30mWELCOME TO YOUR SECURED PERSONAL DIARY\x1b[0m *******************\n");
    printf ("*******************************************************************************\n");
    printf ("*                                                                             *\n");
    printf ("*                              \x1b[1mLOGIN MENU\x1b[0m                                     *\n");
    printf ("* SELECT USER:                                                                *\n");
    printf ("* 1. Admin                                                                    *\n");
    printf ("* 2. Life Partner                                                             *\n");
    printf ("* 3. Guest                                                                    *\n");
    printf ("* 4. Exit                                                                     *\n");

    printf ("* Choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      user_level = 2;
      break;
    case 2:
      user_level = 1;
      break;
    case 3:
      user_level = 0;
      break;
    case 4:
      printf ("                           \x1b[6m***  Exiting  ***\x1b[0m\n");
      exit (1);
    default:
      printf ("                          \x1b[6m*** Invalid Choice ***\x1b[0m\n");
      delay (1);
      goto again;
    }

    if (user_level == 0) {
      menu ();
    }

    else {
      FILE* fp;

      if (user_level == 2) {
        fp = fopen ("admin_pass.txt", "r");

        if (fp == NULL) {
          erase_everything();
          setpass (user_level);
          printf ("                     \x1b[6m*** Press any key to continue ***\x1b[0m\n");
          getch ();
          continue;
        }
      }
      if (user_level == 1) {
        fp = fopen ("part_pass.txt", "r");

        if (fp == NULL) {
          erase_everything();
          setpass (user_level);
          printf ("                     \x1b[6m*** Press any key to continue ***\x1b[0m\n");
          getch ();
          continue;
        }
      }

      printf ("* ENTER PASSWORD (Enter \"q\" to exit): ");
      fflush(stdin);

      j = 0;
      while ((ch = _getch ()) != 13) {
        if (ch == 8)
          continue;
        s[j] = ch;
        j++;
        printf ("*");
      }
      s[j] = '\0';
      printf ("\n");

      if (strcmp (s, "q") == 0)
        break;
      a = HASH (s);

      fscanf(fp, "%lld", &b);
      fclose (fp);

      if (a == b) {
        printf ("                         \x1b[32m*** Password matched ***\x1b[0m\n");
        printf ("                           \x1b[6m*** Signing in...***\x1b[0m\n");
        delay (2);
        menu ();
      } else {
        printf ("                          \x1b[31m*** Wrong password ***\x1b[0m\n");
        printf ("                            *** Try Again ***\n");
        delay (1);
      }
    }
  }
  return 0;
}
