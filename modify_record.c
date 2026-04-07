#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diary.h"
#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 5000

void modify_record (int user_level) {
  system ("cls");
  show_Time ();

  if (user_level <= 1) {
    printf("Sorry, this option is not available for you.\n");
    delay(1);
    return;
  }

  FILE* date_file = fopen ("available_records.txt", "r");
  char available_date[DATE_SIZE];
  rewind (date_file);

  printf ("Currently available recorded date: \n");
  while (fscanf (date_file, "%s", available_date) != EOF) {
    puts (available_date);
  }
  printf ("\n");
  fclose (date_file);

  char date_string[DATE_SIZE];
  printf ("Enter the date: ");

  fflush(stdin);
  gets (date_string);

  FILE* f_pointer = fopen (date_string, "r");
  if (f_pointer == NULL) {
    printf ("** Record does not exist. **\n");
    return;
  }
  struct record new_record;
  int i = 1;
  while (fread (&new_record, sizeof (struct record), 1, f_pointer)) {
    if (user_level >= new_record.privacy_level) {
      decode(new_record.note);
      printf("Note no. %d \nTime: %s \n", i, new_record.time);
      printf("Note: \n");
      switch(new_record.privacy_level) {
      case 2:
        printf("\x1b[36m");
        break;
      case 1:
        printf("\x1b[33m");
        break;
      case 0:
        printf("\x1b[32m");
        break;
      }

      int len = strlen(new_record.note);
      int cnt = 0;
      for (int cc=0; cc<len; cc++) {
        if (cnt >= 80 - 2) {

          if (new_record.note[cc] == " ")
            printf("\n");
          else {
            cc--;
            printf("-\n");
          }
          cnt = 0;
        } else {
          putchar(new_record.note[cc]);
          cnt++;
        }
      }
      printf("\x1b[0m \n\n");
    } else {
      printf ("Note no. %d \n\x1b[31mYou do not have the required permission to view this note.\x1b[0m\n\n", i);
    }
    i++;
  }

  printf ("Enter the no of note you want to modify: ");
  fflush(stdin);

  int k;
  char option;
  scanf ("%d", &k);

  rewind (f_pointer);
  char temp_name[] = "temp_file";
  FILE* tmp        = fopen (temp_name, "a");
  if (f_pointer == NULL) {
    printf ("** System error. Exiting program. **\n");
    delay (1);
    exit (1);
  }
  i = 1;
  while (fread (&new_record, sizeof (struct record), 1, f_pointer)) {
    if (i == k) {
      printf ("Do you want to modify the time? (y/n) :: ");
      fflush(stdin);

      option = getchar ();
      if (option == 'y') {
        printf ("Enter new time (12:59 AM): ");
        fflush(stdin);

        gets (new_record.time);
      }
      printf ("Do you want to modify the note? (y/n) :: ");
      fflush(stdin);

      option = getchar ();
      if (option == 'y') {
        printf ("Enter new note: ");
        fflush(stdin);
        gets (new_record.note);
        encode(new_record.note);
      }
    }
    fwrite (&new_record, sizeof (struct record), 1, tmp);
    i++;
  }
  fclose (tmp);
  fclose (f_pointer);
  remove (date_string);
  rename (temp_name, date_string);
}
