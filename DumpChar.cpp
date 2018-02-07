#include <stdio.h>
 
int main(void)
{
    FILE *fp;
    unsigned char value;
    int i=0, j;
    unsigned char character[16];
     
     
    fp = fopen ("arp.pcap", "rb");
    if(fp == NULL)
    {
        printf("There is a problem to open file. :(\n");
        return 0;
    }
     
     
    while(!feof(fp))
    {
        i++;
        fread(&value, sizeof(value), 1, fp);
        character[i-1] = (char)value;
        printf("%02X ", value);
         
        if(i==8)
        {
            printf("   ");
        }
        if(!(i % 16))
        {
            printf("\t");
            printf("|");
            for(j=0; j<16; j++)
            {
                if(isprint(character[j]))
                    printf("%c", character[j]);
                else
                    printf(".");
             
            }
            printf("|");
            printf("\n");
            i=0;
        } 
     
     
     
    }
     
    for(j=0; j<i+1; j++)
        printf("\t");
    printf("|");
    for(j=0; j<16; j++)
    {
        if(isprint(character[j]))
            printf("%c", character[j]);
        else
            printf(".");
         
    }
    printf("|");
     
    printf("\n");
     
    printf(" :) \n");
    fclose(fp);
 
 
    return 0;
}