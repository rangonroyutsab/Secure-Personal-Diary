#ifndef DIARY_H_INCLUDED
#define DIARY_H_INCLUDED

#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 500

struct record {
  int privacy_level;
  char time[TIME_SIZE];
  char note[NAME_SIZE];
};

#endif // DIARY_H_INCLUDED
