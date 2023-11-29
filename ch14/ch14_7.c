#include <stdlib.h>
#include <stdio.h>

int 
main (int argc, char* argv[])
{
    int* ptr = malloc(100*sizeof(int));
    ptr[15] = 3;
    printf("%d\n",ptr[15]);
    free(ptr+4);
    printf("%d\n",ptr[15]);

    return 0;
}