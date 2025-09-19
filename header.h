#ifndef HEADER_H
#define HEADER_H

void view_tag(FILE*);
void Big_To_Little_endian(void *,int);
void print_tag(char*, char*);

void edit_tag(char*, char*, char*);
void endian_conversion(void*,int);
#endif