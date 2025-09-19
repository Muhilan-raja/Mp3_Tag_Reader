#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void edit_tag(char *filename, char *tag_type, char *new_tag)
{
    char *tag_name = NULL;

    // map user option to actual ID3 frame
    if(strcmp(tag_type,"-t")==0)      
    tag_name="TIT2";
    else if(strcmp(tag_type,"-a")==0) 
    tag_name="TPE1";
    else if(strcmp(tag_type,"-A")==0) 
    tag_name="TALB";
    else if(strcmp(tag_type,"-y")==0) 
    tag_name="TYER";
    else if(strcmp(tag_type,"-g")==0) 
    tag_name="TCON";
    else if(strcmp(tag_type,"-c")==0) 
    tag_name="COMM";
    else
    {
        printf("Invalid option Use -t/-a/-A/-y/-g/-c\n");
        return;
    }

    FILE *fp  = fopen(filename,"r");
    FILE *fp1 = fopen("temp.mp3","w");

    if(!fp || !fp1)
    {
        printf(" Could not open files.\n");
        return;
    }

    // copy 10-byte ID3 header
    char header[10];
    fread(header,sizeof(char),10,fp);
    fwrite(header,sizeof(char),10,fp1);

    // process 6 common metadata frames
    for(int i=0;i<6;i++)
    {
        char tag[5];
        int size;
        char skip_byte[3];
        int new_size;

        fread(tag,sizeof(char),4,fp);
        tag[4]='\0';

        fread(&size,sizeof(int),1,fp);
        endian_conversion(&size,sizeof(size));

        fread(skip_byte,sizeof(char),3,fp);

        char *content = malloc(size+1);
        fread(content,sizeof(char),size-1,fp);

        // found the frame to edit
        if(strcmp(tag_name,tag)==0)
        {
            new_size = strlen(new_tag)+1;

            fwrite(tag,1,4,fp1);
            endian_conversion(&new_size,sizeof(new_size));
            fwrite(&new_size,4,1,fp1);
            fwrite(skip_byte,sizeof(char),3,fp1);
            endian_conversion(&new_size,sizeof(new_size));
            fwrite(new_tag,sizeof(char),new_size-1,fp1);

            printf("\n===== MP3 Tag Edit =====\n");
            if(strcmp(tag,"TIT2")==0)      
            printf("Title   -> %s\n", new_tag);
            else if(strcmp(tag,"TPE1")==0) 
            printf("Artist  -> %s\n", new_tag);
            else if(strcmp(tag,"TALB")==0) 
            printf("Album   -> %s\n", new_tag);
            else if(strcmp(tag,"TYER")==0) 
            printf("Year    -> %s\n", new_tag);
            else if(strcmp(tag,"TCON")==0) 
            printf("Genre   -> %s\n", new_tag);
            else if(strcmp(tag,"COMM")==0) 
            printf("Comment -> %s\n", new_tag);
            printf("========================\n\n");

            free(content);
            break;
        }
        else
        {
            // not the frame we want -> copy as-is
            fwrite(tag,sizeof(char),4,fp1);
            endian_conversion(&size,sizeof(size));
            fwrite(&size,sizeof(int),1,fp1);
            endian_conversion(&size,sizeof(size));
            fwrite(skip_byte,sizeof(char),3,fp1);
            fwrite(content,size-1,1,fp1);
        }

        free(content);
    }

    // copy remaining audio data
    char data;
    while(fread(&data,1,1,fp) > 0)
    {
        fwrite(&data,1,1,fp1);
    }

    fclose(fp);
    fclose(fp1);

    // replace old file with updated one
    remove(filename);
    rename("temp.mp3",filename);
}

// simple byte-swap (used for size fields)
void endian_conversion(void *ptr, int len)
{
    char *bytes = (char *)ptr;
    for (int i = 0; i < len / 2; i++)
    {
        char temp = bytes[i];
        bytes[i] = bytes[len - 1 - i];
        bytes[len - 1 - i] = temp;
    }
}

