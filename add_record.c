#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diary.h"

#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 5000

void add_record (int user_level) {
  system ("cls");
  show_Time ();


  time_t current_time = time (NULL);
  char date_string[DATE_SIZE], time_string[TIME_SIZE];
  strftime (date_string, DATE_SIZE, "%d-%m-%Y", localtime (&current_time));
  strftime (time_string, TIME_SIZE, "%I:%M %p", localtime (&current_time));

  FILE* f_pointer = fopen (date_string, "r");
  struct record new_record;

  if (f_pointer == NULL) {
    printf ("No records added today.\n\n");
    FILE* date_file = fopen ("available_records.txt", "a+");

    fprintf (date_file, date_string);
    fprintf (date_file, "\n");
    fclose (date_file);
  } else {
    int i = 1;
    printf ("Currently added notes today: \n\n");
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
    fclose (f_pointer);
  }

  f_pointer = fopen (date_string, "a");
  if (f_pointer == NULL) {
    printf ("** Error creating record. **\n");
    exit (1);
  }

  if (user_level > 0) {
    printf ("Select the privacy type of your note: \n");
    if (user_level >= 0)
      printf ("1. Public\n");
    if (user_level >= 1)
      printf ("2. Protected\n");
    if (user_level >= 2)
      printf ("3. Private\n");
    int choice;
    scanf ("%d", &choice);

    switch (choice) {
    case 1:
      new_record.privacy_level = 0;
      break;
    case 2:
      new_record.privacy_level = 1;
      break;
    case 3:
      new_record.privacy_level = 2;
      break;
    default:
      printf ("Invalid choice. Exiting.\n");
      delay (1);
      return;
    }
  } else {
    new_record.privacy_level = 0;
  }

  strcpy (new_record.time, time_string);
  printf ("Enter the note: \n>> ");
  fflush(stdin);
  gets (new_record.note);
  encode(new_record.note);
  fwrite (&new_record, sizeof (struct record), 1, f_pointer);
  fclose (f_pointer);
}
