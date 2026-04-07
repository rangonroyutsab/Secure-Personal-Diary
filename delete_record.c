#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 5000


void delete_record (int user_level) {
  system ("cls");
  show_Time ();

  if (user_level <= 1) {
    printf("Sorry, this option is not available for you.\n");
    delay(1);
    return;
  }

  char available_records[] = "available_records.txt";
  char temp_name[] = "temp_file.txt";

  char available_date[DATE_SIZE];
  char date_string[DATE_SIZE];

  FILE* date_file = fopen (available_records, "r");
  FILE* tmp = fopen(temp_name, "w+");

  printf ("Currently available recorded dates: \n");
  rewind (date_file);

  while (fscanf (date_file, "%s", available_date) != EOF) {
    puts (available_date);
  }
  printf("all\n");

  printf ("Enter the date: ");
  fflush(stdin);
  gets (date_string);
  if (strcmp(date_string, "all") == 0) {
    printf("Are you sure? (yes/no): ");
    fflush(stdin);
    gets(date_string);
    if (strcmp(date_string, "yes") == 0) {
      fclose(tmp);
      fclose (date_file);
      erase_everything();
    }
    return;
  }
  remove (date_string);
  rewind (date_file);
  while(fscanf (date_file, "%s", available_date) != EOF) {
    if (strcmp(available_date, date_string) == 0) {
      continue;
    }
    fprintf(tmp,"%s", available_date);
    fprintf(tmp, "\n", available_date);
  }
  fclose(tmp);
  fclose (date_file);
  remove(available_records);
  rename(temp_name, available_records);
  printf ("** Record deleted successfully **\n");
}
