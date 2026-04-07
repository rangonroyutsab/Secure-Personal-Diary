#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int key = 128;

void encode(char* s) {
  int n = strlen(s);
  char t[n];
  for (int i=0; i<n; i++) {
    s[i] = s[i] + key;
  }
}

void decode(char* s) {
  int n = strlen(s);
  char t[n];
  for (int i=0; i<n; i++) {
    s[i] = s[i] - key;
  }
}
