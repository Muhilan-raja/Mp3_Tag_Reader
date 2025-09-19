#include <stdio.h>
#include <string.h>
#include "header.h"

/* CLI entry: routes to view (-v) or edit (-e). */
void main(int argc, char *argv[])
{
    FILE *fp;

    /* view tags: ./a.out -v file.mp3 */
    if (argc == 3 && strcmp(argv[1], "-v") == 0)
    {
        fp = fopen(argv[2], "rb");
        if (fp == NULL)
        {
            printf("Cannot open file: %s\n", argv[2]);
            return;
        }

        view_tag(fp);
        fclose(fp);
    }
    /* edit tag: ./a.out -e file.mp3 <opt> <value> */
    else if (argc == 5 && strcmp(argv[1], "-e") == 0)
    {
        edit_tag(argv[2], argv[3], argv[4]);
    }
    /* help menu (basic) */
    else if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        printf("--------------- HELP ----------------\n");
        printf("View tags:\n");
        printf("  ./a.out -v <file.mp3>\n\n");
        printf("Edit a tag:\n");
        printf("  ./a.out -e <file.mp3> <option> <new_value>\n");
        printf("Options:\n");
        printf("  -t  Title   (TIT2)\n");
        printf("  -a  Artist  (TPE1)\n");
        printf("  -A  Album   (TALB)\n");
        printf("  -y  Year    (TYER)\n");
        printf("  -g  Genre   (TCON)\n");
        printf("  -c  Comment (COMM)\n");
        printf("-------------------------------------\n");
    }
    /* no args or anything else → quick usage */
    else
    {
        printf("-------------------------------------\n");
        printf("Invalid arguments.\n");
        printf("Usage:\n");
        printf("  View : ./a.out -v <file.mp3>\n");
        printf("  Edit : ./a.out -e <file.mp3> <option> <new_value>\n");
        printf("  Help : ./a.out --help\n");
        printf("-------------------------------------\n");
    }
}
