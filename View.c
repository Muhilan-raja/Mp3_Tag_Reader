#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/* show the first 6 ID3v2.3 tags from an MP3 */
void view_tag(FILE *fp)
{
    printf("=========== MP3 Tag Viewer ===========\n");
    char tag[5];
    int size;

    // skip 10-byte ID3 header
    fseek(fp, 10, SEEK_SET);

    // process 6 common frames (Title, Artist, Album, Year, Genre, Comment)
    for (int i = 0; i < 6; i++)
    {
        fread(tag, sizeof(char), 4, fp);
        tag[4] = '\0';

        fread(&size, sizeof(int), 1, fp);
        Big_To_Little_endian(&size, sizeof(size)); // convert size

        fseek(fp, 3, SEEK_CUR); // skip 3 flag bytes

        char *content = malloc(size + 1);
        fread(content, sizeof(char), size - 1, fp);
        content[size - 1] = '\0';

        print_tag(tag, content);
        free(content);
    }
    
    printf("======================================\n");
    printf("Done Tags displayed successfully.\n\n");
}

/* convert a 4-byte number between big/little endian */
void Big_To_Little_endian(void *ptr, int len)
{
    char *bytes = (char *)ptr;
    for (int i = 0; i < len / 2; i++)
    {
        char temp = bytes[i];
        bytes[i] = bytes[len - 1 - i];
        bytes[len - 1 - i] = temp;
    }
}

/* print each tag in a readable way */
void print_tag(char *tag, char *content)
{
    if    (strcmp(tag,"TIT2")==0) 
    printf("Title   : %s\n", content);
    else if (strcmp(tag,"TPE1")==0) 
    printf("Artist  : %s\n", content);
    else if (strcmp(tag,"TALB")==0) 
    printf("Album   : %s\n", content);
    else if (strcmp(tag,"TYER")==0) 
    printf("Year    : %s\n", content);
    else if (strcmp(tag,"TCON")==0) 
    printf("Genre   : %s\n", content);
    else if (strcmp(tag,"COMM")==0) 
    printf("Comment : %s\n", content);
}
