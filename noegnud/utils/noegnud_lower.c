#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    char *ch;
    if (argc < 2)
        exit(0);

    ch = argv[1];
    while (*ch) {
        printf("%c", tolower(*ch));
        ch++;
    }
    printf("\n");
    return 0;
}
