#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diary.h"

#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 5000


view_all_records(user_level) {
  FILE* date_file = fopen ("available_records.txt", "r");
  rewind (date_file);
  char date_string[DATE_SIZE];

  printf ("\x1b[5mDisplaying all available records:\x1b[0m\n\n");
  while (fscanf (date_file, "%s", date_string) != EOF) {
    printf("\x1b[4m%s:\x1b[0m\n", date_string);
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
    fclose (f_pointer);
  }
  fclose (date_file);
}
