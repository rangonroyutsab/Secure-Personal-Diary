#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 5000

void erase_everything () {
  char available_records[] = "available_records.txt";
  char date_string[DATE_SIZE];

  FILE* date_file = fopen (available_records, "r");
  rewind (date_file);
  while (fscanf (date_file, "%s", date_string) != EOF) {
    remove(date_string);

  }
  fclose (date_file);
  remove(available_records);
}
