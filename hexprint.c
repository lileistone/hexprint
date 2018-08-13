/*
 *  PRINT_HEX.C
 *
 *  Print the contents of an array as hexadecimal and ASCII formats.
 *
 *  (C) Li Lei, 2017-10-18
 */

#include <stdio.h>



static int is_printable(unsigned char c);


/*------------------------------------------------------------------------------
  FUNCTION NAME: print_hex()
  PURPOSE:
        This function displays the contents of an array as hexadecimal and
        ASCII formats.
  PARAMETER:
        INPUT:  array         - base address of the array to be displayed;
                name          - name of the array;
                start_index   - start offset address of first byte to display;
                length        - number of bytes to display;
                start_address - start address displayed on the left column;
        OUTPUT:
            	NONE.
	
    RETURN VALUE:
                NONE.
------------------------------------------------------------------------------*/

/*
            +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
-------------------------------------------------------------------------------
0x0801ABC0: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F ; ................
*/

void  hexprint ( const unsigned char array[],
                  const unsigned char *name        ,
                        unsigned int  start_index  ,
                        unsigned int  length       ,
                        unsigned int  start_address  )
{
    unsigned int  lines, remainder, offset;
    unsigned int  start_rounding;
    unsigned int  curr_start_index, curr_start_address;

    unsigned int  i, j;

    printf("Contents of \"%s\": \n", name);

    offset          = start_index % 16;
    start_rounding  = start_index - offset;
    remainder       = (offset + length) % 16;
    lines           = (offset + length) / 16 + ( remainder > 0 );


    printf("            +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F\n");
    printf("-------------------------------------------------------------------------------\n");

    // Special treatment for First line
    curr_start_address = start_address - offset;
    printf("0x%08X: ", curr_start_address);     // Start address of the current line

    curr_start_index = start_rounding;          // Start index of the current line

    if ( offset != 0 )                          // The first line does not start from 0
    {
        for ( j = 0; j < 16; ++j )              // HEXes
        {
            if ( j < offset )
            {
                printf("   ");
            }
            else
            {
                printf("%02X ", array[curr_start_index + j]);
            }
        }

        printf("; ");                           // Seperator of HEX and ASCII

        for ( j = 0; j < 16; ++j )              // ASCIIes
        {
            if ( j < offset )
            {
                printf(" ");
            }
            else
            {
                if ( is_printable(array[curr_start_index + j]) )
                //if ( isprint(array[curr_start_index + j]) )
                {
                    printf("%c", array[curr_start_index + j]);
                }
                else
                {
                    printf(".");
                }
            }

        }

        printf("\n");                           // End of First line
    }
    else                                        // The first line starts from 0
    {
        for ( j = 0; j < 16; ++j )              // HEXes
        {
            printf("%02X ", array[curr_start_index + j]);
        }

        printf("; ");                           // Seperator of HEX and ASCII

        for ( j = 0; j < 16; ++j )              // ASCIIes
        {
            if ( is_printable(array[curr_start_index + j]) )
            //if ( isprint(array[curr_start_index + j]) )
            {
                printf("%c", array[curr_start_index + j]);
            }
            else
            {
                printf(".");
            }
        }

        printf("\n");                           // End of First line
    }

    for ( i = 1; i < lines - 1; ++i )           // Middle lines
    {
        curr_start_index   = start_rounding + i * 16;
        curr_start_address = curr_start_address + 16;

        printf("0x%08X: ", curr_start_address); // Start address of the current
                                                // line

        for ( j = 0; j < 16; ++j )              // HEXes
        {
            printf("%02X ", array[curr_start_index + j]);
        }

        printf("; ");                           // Seperator of HEX and ASCII

        for ( j = 0; j < 16; ++j )              // ASCIIes
        {

            //printf("%02X", array[curr_start_index + j]);
            if ( is_printable(array[curr_start_index + j]) )
            //if ( isprint(array[curr_start_index + j]) )
            {
                printf("%c", array[curr_start_index + j]);
            }
            else
            {
                printf(".");
            }

        }

        printf("\n");                           // End of current line

    }


    // Special treatment for Last line
    curr_start_index = start_rounding + (lines - 1) * 16;
    curr_start_address = curr_start_address + 16;

    printf("0x%08X: ", curr_start_address);     // Start address of the current
                                                // line

    if ( remainder != 0 )                       // The last line is not full
    {


        for ( j = 0; j < 16; ++j )              // HEXes
        {
            if ( j >= remainder )
            {
                printf("   ");
            }
            else
            {
                printf("%02X ", array[curr_start_index + j]);
            }
        }

        printf("; ");                           // Seperator of HEX and ASCII

        for ( j = 0; j < 16; ++j )              // ASCIIes
        {
            if ( j >= remainder )
            {
                printf(" ");
            }
            else
            {
                if ( is_printable(array[curr_start_index + j]) )
                //if ( isprint(array[curr_start_index + j]) )
                {
                    printf("%c", array[curr_start_index + j]);
                }
                else
                {
                    printf(".");
                }
            }

        }

        printf("\n");                           // End of First line
    }

    else                                        // The last line is full

    {
        for ( j = 0; j < 16; ++j )              // HEXes
        {
            printf("%02X ", array[curr_start_index + j]);
        }

        printf("; ");                           // Seperator of HEX and ASCII

        for ( j = 0; j < 16; ++j )              // ASCIIes
        {
            if ( is_printable(array[curr_start_index + j]) )
            //if ( isprint(array[curr_start_index + j]) )
            {
                printf("%c", array[curr_start_index + j]);
            }
            else
            {
                printf(".");
            }
        }

        printf("\n");                           // End of First line
    }

    return ;

}



/*------------------------------------------------------------------------------
  FUNCTION NAME: is_printable()
  PURPOSE:
        This function validates whether the input character is printable or not.
  PARAMETER:
        INPUT:  c   - the character to be judged.
        OUTPUT:
            	NONE.
	
    RETURN VALUE:
                1 - printable;
                0 - un-printable.
------------------------------------------------------------------------------*/

static int is_printable(unsigned char c)
{
    return ( ( c >= ' ' && c <= '~' ) ?  1  :  0 );
}

