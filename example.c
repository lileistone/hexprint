#include <stdio.h>
#include <malloc.h>

#include "hexprint.h"


int main ( int argc, char *argv[] )
{
    unsigned char *buff = NULL;
    FILE          *fp   = NULL;

    buff = (unsigned char *)malloc(100);
    if ( buff == NULL )
    {
        printf("Error allocating adequate memory in heap. Quit.\n");
        return -1;
    }

    fp = fopen("test.txt", "r");
    if ( fp == NULL )
    {
        printf("Error opening test file. Quit.\n");
        return -1;
    }

    fread(buff, sizeof(unsigned char), 100, fp);
    hexprint ( buff,                // The buffer to print/display on console
               "Test data",         // name of the buffer to display
               20,                  // display from the 20th element within the buffer, 
                                    // previous 20 bytes are ignored in this example
               80,                  // display 80 bytes
               ((unsigned long)buff + 20));     
                                    // the start address to display, this example shows the
                                    // virtual address of the buffer allocated by malloc()

    fclose(fp);
    free(buff);

    return 0;
}
    