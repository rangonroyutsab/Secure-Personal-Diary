#ifndef FUCNTION_PROTOTYPES_H_INCLUDED
#define FUCNTION_PROTOTYPES_H_INCLUDED

void delay (int number_of_seconds);
void show_Time ();

int HASH(char *pass);
int HASH2(char *pass);

void encode(char* s);
void decode(char* s);

void setpass(int user_level);
void password_change(int user_level);

void add_record (int user_level);
void view_record (int user_level);
void view_all_records(int user_level);
void modify_record (int user_level);
void delete_record (int user_level);
void show_today_record(int user_level);

void erase_everything ();

#endif // FUCNTION_PROTOTYPES_H_INCLUDED
